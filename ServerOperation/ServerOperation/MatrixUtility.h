#pragma once

#include <Windows.h>

VOID dot(FLOAT *l, FLOAT *r, FLOAT *m);
VOID cross(FLOAT *l, FLOAT *r, FLOAT *m);
VOID normalize(FLOAT *v, FLOAT *n);
VOID multiquat(FLOAT *p, FLOAT *q, FLOAT *r);
VOID quat2mat(FLOAT *q, FLOAT *m);
VOID multimatvec(FLOAT *m, FLOAT *v, FLOAT *r);
VOID slerp(FLOAT p[], const FLOAT q[], const FLOAT r[], const FLOAT t);
