#include <Windows.h>

#include "MatrixUtility.h"

/**
 * 4x4�s��̓���
 * @param l ���s��
 * @param r �E�s��
 * @param m �v�Z����
 */
VOID dot(FLOAT *l, FLOAT *r, FLOAT *m)
{
}

/**
 * 4x4�s��̊O��
 * @param l ���s��
 * @param r �E�s��
 * @param m �v�Z����
 */
VOID cross(FLOAT *l, FLOAT *r, FLOAT *m)
{
}

/**
 * 3���������x�N�g���̐��K��
 * @param v ���K������x�N�g��
 * @param n �v�Z����
 */
VOID normalize(FLOAT *v, FLOAT *n)
{
}

/**
 * �N�H�[�^�j�I���̐�
 * @param p ��
 * @param q �E
 * @param r �v�Z����
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
 * �N�H�[�^�j�I�����s��ɕϊ�
 * @param q �N�H�[�^�j�I��
 * @param m �v�Z����(4x4�s��)
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
