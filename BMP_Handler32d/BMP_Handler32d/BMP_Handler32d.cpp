/**********************************************************
Program: BMP_Handler32d.cpp
Author: Garth Murray
Date: 10/18/2015
Description: This file implements the functions provided by 
the BMP_Handler.h header file, which are intended to read
and write bits in a BMP file in order to store specific 
data.
**********************************************************/

#include "stdafx.h"
#include "BMP_Handler.h"
#include <fstream>
#include <iostream>



BITMAPFILEHEADER bmpHeader;
BITMAPINFOHEADER bmpInfo; 

BMP_API unsigned char* BMP_Handler::loadBMP(const char* filename, int& width, int& height)
{	
	std::ifstream file(filename, std::ifstream::binary);
	if(!file)
	{
		std::cout << "Failure to open bitmap file.\n";
		return NULL;
	}

	file.read((char*)&bmpHeader, sizeof(BITMAPFILEHEADER));
	file.read((char*)&bmpInfo, sizeof(BITMAPINFOHEADER));

	// Set width and height to the values loaded from the file
	width = (int)bmpInfo.biWidth;
	height = (int)bmpInfo.biHeight;

	unsigned char* pixels = new unsigned char[bmpHeader.bfSize];

	file.read((char*)pixels, bmpHeader.bfSize);

	file.close();
	return pixels;
}

BMP_API void BMP_Handler::saveBMP(const char* filename, const unsigned char* RGB_values, int width, int height)
{
	std::ofstream myfile(filename, std::ios::out | std::ios::binary | std::ofstream::trunc);

	myfile.write((const char*)&bmpHeader, sizeof(BITMAPFILEHEADER));
	myfile.write((const char*)&bmpInfo, sizeof(BITMAPINFOHEADER));

	myfile.write((const char*)RGB_values, 3*width*height);

	myfile.close();
}


