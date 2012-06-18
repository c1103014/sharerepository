#pragma once

#include <iostream>
#include <Windows.h>

using namespace std;

class ImageInfo
{
public:
	ImageInfo(void);
	virtual ~ImageInfo(void);
	void load(string szImagePath);
	INT getWidth(void);
	INT getHeight(void);
	INT getDepth(void);
	BYTE *getImageData(void);
private:
	BYTE *m_ImageData;
	INT m_nWidth;
	INT m_nHeight;
	INT m_nDepth;
};
