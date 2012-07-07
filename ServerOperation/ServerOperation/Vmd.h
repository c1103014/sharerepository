#pragma once

#include <Windows.h>

typedef struct tagVMDHeader {
	char szVersion[30];		// VMDバージョン
	char szModelName[20];	// モデル名
} VMDHEADER;

typedef struct tagVMDBoneFrame {
	char szName[15];		// ボーン名
	DWORD dwFrameNo;		// フレーム番号
	float fPosX;			// x軸
	float fPosY;			// y軸
	float fPosZ;			// z軸
	float fQuaternionX;		// クォータニオンx回転
	float fQuaternionY;		// クォータニオンy回転
	float fQuaternionZ;		// クォータニオンz回転
	float fQuaternionW;		// クォータニオンw回転
	char bezier[64];		// 補間(S字曲線？)
} VMDBONEFRAME;

typedef struct tagVMDMorphFrame {
	char szName[15];		// 表情名
	DWORD dwFrameNo;		// フレーム番号
	float fValue;			// 0 or 1 ← 表情のon/offかな？
} VMDMorphFrame;

typedef struct tagVMDCameraFrame {
	DWORD dwFrameNo;		// フレーム番号
	float fDistance;		// 目標点とカメラの距離(目標点がカメラ前面でマイナス)
	float fDestX;			// 目標点x座標
	float fDestY;			// 目標点y座標
	float fDestZ;			// 目標点z座標
	float fRadX;			// カメラx軸回転(rad) (MMD数値入力のマイナス値)
	float fRadY;			// カメラy軸回転(rad)
	float fRadZ;			// カメラz軸回転(rad)
	char bezier[24];		// 補間
	DWORD dwAngle;			// 視野角(deg)
	char parspective;		// パースペクティブ(0:on 1:off)
} VMDCameraFrame;

typedef struct tagVMDLightFrame {
	DWORD dwFrameNo;		// フレーム番号
	float fColorR;			// 照明色赤(MMD入力値を256で割った値)
	float fColorG;			// 照明色緑(MMD入力値を256で割った値)
	float fColorB;			// 照明色青(MMD入力値を256で割った値)
	float fPosX;			// 照明x座標(MMD入力値)
	float fPosY;			// 照明y座標(MMD入力値)
	float fPosZ;			// 照明z座標(MMD入力値)
} VMDLightFrame;

typedef struct tagVMDSelfShadowFrame {
	DWORD dwFrameNo;		// フレーム番号
	char cType;				// セルフシャドウ種類(0:OFF, 1:model1, 2:model2)
	float fDistance;		// シャドウ距離(MMD入力値xを0.1-x/100000とした値)
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
