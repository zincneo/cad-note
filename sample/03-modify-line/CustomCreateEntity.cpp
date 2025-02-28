#include "pch.h"
#include "CustomCreateEntity.h"

AcDbObjectId CustomCreateEntity::CreateLine() {
	// 创建直线对象
	AcGePoint3d startPoint(0, 0, 0), endPoint(100, 100, 0);
	AcDbLine* pLine = new AcDbLine(startPoint, endPoint);

	// 获取块表指针
	AcDbBlockTable* pBlockTable;
	acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead);

	// 获取指向块表记录的指针
	AcDbBlockTableRecord* pBlockTableRecord;
	pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, AcDb::kForWrite);

	// 将直线对象写入到块表记录中
	AcDbObjectId lineId;
	// 这里对象已经将内存移交到数据库中，请不要delete
	pBlockTableRecord->appendAcDbEntity(lineId, pLine);

	// 关闭打开的各数据库对象
	pBlockTable->close();
	pBlockTableRecord->close();
	pLine->close();

	acedPrompt(_T("\n绘制直线完成"));
	return lineId;
}