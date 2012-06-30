#include <Windows.h>

#include "ImageInfo.h"
#include "bitmap24.h"
#include "TgaImg.h"

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
 * 画像ファイルを読み込みます。
 * @param szImagePath 24bitビットマップしか読めません
 */
VOID ImageInfo::load(string szImagePath)
{
	if (m_ImageData != NULL) {
		delete [] m_ImageData;
		m_ImageData = NULL;
	}
	string szBmpExt("bmp");
	INT nPos = static_cast<INT>(szImagePath.rfind(szBmpExt, szImagePath.length() - 1));
	if (nPos == szImagePath.length() - szBmpExt.length()) {
		CBitmap24 bmp;
		bmp.Load(szImagePath);
		m_nWidth = bmp.GetWidth();
		m_nHeight = bmp.GetHeight();
		m_nDepth = 24;
		m_ImageData = new BYTE[m_nWidth * m_nHeight * (m_nDepth / 8)];
		memcpy(m_ImageData, bmp.GetPixelAddress(0, 0), sizeof(BYTE) * m_nWidth * m_nHeight * (m_nDepth / 8));
		bmp.Delete();
	}
	string szTgaExt("tga");
	nPos = static_cast<INT>(szImagePath.rfind(szTgaExt, szImagePath.length() - 1));
	if (nPos == szImagePath.length() - szTgaExt.length()) {
		TGAImg tga;
		tga.Load(const_cast<char *>(szImagePath.c_str()));
		m_nWidth = tga.GetWidth();
		m_nHeight = tga.GetHeight();
		m_nDepth = tga.GetBPP();
		m_ImageData = new BYTE[m_nWidth * m_nHeight * (m_nDepth / 8)];
		memcpy(m_ImageData, tga.GetImg(), sizeof(BYTE) * m_nWidth * m_nHeight * (m_nDepth / 8));
	}
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
