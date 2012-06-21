#include <Windows.h>
#include <cstdio>
#include <cstring>

#include "TgaLoader.h"

CTgaLoader::CTgaLoader(void) {
	m_pTga = NULL;
}
CTgaLoader::~CTgaLoader(void) {
	Delete();
}

INT CTgaLoader::Load(char *filename)
{
	// tgaファイル読み込み用(ファイルポインタ的な存在)
	TGA *pTga;

	// tgaファイルオープン
	pTga = TGAOpen(filename, "r");
	if (pTga == NULL) {
		return 0;
	}

	// tgaファイル読み込み？
	TGAData tgaData;
	memset(&tgaData, 0, sizeof(TGAData));
	tgaData.flags = TGA_IMAGE_ID | TGA_IMAGE_DATA | TGA_RGB;
	TGAReadImage(pTga, &tgaData);
	m_pTga = pTga;
	m_byDepth = pTga->hdr.depth;
	m_wWidth = pTga->hdr.width;
	m_wHeight = pTga->hdr.height;
	m_pbyImageData = tgaData.img_data;
	flipVertical();
	return 1;
}

BYTE CTgaLoader::getDepth(void)
{
	return m_byDepth;
}

BYTE *CTgaLoader::getImageData(void)
{
	return m_pbyImageData;
}

WORD CTgaLoader::getWidth(void)
{
	return m_wWidth;
}

WORD CTgaLoader::getHeight(void)
{
	return m_wHeight;
}

VOID CTgaLoader::Delete(void)
{
	if (m_pTga != NULL) {
		TGAClose(m_pTga);
		m_pTga = NULL;
	}
}

VOID CTgaLoader::flipVertical(void)
{
	BYTE *ptr = m_pbyImageData;
	BYTE tmp;
	INT width;
	if (getDepth() == 24) {
		width = getWidth() * 3;
	} else {
		width = getWidth() * 4;
	}
	for (INT i = 0; i < getHeight() / 2; i++) {
		for (INT j = 0; j < width; j++) {
			tmp = ptr[i * width + j];
			ptr[i * width + j] = ptr[(getHeight() - i - 1) * width + j];
			ptr[(getHeight() - i - 1) * width + j] = tmp;
		}
	}
}

VOID CTgaLoader::flipHorizontal(void)
{
	BYTE *ptr = m_pbyImageData;
	BYTE tmp;
	INT width;
	INT bit;
	if (getDepth() == 24) {
		width = getWidth() * 3;
		bit = 3;
	} else {
		width = getWidth() * 4;
		bit = 4;
	}

	for (INT i = 0; i < getHeight(); i++) {
		for (INT j = 0; j < width / 2; j+=bit) {
			tmp = ptr[i * width + j];
			ptr[i * width + j] = ptr[i * width + width - bit - j];
			ptr[i * width + width - bit - j] = tmp;
			tmp = ptr[i * width + j + 1];
			ptr[i * width + j + 1] = ptr[i * width + width - bit - j + 1];
			ptr[i * width + width - bit - j + 1] = tmp;
			tmp = ptr[i * width + j + 2];
			ptr[i * width + j + 2] = ptr[i * width + width - bit - j + 2];
			ptr[i * width + width - bit - j + 2] = tmp;
			if (bit == 4) {
				tmp = ptr[i * width + j + 3];
				ptr[i * width + j + 3] = ptr[i * width + width - bit - j + 3];
				ptr[i * width + width - bit - j + 3] = tmp;
			}
		}
	}
}
