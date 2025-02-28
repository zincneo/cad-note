#include "pch.h"
#include "CustomCreateEntity.h"

AcDbObjectId CustomCreateEntity::CreateLine() {
	// ����ֱ�߶���
	AcGePoint3d startPoint(0, 0, 0), endPoint(100, 100, 0);
	AcDbLine* pLine = new AcDbLine(startPoint, endPoint);

	// ��ȡ���ָ��
	AcDbBlockTable* pBlockTable;
	acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead);

	// ��ȡָ�����¼��ָ��
	AcDbBlockTableRecord* pBlockTableRecord;
	pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, AcDb::kForWrite);

	// ��ֱ�߶���д�뵽����¼��
	AcDbObjectId lineId;
	// ��������Ѿ����ڴ��ƽ������ݿ��У��벻Ҫdelete
	pBlockTableRecord->appendAcDbEntity(lineId, pLine);

	// �رմ򿪵ĸ����ݿ����
	pBlockTable->close();
	pBlockTableRecord->close();
	pLine->close();

	acedPrompt(_T("\n����ֱ�����"));
	return lineId;
}