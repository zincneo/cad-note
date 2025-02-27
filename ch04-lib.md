# ObjectARX 核心库概览

ObjectARX应用程序必须连接到acdb.lib和rxapi.lib两个动态链接库，这里面包含了几乎所有核心库的实现

> 最核心的为以下五个库

- AcRx
- AcEd
- AcDb
- AcGi
- AcGe

## AcRx

- ARX Runtiem
- AutoCAD的一个运行时扩展库
- 提供一些系统类
- 主要用于DLL初始化和连接，以及运行时类的注册和标识

## AcEd

- AutoCAD Editor
- AutoCAD编辑器功能相关的库
- 上一节见过类型AcEdCommandStack用来操作命令堆栈
- 还有一个比较重要的一个类AcEditorReactor
  - 这个反应器用来监听AutoCAD的状态
  - 比如指定事件的开始终止和删除等等

## AcDb

- 提供组成AutoCAD数据库的类的库
- 可以认为AutoCAD软件保存的dwg格式的文件就是一个数据库
- AutoCad数据库用来存储所有的图形对象和非图形对象
- 图形对象被称为实体，组成AutoCAD中的图形
- 非图形对象如层，线形，字体也是图形的一部分
- 可以使用这个库查询和管理现有的所有对象
- 完整的数据库包含九个符号表


## AcGi

- 提供绘制AutoCAD实体的图形界面的库

## AcGe

- 提供几何图形的库
- AcDb就使用了这个库
- 提供了很多几何类，如向量和矩阵用来完成二维和三维操作
- 提供了几种坐标系统
