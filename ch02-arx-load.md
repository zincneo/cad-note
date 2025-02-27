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

1. 在arx程序代码中解锁
2. 打开CAD之后使用`APPLOAD`命令(缩写`AP`)卸载.arx文件
3. 使用`ARX`命令
4. 调用LISP函数
    - 在CAD的命令行输入VLIDE可以打开LISP控制台
    - 在LISP控制台执行代码`(ARXUNLOAD ARXNAME NUM)`
5. 在arx应用程序内部调用acedArxUnLoad函数卸载
