#ifndef PG_PG_ACCESS_H
#define PG_PG_ACCESS_H

#define PG_READ_BLOCK_SIZE 8096

class PgError: public std::runtime_error {
	std::string m_what;
public:
	PgError(const std::string& what);
	PgError(const PgError&);
	PgError& operator = (const PgError&);
	virtual ~PgError();
	virtual const char* what() const;
};

class PgConnection;

class PgResult {
	friend class PgConnection;
public:
	enum FieldType {
		ftUnknown = 0,
		ftBool = 1,
		ftChar = 2,
		ftInt = 3,
		ftFloat = 4,
		ftDate = 5
	};
public:
	~PgResult();
	int NumRows();
	int NumCols();
	int GetFieldNum(const char* fieldName);
	bool HasNext();
	bool Next();
	FieldType GetFieldType(int fieldNo);
	std::string GetString(int fieldNo);
	bool GetBoolean(int fieldNo);
	int GetInteger(int fieldNo);
	double GetDouble(int fieldNo);
private:
	int m_tuplesCount;
	int m_tupleNo;
	PGresult* m_result;
	PgConnection* m_pConnection;
	PgResult(PgConnection* connection, PGresult* result);
};

class PgConnection {
public:
	PgConnection(const char* connectionInfo);
	~PgConnection();
	bool Connect(const char* connectionInfo);
	bool Reconnect();
	bool Disconnect();
	bool IsConnected();
	bool BeginTransaction();
	bool EndTransaction();
	bool RollbackTransaction();
	PgResult Select(const std::string&, ...);
	bool Update(const std::string&, ...);
	// Blob
	int CreateBlob();
	bool IsBlobExists(int id);
	int GetBlobContentSize(int id);
	void AddBlobContent(int id, const std::string& s);
	void SetBlobContent(int id, const std::string& s);
	void GetBlobContent(int id, std::string& content);
private:
	friend class PgResult;
	PGconn* m_connection;
	bool m_inTransaction;
	std::string m_connectionInfo;
	std::string Encode(const std::string& s);
	std::string Decode(const std::string& s);
	int CountSpecifiers(const std::string& query);
	bool MakeQuery(const std::string& query, va_list listArgs, std::string& result);
	void AddString(std::string& query, const char* s);
	void AddInteger(std::string& query, int i);
	void AddBoolean(std::string& query, bool b);
	void AddDouble(std::string& query, double d);
};

#endif