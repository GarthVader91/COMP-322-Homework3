#pragma once

#define BMPEXPORTS

#ifdef BMPEXPORTS
#define BMP_API __declspec(dllexport)
#else
#define BMP_API __declspec(dllimport)
#endif

class BMP_Handler {
public:
	static BMP_API unsigned char* loadBMP(const char*, int&, int&);

	static BMP_API void saveBMP(const char*, const unsigned char*, int, int);
};