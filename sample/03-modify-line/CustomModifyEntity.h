#pragma once
#include "pch.h"
#include <rxregsvc.h>
#include <aced.h>
#include <tchar.h>
#include <dbents.h>
#include <geassign.h>
#include <dbapserv.h>
#include <adscodes.h>

class CustomModifyEntity {
public:
	static Acad::ErrorStatus ChangeColor(AcDbObjectId entId, Adesk::UInt16
		colorIndex);
};