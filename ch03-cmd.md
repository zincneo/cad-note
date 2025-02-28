# ObjectARX命令

- 在ObjectARX应用程序中可以注册AutoCAD的新命令
- 新的命令和AutoCAD原生的命令在执行效率上没有区别

## 加载和卸载新命令的方法

- accmd.h头文件中提供了宏acedRegCmds
- 该宏像函数一样调用acedRegCmds()返回一个AcEdCommandStack类的对象
- 命令调用堆栈类AcEdCommandStack类
  - 命令都存储在该类型的实例上
  - 成员方法addCommand可以向命令堆栈上添加新的命令
  - 成员方法removeCmd可以按组和全局名称删除命令堆栈上的命令
  - 成员方法removeGroup可以按组删除命令堆栈上的命令
- 在Visual Studio中使用模板创建的ARX项目会使用宏ACED_ARXCOMMAND_ENTRY_AUTO来添加新的命令，该宏映射的最终结构同样是调用addCommand方法

### addCommand函数原型

```cpp
// 命令调用堆栈类继承自基类AcRxObject，关于AcRx库下一节会介绍
class AcEdCommandStack: public AcRxObject {
public:
  virtual Acad::ErrorStatus addCommand(const ACHAR * cmdGroupName, // 命令所属的组
                                     const ACHAR * cmdGlobalName,  // 命令的全局名称
                                     const ACHAR * cmdLocalName,   // 命令的本地名称
                                     Adesk::Int32 commandFlags,    // 命令的类型
                                     AcRxFunctionPtr FunctionAddr, // 命令执行的函数地址
                                     AcEdUIContext *UIContext=NULL,
                                     int fcode=-1,
                                     const AcRxResourceInstance& resourceInstance = AcRxResourceInstance::empty(),
                                     AcEdCommand** cmdPtrRet=NULL) = 0;
}
```

需要关注的是前五个参数

1. cmdGroupName 命令属于哪一个组，一个组下可以有多个命令
2. cmdGlobalName 命令的国际名称(英文)
3. cmdLocalName 命令的本地名称(本地语言或者也设置英文)
4. commandFlags 命令的类型
  - 模态命令: 执行过程中不可以执行其他模态命令，但是可以执行其他透明命令
  - 透明命令

