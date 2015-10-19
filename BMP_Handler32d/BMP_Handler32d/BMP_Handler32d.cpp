/**********************************************************
Program: BMP_Handler32d.cpp
Author: Garth Murray
Date: 10/19/2015
Description: This file implements the functions provided by 
the BMP_Handler.h header file, which are intended to read
and write bits in a BMP file in order to store specific 
data.
**********************************************************/

#include "stdafx.h"
#include "BMP_Handler.h"
#include <fstream>
#include <iostream>



//BITMAPFILEHEADER bmpHeader1;
//BITMAPINFOHEADER bmpInfo; 

typedef struct tag_bitmapFile 
{
        WORD    bfType;
		DWORD   bfSize;
        WORD    bfReserved1;
        WORD    bfReserved2;
        DWORD   bfOffBits;
} bitmapFile;


typedef struct tag_bitmapInfo
{
		DWORD      biSize;
        LONG       biWidth;
        LONG       biHeight;
        WORD       biPlanes;
        WORD       biBitCount;
        DWORD      biCompression;
        DWORD      biSizeImage;
        LONG       biXPelsPerMeter;
        LONG       biYPelsPerMeter;
        DWORD      biClrUsed;
        DWORD      biClrImportant;
} bitmapInfo;

bitmapFile bmpHeader;
bitmapInfo bmpInfo; 

BMP_API unsigned char* BMP_Handler::loadBMP(const char* filename, int& width, int& height)
{	
	std::ifstream file(filename, std::ifstream::binary);

	//Checks if file can be opened
	if(!file)
	{
		std::cout << "Failure to open bitmap file.\n";
		return NULL;
	}

	//Reads in the bitmap headers
	file.read((char*)&bmpHeader, sizeof(bitmapFile) - 2);
	file.read((char*)&bmpInfo, sizeof(bitmapInfo) - 2);

	// Check if the file is an actual BMP file
	if(bmpHeader.bfType != 0x4D42)
	{
		std::cout << "File \"" << filename << "\" isn't a bitmap file\n";
		return NULL;
	}

	// Set width and height to the values loaded from the file
	width = (int)bmpInfo.biWidth;
	height = (int)bmpInfo.biHeight;

	//Array that will store altered bits
	unsigned char* pixels = new unsigned char[width*height*4];

	//Reads in RGB values to the pixels array
	file.read((char*)pixels, width*height*4);

	file.close();
	return pixels;
}

BMP_API void BMP_Handler::saveBMP(const char* filename, const unsigned char* RGB_values, int width, int height)
{
	std::ofstream myfile(filename, std::ios::out | std::ios::binary | std::ofstream::trunc);

	//Moves through headers
	myfile.write((const char*)&bmpHeader, sizeof(bitmapFile) - 2);
	myfile.write((const char*)&bmpInfo, sizeof(bitmapInfo) - 2);

	//Writes out altered bits to image
	myfile.write((const char*)RGB_values, 4*width*height);

	myfile.close();
}



