#include "pch.h"
#include "CustomModifyEntity.h"

Acad::ErrorStatus CustomModifyEntity::ChangeColor(AcDbObjectId entId, Adesk::UInt16
	colorIndex) {
	AcDbEntity* pEntity;
	acdbOpenObject(pEntity, entId, AcDb::kForWrite);
	pEntity->setColorIndex(colorIndex);
	return Acad::eOk;
}