#pragma once

#include <Windows.h>

#define IMG_OK              0x1
#define IMG_ERR_NO_FILE     0x2
#define IMG_ERR_MEM_FAIL    0x4
#define IMG_ERR_BAD_FORMAT  0x8
#define IMG_ERR_UNSUPPORTED 0x40

class TGAImg
 {
  public:
   TGAImg();
   ~TGAImg();
   INT Load(char* szFilename);
   INT GetBPP();
   INT GetWidth();
   INT GetHeight();
   BYTE *GetImg();       // Return a pointer to image data
   BYTE *GetPalette();   // Return a pointer to VGA palette

  private:
   SHORT iWidth,iHeight,iBPP;
   ULONG lImageSize;
   CHAR bEnc;
   BYTE *pImage, *pPalette, *pData;
   
   // Internal workers
   INT ReadHeader();
   INT LoadRawData();
   INT LoadTgaRLEData();
   INT LoadTgaPalette();
   VOID BGRtoRGB();
   VOID FlipImg();
 };
