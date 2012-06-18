#include "bitmap24.h"

// ============================================================================
// �f�t�H���g�R���X�g���N�^
// ============================================================================
CBitmap24::CBitmap24()
{
	m_OutColor = COLOR24_WHITE;
	m_Buffer = NULL;
	Resize(8, 8);
}

// ============================================================================
// �R���X�g���N�^
// @param width, height �T�C�Y
// ============================================================================
CBitmap24::CBitmap24(int width, int height)
{
	m_OutColor = COLOR24_WHITE;
	m_Buffer = NULL;
	Resize(width, height);
}

// ============================================================================
// �f�X�g���N�^
// ============================================================================
CBitmap24::~CBitmap24(void)
{
	Delete();
}

// ============================================================================
// �o�b�t�@�̉��
// ============================================================================
void CBitmap24::Delete()
{
	if(m_Buffer != NULL)
	{
		delete[] (BYTE *)m_Buffer;
		m_Buffer = NULL;
	}
}

// ============================================================================
// �T�C�Y�ύX
// @param width, height �T�C�Y
// ============================================================================
void CBitmap24::Resize(int width, int height)
{
	Delete();

	m_Width = width;
	m_Height = height;
	m_Buffer = new BYTE[sizeof(COLOR24) * m_Width * m_Height];
	memset(m_Buffer, 0x00, sizeof(COLOR24) * m_Width * m_Height);
	InitHeader();
}

// ============================================================================
// �w�b�_���E�o�b�t�@���R�s�[����
// @param �R�s�[��
// ============================================================================
void CBitmap24::Copy(CBitmap24 *obj)
{
	// �w�b�_
	m_Header = *obj->GetHeader();
	// �o�b�t�@
	m_Buffer = NULL;
	Resize(obj->GetWidth(), obj->GetHeight());
	size_t memsize = sizeof(COLOR24) * obj->GetWidth() * obj->GetHeight();
	memcpy(m_Buffer, obj->GetBuffer(), memsize);
	// �̈�O�̐F
	m_OutColor = obj->GetOutColor();
}

// ============================================================================
// �s�N�Z���̃A�h���X��Ԃ�
// @param x, y ���W
// ============================================================================
void *CBitmap24::GetPixelAddress(int x, int y)
{
	if(x < 0 || m_Width <= x || y < 0 || m_Height <= y)
	{
		return NULL;
	}
	return GetPixelAddressNC(x, y);
}

// ============================================================================
// �s�N�Z���ɐF��ݒ肷��
// @param x, y ���W
// @param color �F
// ============================================================================
void CBitmap24::SetPixel(int x, int y, COLOR24 *color)
{
	COLOR24 *ptr = (COLOR24 *)GetPixelAddress(x, y);
	if(ptr == NULL) return;
	ptr->r = color->r;
	ptr->g = color->g;
	ptr->b = color->b;
}

// ============================================================================
// �s�N�Z���̐F���擾����
// @param x, y ���W
// @return �F
// ============================================================================
COLOR24 CBitmap24::GetPixel(int x, int y)
{
	COLOR24 *ptr = (COLOR24 *)GetPixelAddress(x, y);
	if(ptr == NULL) return m_OutColor;
	return *ptr;
}

// ============================================================================
// �w�b�_��񏉊���
// ============================================================================
void CBitmap24::InitHeader()
{
	MY_BITMAP *header = this->GetHeader();
	header->bmf.bfType = char('B') | (char('M') << 8);
	header->bmf.bfSize = 14 + sizeof(BITMAPINFOHEADER) + (this->GetWidth() * this->GetHeight() * 3);
	header->bmf.bfReserved1 = 0;
	header->bmf.bfReserved2 = 0;
	header->bmf.bfOffBits = 14 + sizeof(BITMAPINFOHEADER);

	header->bmi.biSize = sizeof(BITMAPINFOHEADER);
	header->bmi.biWidth = this->GetWidth();
	header->bmi.biHeight = this->GetHeight();
	header->bmi.biPlanes = 1;
	header->bmi.biBitCount = 24;
	header->bmi.biCompression = BI_RGB;
	header->bmi.biClrImportant = 0;
	header->bmi.biSizeImage = 0;
	header->bmi.biXPelsPerMeter = 0;
	header->bmi.biYPelsPerMeter = 0;
	header->bmi.biClrUsed = 0;
	header->bmi.biClrImportant = 0;
}

// ============================================================================
// �r�b�g�}�b�v�ǂݍ���
// @param filename �t�@�C����
// ============================================================================
void CBitmap24::Load(string filename)
{
	ifstream ifs(filename.c_str(), ios::binary);
	if(!ifs)
	{
		return;
	}

	MY_BITMAP *header = this->GetHeader();
	/* header infomation */
	ifs.read((char*)&header->bmf.bfType, sizeof(header->bmf.bfType));
	ifs.read((char*)&header->bmf.bfSize, sizeof(header->bmf.bfSize));
	ifs.read((char*)&header->bmf.bfReserved1, sizeof(header->bmf.bfReserved1));
	ifs.read((char*)&header->bmf.bfReserved2, sizeof(header->bmf.bfReserved2));
	ifs.read((char*)&header->bmf.bfOffBits, sizeof(header->bmf.bfOffBits));

	ifs.read((char*)&header->bmi.biSize, sizeof(header->bmi.biSize));
	ifs.read((char*)&header->bmi.biWidth, sizeof(header->bmi.biWidth));
	ifs.read((char*)&header->bmi.biHeight, sizeof(header->bmi.biHeight));
	ifs.read((char*)&header->bmi.biPlanes, sizeof(header->bmi.biPlanes));
	ifs.read((char*)&header->bmi.biBitCount, sizeof(header->bmi.biBitCount));
	ifs.read((char*)&header->bmi.biCompression, sizeof(header->bmi.biCompression));
	ifs.read((char*)&header->bmi.biSizeImage, sizeof(header->bmi.biSizeImage));
	ifs.read((char*)&header->bmi.biXPelsPerMeter, sizeof(header->bmi.biXPelsPerMeter));
	ifs.read((char*)&header->bmi.biYPelsPerMeter, sizeof(header->bmi.biYPelsPerMeter));
	ifs.read((char*)&header->bmi.biClrUsed, sizeof(header->bmi.biClrUsed));
	ifs.read((char*)&header->bmi.biClrImportant, sizeof(header->bmi.biClrImportant));

	this->SetHeader(header);
	this->Resize(header->bmi.biWidth, header->bmi.biHeight);

	// Pixel
	BYTE *ptr = (BYTE *)this->GetPixelAddress(0, 0);
	int padding = 4 - (this->GetWidth() * sizeof(COLOR24) % 4); // �S�̔{���Ńp�f�B���O
	COLOR24 padColor = {0, 0, 0};
	for(int j = 0; j < this->GetHeight(); j++)
	{
		for(int i = 0; i < this->GetWidth(); i++)
		{
			for(int k = 2; k > -1; k--)
			{
				ifs.read((char *)&ptr[k], sizeof(BYTE));

			}
			ptr += 3;
		}
		if(padding != 4)
		{
			for(int i = 0; i < padding; i++)
			{
				BYTE tmp; // �̂ĕϐ�
				// �p�f�B���O�i��ǂ݁j
				ifs.read((char *)&tmp, sizeof(BYTE));
			}
		}
	}
	ifs.close();

	// MMD�p�ɕҏW(�����A�㉺�t�ɂȂ��Ă�)
	ptr = (BYTE *)this->GetPixelAddress(0, 0);
	BYTE tmp;
	for (int i = 0; i < this->GetHeight() / 2; i++) {
		for (int j = 0; j < this->GetWidth() * 3; j++) {
			tmp = ptr[i * this->GetWidth() * 3 + j];
			ptr[i * this->GetWidth() * 3 + j] = ptr[(this->GetHeight() - i - 1) * this->GetWidth() * 3 + j];
			ptr[(this->GetHeight() - i - 1) * this->GetWidth() * 3 + j] = tmp;
		}
	}
}

// ============================================================================
// �r�b�g�}�b�v��������
// @param filename �t�@�C����
// ============================================================================
void CBitmap24::Save(string filename)
{
	ofstream ofs(filename.c_str(), ios::binary);
    if(!ofs)
	{
		return;
	}

	MY_BITMAP *header = this->GetHeader();
	/* header infomation */
	ofs.write((char*)&header->bmf.bfType, sizeof(header->bmf.bfType));
	ofs.write((char*)&header->bmf.bfSize, sizeof(header->bmf.bfSize));
	ofs.write((char*)&header->bmf.bfReserved1, sizeof(header->bmf.bfReserved1));
	ofs.write((char*)&header->bmf.bfReserved2, sizeof(header->bmf.bfReserved2));
	ofs.write((char*)&header->bmf.bfOffBits, sizeof(header->bmf.bfOffBits));

	ofs.write((char*)&header->bmi.biSize, sizeof(header->bmi.biSize));
	ofs.write((char*)&header->bmi.biWidth, sizeof(header->bmi.biWidth));
	ofs.write((char*)&header->bmi.biHeight, sizeof(header->bmi.biHeight));
	ofs.write((char*)&header->bmi.biPlanes, sizeof(header->bmi.biPlanes));
	ofs.write((char*)&header->bmi.biBitCount, sizeof(header->bmi.biBitCount));
	ofs.write((char*)&header->bmi.biCompression, sizeof(header->bmi.biCompression));
	ofs.write((char*)&header->bmi.biSizeImage, sizeof(header->bmi.biSizeImage));
	ofs.write((char*)&header->bmi.biXPelsPerMeter, sizeof(header->bmi.biXPelsPerMeter));
	ofs.write((char*)&header->bmi.biYPelsPerMeter, sizeof(header->bmi.biYPelsPerMeter));
	ofs.write((char*)&header->bmi.biClrUsed, sizeof(header->bmi.biClrUsed));
	ofs.write((char*)&header->bmi.biClrImportant, sizeof(header->bmi.biClrImportant));

	// Pixel
	BYTE *ptr = (BYTE *)this->GetPixelAddress(0, 0);
	int padding = 4 - (this->GetWidth() * sizeof(COLOR24) % 4); // �S�̔{���Ńp�f�B���O
	for(int j = 0; j < this->GetHeight(); j++)
	{
		for(int i = 0; i < this->GetWidth(); i++)
		{
			for(int k = 2; k > -1; k--)
			{
				ofs.write((char *)&ptr[k], sizeof(BYTE));
			}
			ptr += 3;
		}
		if(padding != 4)
		{
			for(int i = 0; i < padding; i++)
			{
				// �p�f�B���O
				ofs.write((char *)&COLOR24_WHITE, sizeof(BYTE));
			}
		}
	}
	ofs.close();
}
