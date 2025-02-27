# AutoCAD数据库

- AutoCAD保存的dwg文件其实就是一个特殊的数据库
  - 这个数据库存储组成AutoCAD软件中看到的图形的所有对象和实体
- 新建一张drawing.dwg可以理解为就是新建了一个数据库
  - 数据库中的基本对象是实体:比如画一个圆、一条直线
  - 实体是一种特殊的数据库对象
- 在AutoCAD数据库中固定包含了九个符号表(Symbol Table)
  - 查看ObjectARX的类图可以在AcDb库下看到对应的九张符号表的类
    1. AcDbViewTable 视图表
    2. AcDbViewportTable 视口表
    3. AcDbBlockTable 块表
    4. AcDbDimStyleTable 标注样式表
    5. AcDbLayerTable 层表
    6. AcDbLineTypeTable 线型表
    7. AcDbRegAppTable 应用程序表
    8. AcDbTextStyleTable 字体样式表
    9. AcDbUCSTable 坐标系统表
  - 以上的符号表都有对应的记录类型Record
    - 新建的dwg数据库的各符号表中就有一些默认的Record
    - 块表
      - *Model_space 模型空间
      - *Paper_space 布局空间1
      - *Paper_space0 布局空间2
    - 层表
      - 0
    - 线型表
      - ByLayer
      - ByBlock
      - Continuous
- 词典Dictionary
  - 为存储对象提供了比符号表更加不同的容器
  - 一个词典可以包含任何类型的数据库对象以及子类对象
  - 当创建图形时，我们就创建了一个命名对象词典
    - 命名对象词典就是根root
    - 可以往root里面添加任何新的词典，并在词典中添加数据库对象
- 代码中如何访问数据库
 - 需要包含头文件dbapserv.h
 - 全局函数acdbHostApplicationServices可以获取当前数据库
 - `acdbHostApplicationServices()->workingDatabase()`返回一个AcDbDatabase类的对象
- 多元数据库
  - 在一个AutoCAD会话中可以获取多个数据库
  - 在每一个会话(一张打开的dwg中)中，每一个对象都有一个句柄和ID
  - 在特定的范围内，句柄是唯一的识别对象
  - 在加载的数据库当中，ID是当前的识别对象(关闭再打开对象的ID就变了，但是句柄不变)
    - 对象ID只在打开的会话的内存中存在，句柄保存在图形中
    - 获取对象ID可以获得一个指向当前数据库中对象的指针，可以对对象进行操作
