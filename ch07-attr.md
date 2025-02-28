# 修改图形对象属性

## 目标

将上一节的直线修改为红色

## 思路

- 如果是创建的时候修改直接操作创建的对象即可
- 修改已经添加到数据库中的对象才是核心问题
  1. 打开和关闭图形数据库的对象
  2. ID（AcDbObjectId）、指针、句柄（Handle）和ads_name

### 打开和关闭图形数据库的对象

- 访问图形数据库中对象的特性，必须在该对象被打开（对象创建时也会被打开）状态下访问
  - 用对象指针进行访问
- 并且在访问结束后要及时关闭该对象，不然就会引起 AutoCAD 的错误终止
- 关闭之后再次访问对象
  - AcDbObjectId，也就是对象的 ID 号
  - 在创建对象时，可以将图形数据库分配给该对象的 ID 保存起来
  - 在需要访问该对象时，根据这个 ID 从数据库中获得指向该对象的指针，就可以修改或者查询该对象的特性
  - 全局函数 acdbOpenAcDbEntity用于从实体的 ID 号获得指向图形数据库中实体的指针
- ObjectARX 提供了另外两个全局函数 acdbOpenAcDbObject 和 acdbOpenObject 来实现类似的功能，这三个函数的区别在与适用范围
  - acdbOpenAcDbEntity：适用于打开继承于 AcDbEntity 的数据库常驻对象，这类对象一般都能在图形窗口中显示，如直线、圆等
  - acdbOpenAcDbObject：适用于打开未继承于 AcDbEntity 的数据库常驻对象，这类对象不能在图形窗口中显示，如层表、线型表等
  - acdbOpenObject：如何不知道要打开的对象是否继承于 AcDbEntity 类，可以使用这个函数

### ID、指针、句柄、ads_name

- 访问实体的特性必须通过对象指针
- 获得了实体的ID、句柄或者ads_name，都能通过ID作中介而获得对象的指针
- ID:在一个 AutoCAD 任务中，可能会加载在多个数据库，但所有对象的ID本次任务中都是独一无二的。在不同的 AutoCAD 任务中，同一个图形对象的 ID 可能不同
- 句柄:在一个 AutoCAD 任务中，不能保证每个对象句柄都唯一。形数据库中所有对象的句柄都是唯一的。句柄随 DWG 图形一起保存，在两次任务期间同一对象的句柄是相同的
- ads_name:是不稳定的，只在某一个特定图层中可以使用

## 代码注意要点

### 让CreateLine函数返回对象ID

```cpp
AcDbObjectId CreateLine();
```

### 修改实体的颜色

```cpp
Acad::ErrorStatus ChangeColor(AcDbObjectId entId, Adesk::UInt16 colorIndex) {
  AcDbEntity *pEntity;
  // 打开数据库中实体
  acdbOpenObject(pEntity, entId, AcDb::kForWrite);
  // 修改实体的颜色
  pEntity->setColorIndex(colorIndex);
  pEntity->close();
  return Acad::eOk;
}  
```

### 使用类来组织

- 使用一个类CustomCreateEntity来管理创建实体
- 使用一个类CustomModityEntity来管理修改实体

## 示例代码

> 参考sample/03-modify-line
