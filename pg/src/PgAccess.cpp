#include <exception>
#include <stdexcept>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <libpq-fe.h>
#include <libpq/libpq-fs.h>

#include "PgAccess.h"

// Connection exception class

PgError::PgError(const std::string& what) throw():
	std::runtime_error(what),
	m_what(what) {
}

PgError::PgError(const PgError& error) throw():
	std::runtime_error(error.m_what.c_str()),
	m_what(error.m_what) {
	//
}

PgError& PgError::operator = (const PgError&) throw() {
	//
	return *this;
}

PgError::~PgError() throw() {
	//
}

const char* PgError::what() const throw() {
	return std::runtime_error::what();
}

// Query result class

PgResult::PgResult(PgConnection* connection, PGresult* result):
	m_result(result),
	m_pConnection(connection) {
	m_tuplesCount = PQntuples(m_result);
	m_tupleNo = m_tuplesCount > 0 ? 0 : -1;
}

PgResult::~PgResult() {
	PQclear(m_result);
}

bool PgResult::HasNext() {
	return m_tupleNo + 1 < m_tuplesCount;
}

bool PgResult::Next() {
	if (!HasNext()) {
		return false;
	}
	printf("tuple no: %d", m_tupleNo);
	m_tupleNo++;
	return true;
}

int PgResult::NumRows() {
	return m_tuplesCount;
}

int PgResult::NumCols() {
	return PQnfields(m_result);
}

int PgResult::GetFieldNum(const char* fieldName) {
	return PQfnumber(m_result, fieldName);
}

PgResult::FieldType PgResult::GetFieldType(int fieldNo) {
	Oid fieldType = PQftype(m_result, fieldNo);
	switch (fieldType) {
		case 16: // bool
			return ftBool;
		case 18: // char
		case 19: // name
		case 25: // text
		case 1042: // bpchar
		case 1043: // varchar
		case 27712: // clob
			return ftChar;
		case 20: // int8
		case 21: // int2
		case 23: // int4
		case 26: // Oid
			return ftInt;
		case 700:
		case 701:
		case 1700:
			return ftFloat;
		//case 1082: // date
		//case 1184: // timestamp
		//	return ftDate;
		default:
			return ftUnknown;
	}
}

std::string PgResult::GetString(int fieldNo) {
	if (PQftype(m_result, fieldNo) == 26) { // Special case for BLOB
		char* value =  PQgetvalue(m_result, m_tupleNo, fieldNo);
		if (value == NULL) {
			return std::string("");
		}
		char* error;
		int oid = strtol(value, &error, 10);
		std::string result;
		m_pConnection->GetBlobContent(oid, result);
		return result;
	}

	if (PQftype(m_result, fieldNo) == 17) { // Special case for bytea.
		size_t size = PQgetlength(m_result, m_tupleNo, fieldNo);
		std::string result;
		result.resize(size);
		char* value =  PQgetvalue(m_result, m_tupleNo, fieldNo);
		if (value == NULL) {
			return std::string("");
		}
		result.assign(value, 0, size);
		return result;
	}

	if (PQgetisnull(m_result, m_tupleNo, fieldNo) == 1) { // Other cases
		return std::string("");
	}
	return m_pConnection->Decode(PQgetvalue(m_result, m_tupleNo, fieldNo));
}

bool PgResult::GetBoolean(int fieldNo) {
	if (GetFieldType(fieldNo) == ftBool) {
		char* value = PQgetvalue(m_result, m_tupleNo, fieldNo);
		return value[0] == 't';
	}
	throw PgError("Field type is not boolean");
}

int PgResult::GetInteger(int fieldNo) {
	if (GetFieldType(fieldNo) == ftInt) {
		char* value = PQgetvalue(m_result, m_tupleNo, fieldNo);
		char* error;
		return strtol(value, &error, 10);
	}
	throw PgError("Field type is not integer");
}

double PgResult::GetDouble(int fieldNo) {
	if (GetFieldType(fieldNo) == ftFloat) {
		char* value = PQgetvalue(m_result, m_tupleNo, fieldNo);
		char* error;
		return strtod(value, &error);
	}
	throw PgError("Field type is not double");
}

void notice_processor(void*, const char* message) {
	printf("PgConnection. Notice: %s\n", message);
}

// Connection class

PgConnection::PgConnection(const char* connectionInfo):
	m_connectionInfo(connectionInfo) {
	if (!Connect(connectionInfo)) {
		throw PgError("Connection failed. Cannot connect to postgresql server");
	}
}

PgConnection::~PgConnection() {
	// PQ
}

int PgConnection::CountSpecifiers(const std::string& query) {
	int countSpecifiers = 0;
	for (size_t i = 0; i < query.size(); ++i) {
		if (query[i] != '%') {
			continue;
		}
		if (i + 1 >= query.size()) {
			return -1;
		}
		switch (query[i]) {
			case 's': // string
			case 'i': // int
			case 'd': // int
			case 'b': // boolean
			case 'f': // float
				countSpecifiers++;
				break;
			default:
				return -1;
		}
	}
	return countSpecifiers;
}

void PgConnection::AddString(std::string& query, const char* s) {
	query += Encode(s);
}

void PgConnection::AddInteger(std::string& query, int i) {
	static char buffer[20];
	sprintf_s(buffer, "%d", i);
	query += buffer;
}

void PgConnection::AddBoolean(std::string& query, bool b) {
	query += b ? "true" : "false";
}

void PgConnection::AddDouble(std::string& query, double d) {
	static char buffer[32];
	sprintf_s(buffer, "%f", d);
	query += buffer;
}
	
bool PgConnection::MakeQuery(const std::string& query, va_list listArgs, std::string& result) {
	for (size_t i = 0; i < query.size(); ++i) {
		if (query[i] != '%') {
			result += query[i];
			continue;
		}
		if (i + 1 >= query.size()) {
			return false;
		}
		switch (query[i]) {
			case 's': // string
				AddString(result, va_arg(listArgs, const char *));
				break;
			case 'i':
			case 'd': // integer
				AddInteger(result, va_arg(listArgs, int));
				break;
			case 'b': // boolean
				AddBoolean(result, va_arg(listArgs, bool));
				break;
			case 'f': // double
				AddDouble(result, va_arg(listArgs, double));
				break;
			default:
				return false;
		}
	}
	return true;
}

PgResult PgConnection::Select(const std::string& query, ...) {
	if (!IsConnected()) {
		throw PgError("Didn't connected to postgresql server");
	}
	int countSpecifiers = CountSpecifiers(query);
	if (countSpecifiers == -1) {
		throw PgError("Illegal query format");
	}
	PGresult* result;
	if (countSpecifiers == 0) {
		result = PQexec(m_connection, query.c_str());
	} else {
		std::string queryString;
		va_list list;
		va_start(list, query);
		if(!MakeQuery(query, list, queryString)) {
			va_end(list);
			throw PgError("Illegal query format");
		}
		va_end(list);
		result = PQexec(m_connection, queryString.c_str());
	}
	if (result != NULL) {
		ExecStatusType status = PQresultStatus(result);
		if (status == PGRES_TUPLES_OK) {
			return PgResult(this, result);
		}
		if (status == PGRES_COMMAND_OK) {
			PQclear(result);
			throw PgError("Command which should return something returned nothing");
		}
	}
	// Error handling
	std::string errorText = PQerrorMessage(m_connection);
	if (result) {
		PQclear(result);
	}
	if (PQstatus(m_connection) == CONNECTION_BAD) {
		Disconnect();
		throw PgError("Connection reset in Select");
	} else {
		throw PgError(errorText);
	}
}

bool PgConnection::Update(const std::string& query, ...) {
	if (!IsConnected()) {
		throw PgError("Didn't connected to postgresql server");
	}
	while (true) {
		int countSpecifiers = CountSpecifiers(query);
		if (countSpecifiers == -1) {
			throw PgError("Illegal query format");
		}
		PGresult* result;
		if (countSpecifiers == 0) {
			result = PQexec(m_connection, query.c_str());
		} else {
			std::string queryString;
			va_list list;
			va_start(list, query);
			if(!MakeQuery(query, list, queryString)) {
				va_end(list);
				throw PgError("Illegal query format");
			}
			va_end(list);
			result = PQexec(m_connection, queryString.c_str());
		}
		if (result != NULL) {
			ExecStatusType status = PQresultStatus(result);
			if (status == PGRES_COMMAND_OK || status == PGRES_TUPLES_OK) {
				const char *tuples = PQcmdTuples(result);
				char *error = NULL;
				long n = strtol(tuples, &error, 10);
				if (*error != 0) {
					n = -1;
				}
				PQclear(result);
				return n >= 0;
			}
		}
		// Error handling
		std::string errorText = PQerrorMessage(m_connection);
		if (result) {
			PQclear(result);
		}
		if (PQstatus(m_connection) == CONNECTION_BAD) {
			if (m_inTransaction) {
				Disconnect();
				throw PgError("Connection reset in execUpdate");
			}
			Reconnect();
			continue;
		} else {
			throw PgError(errorText);
		}
	}
}

bool PgConnection::BeginTransaction() {
	m_inTransaction = true;
	return true;
}

bool PgConnection::EndTransaction() {
	m_inTransaction = false;
	return true;
}

bool PgConnection::RollbackTransaction() {
	m_inTransaction = false;
	return true;
}

bool PgConnection::Connect(const char* connectionInfo) {
	m_connection = PQconnectdb(connectionInfo);
	ConnStatusType status = PQstatus(m_connection);
	if (status != CONNECTION_OK) {
		return false;
	}
	PQsetNoticeProcessor(m_connection, notice_processor, this);
	return true;
}

bool PgConnection::Reconnect() {
	if (IsConnected()) {
		Disconnect();
	}
	return Connect(m_connectionInfo.c_str());
}

bool PgConnection::Disconnect() {
	if (m_connection != NULL) {
		PQfinish(m_connection);
		m_connection = NULL;
		return true;
	}
	return false;
}

bool PgConnection::IsConnected() {
	return m_connection != NULL;
}

std::string PgConnection::Encode(const std::string& text) {
	size_t bufferSize;
	char* escapedString = (char*)PQescapeBytea((unsigned char*)text.c_str(), text.length(), &bufferSize);
	std::string result(escapedString);
	PQfreemem(escapedString);
	return result;
}

std::string PgConnection::Decode(const std::string& text) {
	size_t outputSize;
	char* readString = (char *)PQunescapeBytea((const unsigned char *)text.c_str(), &outputSize);
	std::string result;
	if (outputSize != 0) {
		char* buffer = new char[outputSize + 1];
		memcpy(buffer, readString, outputSize);
		buffer[outputSize] = '\0';
		PQfreemem(readString);
		result = buffer;
		delete[] buffer;
	}
	return result;
}

// Blobs

bool PgConnection::IsBlobExists(int oid) {
	int fd = lo_open(m_connection, oid, INV_READ);
	lo_close(m_connection, fd);
	return fd >= 0;
}

int PgConnection::CreateBlob() {
	int oid = lo_creat(m_connection, INV_READ | INV_WRITE);
	if (oid == 0) {
		throw PgError("Can not create blob");
	}
	return oid;
}

int PgConnection::GetBlobContentSize(int oid) {
	int fd = lo_open(m_connection, oid, INV_READ);
	if (fd < 0) {
		throw PgError("Can not open blob for reading");
	}
	if (lo_lseek(m_connection, fd, 0, SEEK_END) < 0) {
		throw PgError("Can not seek in file");
	}
	int fileSize = lo_tell(m_connection, fd);
	if (fileSize < 0) {
		throw PgError("Can not get tell in file");
	}
	lo_close(m_connection, fd);
	return fileSize;
}

void PgConnection::SetBlobContent(int oid, const std::string& s) {
	int fd = lo_open(m_connection, oid, INV_WRITE);
	if (fd < 0) {
		throw PgError("Can not open blob for writing");
	}
	if (lo_write(m_connection, fd, s.c_str(), s.length()) != (int)s.length()) {
		throw PgError("Error while writing to blob");
	}
	lo_close(m_connection, fd);
}

void PgConnection::AddBlobContent(int oid, const std::string& s) {
	int fd = lo_open(m_connection, oid, INV_WRITE);
	if (fd < 0) {
		throw PgError("Can not open blob for writing");
	}
	if (lo_lseek(m_connection, fd, 0, SEEK_END) < 0) {
		throw PgError("Can not seek in file");
	}
	if (lo_write(m_connection, fd, s.c_str(), s.length()) != (int)s.length()) {
		throw PgError("Error while writing to blob");
	}
	lo_close(m_connection, fd);
}

void PgConnection::GetBlobContent(int oid, std::string& content) {
	int fd = lo_open(m_connection, oid, INV_READ);
	if (fd < 0) {
		throw PgError("Can not open large object");
	}
	char s[PG_READ_BLOCK_SIZE];
	int n;
	content = "";
	do {
		n = lo_read(m_connection, fd, s, PG_READ_BLOCK_SIZE);
		if (n < 0) {
			lo_close(m_connection, fd);
			throw PgError("Error while reading from blob");
		}
		// TODO: комментарий про insert
		content.insert(content.length(), s, n);
	} while (n == PG_READ_BLOCK_SIZE);
	lo_close(m_connection, fd);
}