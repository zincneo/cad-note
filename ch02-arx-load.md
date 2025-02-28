# ObjectARX程序加载和卸载

> 本质上就是CAD程序加载和卸载.arx文件

## 加载

1. 打开CAD之后使用`APPLOAD`命令(缩写`AP`)加载.arx文件
2. 利用acad.rx文件
    - 在CAD的命令框左侧打开设置选项
    - 设置选项->支持文件的搜索路径->添加路径
    - CAD会使用路径的acad.rx文件
    - acad.rx就是一个纯文本文件，包含了要加载的.arx文件的路径
3. 使用`ARX`命令
4. 调用LISP函数
    - 在CAD的命令行输入VLIDE可以打开LISP控制台
    - 在LISP控制台执行代码`(ARXLOAD filepath.arx)`
5. 在arx应用程序内部调用acedArxLoad函数加载
    - 该函数的参数是指向另外一个arx程序

## 卸载

1. 在arx程序代码中卸载，一般会写一个unloadAPP函数处理卸载操作
2. 打开CAD之后使用`APPLOAD`命令(缩写`AP`)卸载.arx文件
3. 使用`ARX`命令
4. 调用LISP函数
    - 在CAD的命令行输入VLIDE可以打开LISP控制台
    - 在LISP控制台执行代码`(ARXUNLOAD ARXNAME NUM)`
5. 在arx应用程序内部调用acedArxUnLoad函数卸载

## 入口函数详解

- acrxEntryPoint 是一个非常重要的函数，它是AutoCAD与ARX应用程序之间的主要接口
- 这个函数的作用是处理AutoCAD发送给ARX应用程序的各种消息和事件
- 通过这个函数，ARX应用程序可以响应AutoCAD的各种操作，如加载、卸载、命令执行等
- 函数签名为`extern "C" AcRx::AppRetCode acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt);`
    - `extern "C"`用来告诉编译器需要按c的方式编译
    - msg是枚举类型，表示AutoCAD在调用这个函数的时候传入的消息类型
        - kInitAppMsg 当ARX应用程序被加载时发送
        - kUnloadAppMsg 当ARX应用程序被卸载时发送
        - kLoadDwgMsg 当AutoCAD加载一个图形文件时发送
        - kUnloadDwgMsg 当AutoCAD卸载一个图形文件时发送
        - kInvkSubrMsg 当用户调用ARX应用程序定义的命令时发送
        - 其他枚举值略去
    - ptk这个参数是一个指向消息相关数据的指针(void *类型)具体的类型和内容取决于msg的值
        - 当msg为kInitAppMsg时，pkt通常为NULL
        - 当msg为kInvkSubrMsg时，pkt可能指向一个包含命令名称或其他相关信息的结构体
    - 返回值类型AcRx::AppRetCode也是一个枚举
        - AcRx::kRetOK 表示消息处理成功
        - AcRx::kRetError 表示消息处理失败
