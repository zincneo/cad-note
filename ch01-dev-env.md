# AutoCAD二次开发环境搭建

## 必须软件和库

- AutoCAD的对应版本
- Visual Studio 2022
- OpenARX SDK的对应版本
- OpenARX Wizard的对应版本

## 构建的目标

- 注意最终输出的文件为project_name.arx
- 通过AutoCAD的`APPLOAD`命令(缩写`AP`)可以加载project_name.arx进行测试
- 注意，arx程序本质上就是c++动态链接库，因此没有main函数作为程序的入口，取而代之的是acrxEntryPoint函数传递消息到AutoCAD中

## 创建项目的两种方式

- 通过c++ DLL动态链接库的模板创建
- 通过wizard安装得到的cad模板创建

## 通过动态链接库模板创建

### 安装ObjectARX SDK

- 官网下载对应版本的安装包
- 安装到本地自行确定的位置
- 以下以objectarx2018为例，测试过objectarx2024同样可用，注意改文件路径和文件名就好

### 创建项目

- 在Visual Studio 2022中新建c++ DLL项目
- 这里创建一个叫做`Exam01`的项目

### 项目配置

- 打开项目属性
- 常规
  - 平台工具集->Visual Studio 2017(v141)
  - Windows SDK版本->10.0.19
  - 目标文件扩展名->`.arx`
- VC++目录->包含目录
  - `objectarx2018/inc/`
  - `objectarx2018/inc-x64/`
- VC++目录->库目录
  - `objectarx2018/lib-x64`
- 链接器->输入->附加依赖项
  - acad.lib
  - acdb22.lib
  - acge22.lib
  - ac1st22.lib
  - rxapi.lib
  - accore.lib
- 链接器->输入->模块定义文件
  - 设置为和源文件中同名的.def文件
- 注意项目不可以取消预编译头，否则编译会有一大堆报错
- 源文件的cpp文件名可以自己改，不影响项目构建

### 入口程序

- 项目默认以dllmain.cpp作为入口程序
- 编译的dll库作为AutoCad的插件安装
- 接口函数为acrxEntryPoint

> 示例程序

```cpp
#include "pch.h"
#include "rxregsvc.h"
#include "aced.h"
#include "tchar.h"

void InitApplication();
void UnloadApplication();
void Hello();

extern "C" AcRx::AppRetCode acrxEntryPoint(
    AcRx::AppMsgCode msg, void* appId)
{
    switch (msg) {
    case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(appId);
        acrxDynamicLinker->registerAppMDIAware(appId);
        InitApplication();
        break;
    case AcRx::kUnloadAppMsg:
        UnloadApplication();
        break;
    default:
        break;
    }
    return AcRx::kRetOK;
}

void Hello() {
    acedPrompt(_T("\nHello World"));
}

void InitApplication() {
    acedRegCmds->addCommand(_T("Exam01"), _T("Hello"), _T("你好"), ACRX_CMD_MODAL, Hello);
}

void UnloadApplication() {
    acedRegCmds->removeGroup(_T("Exam01"));
} 
```

### 添加def文件

- C++ DLL项目中配置.def文件用来显示指定DLL导出的函数
  - .def 文件列出 DLL 导出的函数名和序号，确保这些函数可供外部调用
  - 可以精确控制导出的函数名和序号，避免编译器自动导出所有符号
  - 某些情况下，使用 .def 文件能更好地兼容不同编译器或平台
  
```def
LIBRARY Exam01
DESCRIPTION "First ARX application"
EXPORTS
acrxEntryPoint	PRIVATE
acrxGetApiVersion PRIVATE
```

- 关于以上def内容的解释
- 第一个语句必须是 LIBRARY 语句，后面跟着项目的名称
- DESCRTIPTION语句可有可无，用来描述这个动态链接库的功能
- EXPORTS 语句列出了动态链接库输出的函数，对于 ARX 应用程序，至少要输出
acrxEntryPoint 和 acrxGetApiVersion 两个函数

### 使用项目

- 点击生成
- 打开AutoCad2018新建图纸
- 在命令行中输入AP
- 安装刚刚生成的.arx文件
- 测试命令`HELLO`和`你好`

## 通过CAD模板创建

### 安装环境

- 下载并安装objectarx sdk
- 下载并安装objectarx wizard
  - 设置对应的sdk和objectarx sdk的路径要保证正确
  - 配置的RDS值在下面代码中会见到
- 启动Visual Studio Installer更新Visual Studio
- 重启Visual Studio发现模板中新增了arx相关的模板
- 实测中目前只在cad2024版本下跑成功过
- 选择ARX/DBX模板创建项目
  - 默认什么都不要设置
- 这里项目名设置为`ArxProject1`


### 构建

- 几乎不需要额外配置
- 可能需要这个配置消除编译器报错
  - 项目属性->C/C++->预处理器->预处理器定义`_ALLOW_RTCc_IN_STL`

### 代码简述

- 核心的代码文件为`acrxEntryPoint.cpp`
- `CPorjectNameApp`这个类中继承了父类`AcRxArxApp`
    - 这个子类的静态成员方法用来通过ACED_ARXCOMMAND_ENTRY_AUTO宏注册到命令中
    - 这个子类作为宏IMPLEMENT_ARX_ENTRYPOINT的参数定义接口函数acrxEntryPoint
    - 可以看出模板通过宏做了很多事情，使得在这里通过面向对象的方式来完成acrxEntryPoint函数接口的功能

```cpp
#include "StdAfx.h"
#include "resource.h"
#include "tchar.h"
// 之前安装wizard的地方设置的RDS会作为宏，需要在静态成员方法前面加上
#define szRDS _RXST("ADSK")

class CArxProject1App : public AcRxArxApp {
public:
	CArxProject1App () : AcRxArxApp () {}
	virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) {
		AcRx::AppRetCode retCode =AcRxArxApp::On_kInitAppMsg (pkt) ;
		return (retCode) ;
	}
	virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) {
		AcRx::AppRetCode retCode =AcRxArxApp::On_kUnloadAppMsg (pkt) ;
		return (retCode) ;
	}
	virtual void RegisterServerComponents () {
	}
	// 自己添加的hello命令
	static void ADSKMyGroupHello() {
		acedPrompt(_T("\n使用模板构建cad项目"));
	}
} ;
IMPLEMENT_ARX_ENTRYPOINT(CArxProject1App)
ACED_ARXCOMMAND_ENTRY_AUTO(CArxProject1App, ADSKMyGroup, Hello, NiHao, ACRX_CMD_MODAL, NULL)
```
