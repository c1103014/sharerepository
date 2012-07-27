#include <Windows.h>
#include <math.h>

#include "MatrixUtility.h"

/**
 * 4x4行列の内積
 * @param l 左行列
 * @param r 右行列
 * @param m 計算結果
 */
VOID dot(FLOAT *l, FLOAT *r, FLOAT *m)
{
}

/**
 * 4x4行列の外積
 * @param l 左行列
 * @param r 右行列
 * @param m 計算結果
 */
VOID cross(FLOAT *l, FLOAT *r, FLOAT *m)
{
}

/**
 * 3成分を持つベクトルの正規化
 * @param v 正規化するベクトル
 * @param n 計算結果
 */
VOID normalize(FLOAT *v, FLOAT *n)
{
}

/**
 * クォータニオンの積
 * @param p 左
 * @param q 右
 * @param r 計算結果
 */
VOID multiquat(FLOAT *p, FLOAT *q, FLOAT *r)
{
	FLOAT pw, px, py, pz;
    FLOAT qw, qx, qy, qz;

    pw = p[3]; px = p[0]; py = p[1]; pz = p[2];
    qw = q[3]; qx = q[0]; qy = q[1]; qz = q[2];

    r[3] = pw * qw - px * qx - py * qy - pz * qz;
    r[0] = pw * qx + px * qw + py * qz - pz * qy;
    r[1] = pw * qy - px * qz + py * qw + pz * qx;
    r[2] = pw * qz + px * qy - py * qx + pz * qw;
}

/**
 * クォータニオンを行列に変換
 * @param q クォータニオン
 * @param m 計算結果(4x4行列)
 */
VOID quat2mat(FLOAT *q, FLOAT *m)
{
	FLOAT qw, qx, qy, qz;
    FLOAT x2, y2, z2;
    FLOAT xy, yz, zx;
    FLOAT wx, wy, wz;

    qw = q[3]; qx = q[0]; qy = q[1]; qz = q[2];

    x2 = 2.0f * qx * qx;
    y2 = 2.0f * qy * qy;
    z2 = 2.0f * qz * qz;

    xy = 2.0f * qx * qy;
    yz = 2.0f * qy * qz;
    zx = 2.0f * qz * qx;
        
    wx = 2.0f * qw * qx;
    wy = 2.0f * qw * qy;
    wz = 2.0f * qw * qz;

    m[0] = 1.0f - y2 - z2;
    m[1] = xy - wz;
    m[2] = zx + wy;
    m[3] = 0.0f;

    m[4] = xy + wz;
    m[5] = 1.0f - z2 - x2;
    m[6] = yz - wx;
    m[7] = 0.0f;

    m[8] = zx - wy;
    m[9] = yz + wx;
    m[10] = 1.0f - x2 - y2;
    m[11] = 0.0f;

    m[12] = m[13] = m[14] = 0.0f;
    m[15] = 1.0f;
}

VOID multimatvec(FLOAT *m, FLOAT *v, FLOAT *r)
{
	r[0] = m[0] * v[0] + m[1] * v[1] + m[2] * v[2];
	r[1] = m[4] * v[0] + m[5] * v[1] + m[6] * v[2];
	r[2] = m[8] * v[0] + m[9] * v[1] + m[10] * v[2];
}

/*
** 球面線形補間 p ← q と r を t で補間したクォータニオン
*/
VOID slerp(FLOAT p[], const FLOAT q[], const FLOAT r[], const FLOAT t)
{
  FLOAT qr = q[0] * r[0] + q[1] * r[1] + q[2] * r[2] + q[3] * r[3];
  FLOAT ss = 1.0 - qr * qr, sp;
  
  if (ss <= 0.0 || (sp = sqrt(ss)) == 0.0) {
    p[0] = q[0];
    p[1] = q[1];
    p[2] = q[2];
    p[3] = q[3];
  }
  else {
    FLOAT ph = acos(qr);
    FLOAT pt = ph * t;
    FLOAT t1 = sin(pt) / sp;
    FLOAT t0 = sin(ph - pt) / sp;
    
    p[0] = q[0] * t0 + r[0] * t1;
    p[1] = q[1] * t0 + r[1] * t1;
    p[2] = q[2] * t0 + r[2] * t1;
    p[3] = q[3] * t0 + r[3] * t1;
  }
}
