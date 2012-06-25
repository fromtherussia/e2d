#ifndef CGL_TGA_LOADER_H
#define CGL_TGA_LOADER_H

class TgaLoader {
public:
	TgaLoader(std::istream& inputStream);
	~TgaLoader();
	
	const binary_data_t* GetDataBuffer () const;
	uint GetBufferSize () const;
	uint GetWidth () const;
	uint GetHeight () const;
	uint GetBitsPerPixel () const;

private:
	uint width;
	uint height;
	uint bits;
	binary_data_t* data;

	TgaLoader(const TgaLoader&);
	TgaLoader& operator = (const TgaLoader&);

	bool LoadTga(std::istream& inputStream);
	void AllocateData (uint countBytes);
	void FreeData ();
};

#endif