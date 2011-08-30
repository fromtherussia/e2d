#include "Types.h"

#include "TgaLoader.h"

TgaLoader::TgaLoader (std::istream& inputStream)
{
	data = NULL;
	if(!LoadTga(inputStream))
	{
		throw std::invalid_argument("loading failed");
	}
}

TgaLoader::~TgaLoader ()
{
	FreeData();
}

const binary_data_t* TgaLoader::GetDataBuffer () const
{
	return data;
}

uint TgaLoader::GetWidth () const
{
	return width;
}

uint TgaLoader::GetHeight () const
{
	return height;
}

uint TgaLoader::GetBitsPerPixel () const
{
	return bits;
}

uint TgaLoader::GetBufferSize() const
{
	return width * height * (bits >> 3);
}

bool TgaLoader::LoadTga (std::istream& inputStream)
{
	try
	{
		// ������ � �������� ���������
		static unsigned char refHeader[12] = {0,0,2,0,0,0,0,0,0,0,0,0};
		unsigned char header[12];
		inputStream.read((char *)(header), 12);
		if(memcmp(refHeader, header, 12) !=0)
		{
			return false;
		}

		// �������� ������, ������ � ���������
		unsigned char attributes[6];
		inputStream.read((char *)(attributes), 6);
		if(attributes[4] != 24 && attributes[4] != 32)
		{
			return false;
		}
		width  = (uint)attributes[1] * 256 + attributes[0];			
		height = (uint)attributes[3] * 256 + attributes[2];			
		bits = attributes[4];
	
		// �������� ������
		uint channels = bits >> 3;
		uint imageSize = width * height * channels;
		AllocateData(imageSize);
		inputStream.read((char *)(data), imageSize);
		
		// ������������������ ������ � RGB(A)
		for(uint i = 0; i < imageSize; i += channels)
		{
			std::swap(data[i], data[i+2]);
		}
	}
	catch(...)
	{
		// ���� � ������ ���-�� �� ���
		FreeData();
		return false;
	}
	
	return true;
}

void TgaLoader::AllocateData (uint countBytes)
{
	data = new binary_data_t [countBytes];
}

void TgaLoader::FreeData ()
{
	delete data;
	data = NULL;
}