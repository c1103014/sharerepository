#include <cstdlib>

#include "ImageInfo.h"
#include "bitmap24.h"

ImageInfo::ImageInfo(void)
{
	m_ImageData = NULL;
	m_nWidth = 0;
	m_nHeight = 0;
	m_nDepth = 0;
}

ImageInfo::~ImageInfo(void)
{
	if (m_ImageData != NULL) {
		delete [] m_ImageData;
	}
}

/**
 * �摜�t�@�C����ǂݍ��݂܂��B
 * @param szImagePath 24bit�r�b�g�}�b�v�����ǂ߂܂���
 */
void ImageInfo::load(string szImagePath)
{
	CBitmap24 bmp;
	bmp.Load(szImagePath);
	m_nWidth = bmp.GetWidth();
	m_nHeight = bmp.GetHeight();
	m_nDepth = 24;
	m_ImageData = new BYTE[m_nWidth * m_nHeight * (m_nDepth / 8)];
	memcpy(m_ImageData, bmp.GetPixelAddress(0, 0), sizeof(BYTE) * m_nWidth * m_nHeight * (m_nDepth / 8));
	bmp.Delete();
}

INT ImageInfo::getWidth(void)
{
	return m_nWidth;
}

INT ImageInfo::getHeight(void)
{
	return m_nHeight;
}

INT ImageInfo::getDepth(void)
{
	return m_nDepth;
}

BYTE *ImageInfo::getImageData(void)
{
	return m_ImageData;
}
