#include "pch.h"
#include <rxregsvc.h>
#include <aced.h>
#include <tchar.h>
#include <dbents.h>
#include <geassign.h>
#include <dbapserv.h>
#include <adscodes.h>
#include "CustomCreateEntity.h"
#include "CustomModifyEntity.h"

void initApp();
void unloadApp();
void ChangeColor();

extern "C" AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
	switch (msg)
	{
	case AcRx::kInitAppMsg:
		acrxDynamicLinker->unlockApplication(pkt);
		acrxRegisterAppMDIAware(pkt);
		initApp();
		break;
	case AcRx::kUnloadAppMsg:
		unloadApp();
		break;
	default:
		break;
	}

	return AcRx::kRetOK;
}

void initApp() {
    acedRegCmds->addCommand(_T("CAD2018PLUGIN"), _T("MYREDLINE"), _T("MYREDLINE"), ACRX_CMD_MODAL, ChangeColor);
}

void unloadApp() {
	acedRegCmds->removeGroup(_T("CAD2018PLUGIN"));
}

void ChangeColor() {
	AcDbObjectId lineId;
	lineId = CustomCreateEntity::CreateLine();
	CustomModifyEntity::ChangeColor(lineId, 1);
}