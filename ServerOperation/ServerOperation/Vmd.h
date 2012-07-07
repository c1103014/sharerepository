#pragma once

#include <Windows.h>

typedef struct tagVMDHeader {
	char szVersion[30];		// VMD�o�[�W����
	char szModelName[20];	// ���f����
} VMDHEADER;

typedef struct tagVMDBoneFrame {
	char szName[15];		// �{�[����
	DWORD dwFrameNo;		// �t���[���ԍ�
	float fPosX;			// x��
	float fPosY;			// y��
	float fPosZ;			// z��
	float fQuaternionX;		// �N�H�[�^�j�I��x��]
	float fQuaternionY;		// �N�H�[�^�j�I��y��]
	float fQuaternionZ;		// �N�H�[�^�j�I��z��]
	float fQuaternionW;		// �N�H�[�^�j�I��w��]
	char bezier[64];		// ���(S���Ȑ��H)
} VMDBONEFRAME;

typedef struct tagVMDMorphFrame {
	char szName[15];		// �\�
	DWORD dwFrameNo;		// �t���[���ԍ�
	float fValue;			// 0 or 1 �� �\���on/off���ȁH
} VMDMorphFrame;

typedef struct tagVMDCameraFrame {
	DWORD dwFrameNo;		// �t���[���ԍ�
	float fDistance;		// �ڕW�_�ƃJ�����̋���(�ڕW�_���J�����O�ʂŃ}�C�i�X)
	float fDestX;			// �ڕW�_x���W
	float fDestY;			// �ڕW�_y���W
	float fDestZ;			// �ڕW�_z���W
	float fRadX;			// �J����x����](rad) (MMD���l���͂̃}�C�i�X�l)
	float fRadY;			// �J����y����](rad)
	float fRadZ;			// �J����z����](rad)
	char bezier[24];		// ���
	DWORD dwAngle;			// ����p(deg)
	char parspective;		// �p�[�X�y�N�e�B�u(0:on 1:off)
} VMDCameraFrame;

typedef struct tagVMDLightFrame {
	DWORD dwFrameNo;		// �t���[���ԍ�
	float fColorR;			// �Ɩ��F��(MMD���͒l��256�Ŋ������l)
	float fColorG;			// �Ɩ��F��(MMD���͒l��256�Ŋ������l)
	float fColorB;			// �Ɩ��F��(MMD���͒l��256�Ŋ������l)
	float fPosX;			// �Ɩ�x���W(MMD���͒l)
	float fPosY;			// �Ɩ�y���W(MMD���͒l)
	float fPosZ;			// �Ɩ�z���W(MMD���͒l)
} VMDLightFrame;

typedef struct tagVMDSelfShadowFrame {
	DWORD dwFrameNo;		// �t���[���ԍ�
	char cType;				// �Z���t�V���h�E���(0:OFF, 1:model1, 2:model2)
	float fDistance;		// �V���h�E����(MMD���͒lx��0.1-x/100000�Ƃ����l)
} VMDSelfShadowFrame;

class CVmd {
private:
public:
	VMDHEADER mHeader;
	DWORD mdwBoneFrameCount;
	VMDBONEFRAME *mlpBoneFrame;

	CVmd(void);
	virtual ~CVmd(void);
	int load(char *szVMDFileName);
	void free(void);
};
