# CAD直线

## 目标

- 创建一条固定起点终点的直线
- start(0, 0, 0) -> end(100, 100, 0)

## 思路

- dwg文件本身就可以看作一个数据库
- 创建一条固定的直线就是往数据库对应的表(Table)中添加一条记录(Record)
- 图形实体包含在块表AcDbBlockTable中
- 创建的流程
  1. 确定要创建对象的图形数据库
  2. 获得图形数据库的块表
  3. 获得一个存储实体的块表记录，所有模型空间的实体都存储在模型空间的特定记
录中
  4. 创建实体类的一个对象，将该对象附加到特定的块表记录中

## 代码注意要点

### 创建数据库中的直线对象

```cpp
AcGePoint3d ptStart(0, 0, 0); 
AcGePoint3d ptEnd(100, 100, 0); 
AcDbLine *pLine = new AcDbLine(ptStart, ptEnd);
```

- AcGe这个图形库下有很多基本的图形类，这里用到3维的点类AcGePoint3d
- AcDbLine是数据库下表示线的类
- 注意在AutoCAD的机制下，只能使用new关键字创建AcDbLine的实例
- 目前这个对象存储在堆内存上，还没有被加入到数据库(dwg)中

### 将直线对象加入数据库

```cpp
// 获得指向块表的指针
AcDbBlockTable *pBlockTable; 
acdbHostApplicationServices()->workingDatabase() 
 ->getBlockTable(pBlockTable, AcDb::kForRead);

// 获得指向特定的块表记录（模型空间）的指针
AcDbBlockTableRecord *pBlockTableRecord; 
pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, 
 AcDb::kForWrite);

// 将AcDbLine类的对象添加到块表记录中
AcDbObjectId lineId;
pBlockTableRecord->appendAcDbEntity(lineId, pLine);

// 关闭图形数据库的各种对象
pBlockTable->close(); 
pBlockTableRecord->close(); 
pLine->close();
```

- acdbHostApplicationServices()->workingDatabase()能够获得一个指向当前活动的图形数
据库对象的指针
- getBlockTable 是 AcDbDatabase 类的一个成员函数，用于获得指向图形数据库的块表的指针
  - 函数签名为`inline Acad::ErrorStatus getBlockTable(AcDbBlockTable*& pTable, AcDb::OpenMode mode);`
  - mode包含三个值:AcDb::kForRead、AcDb::kForWrite、AcDb::kForNotify
  - 函数的第一个参数是一个引用，因此函数体内修改这个变量的值就让pBlockTable这个变量获得了块表的指针
  - 类似该函数第一个参数传入指针引用的形式后续很多，不做赘述，看函数签名
- getAt 函数是 AcDbBlockTable 类的一个成员函数，用于获得块表中特定的记录
- appendAcDbEntity 是 AcDbBlockTableRecord 类的成员函数，用于将 pEntity 指向的实体
添加到块表记录和图形数据库中

## 注意事项

- 各种数据库对象的关闭：在打开或创建数据库对象之后，必须尽可能早的关闭它
- **不要使用delete pLine的语句**
  - ObjectARX 的编程中，当编程者使用 appendAcDbEntity 函数将对象添加到图形数据库之后，就需要由图形数
据库来操作该对象


## 示例

> 参考sample/02-line.cpp
