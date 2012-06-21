#pragma once

#include <Windows.h>
#include <tga.h>

class CTgaLoader {
private:
	TGA *m_pTga;
	BYTE m_byDepth;			// 24:RGB 32:RGBA
	BYTE *m_pbyImageData;
	WORD m_wWidth;
	WORD m_wHeight;
public:
	CTgaLoader(void);
	virtual ~CTgaLoader(void);
	INT Load(char *filename);
	BYTE getDepth(void);
	BYTE *getImageData(void);
	WORD getWidth(void);
	WORD getHeight(void);
	VOID Delete(void);
	VOID flipVertical(void);
	VOID flipHorizontal(void);
};
