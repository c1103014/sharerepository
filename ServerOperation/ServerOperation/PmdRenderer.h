#pragma once

#include <Windows.h>
#include <string>

#include "Pmd.h"

using namespace std;

class CPmdRenderer
{
public:
	CPmdRenderer(VOID);
	virtual ~CPmdRenderer(VOID);
	VOID load(string filename);
	VOID render(VOID);
private:
	CPmd pmd;
};
