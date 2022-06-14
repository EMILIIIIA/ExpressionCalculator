# [MainWindow](../index.md)
MainWindow是计算器的主窗口，包含标题栏、功能栏、功能选择栏、能放置页面的窗体，历史记录栏等

|**头文件**|**#include "MainWindow.h"**|
|----|:-------|
|**继承自**|**QMainWindow**|

## 公有成员

||**[MainWindow(QWidget *parent = nullptr)](#MainWindow)**|
|----|:-------|
||**[~MainWindow()](#~MainWindow)**|      

## 私有成员

|**void override**|**[mouseMoveEvent(QMouseEvent *\*event*)](#mouseMoveEvent)**|
|----|:-------|
|**void override**|**[mousePressEvent(QMouseEvent *\*event*)](#mousePressEvent)**|
|**void override**|**[mouseReleaseEvent(QMouseEvent *\*event*)](#mouseReleaseEvent)**|
|**void override**|**[resizeEvent(QResizeEvent *\*event*)](#resizeEvent)**|
|**FunctionChooseBar**|***mChooseBarWidget**|
|**PageManager**|**mPagelist**|
|**int32_t**|**mWindowWidth**|
|**int32_t**|**mWindowHeight**|
|**int32_t**|**mLastWidth**|
|**int32_t**|**mLastHeight**|
|**int8_t**|**mMouseState**|
|**QPoint**|**mMousePosition**|
|**bool**|**mIsMaximum**|
|**bool**|**mIsShowFront**|
|**bool**|**mIsShowHis**|
|**bool**|**mIsMousePressed**|

## 公有槽
|**void**|**[getReturnedMode(int selectedMode)](#getReturnedMode)**|
|----|:-------|
|**void**|**[updateHistoryPage(QString)](#updateHistoryPage)**|


## 私有槽
|**void**|**[on_fixFront_clicked()](#on_fixFront_clicked)**|
|----|:-------|
|**void**|**[void on_maximum_clicked()](#on_maximum_clicked)**|
|**void**|**[void on_minimum_clicked()](#on_minimum_clicked)**|
|**void**|**[void on_shutdown_clicked()](#on_shutdown_clicked)**|
|**void**|**[on_showHis_clicked()](#on_showHis_clicked)**|
|**void**|**[on_modeSwitchButton_clicked()](#on_modeSwitchButton_clicked)**|

## 信号
|**void**|**[functionChooseBarOpenAnimation()](#functionChooseBarOpenAnimation)**|
|----|:-------|
|**void**|**[functionChooseBarCloseAnimation()](#functionChooseBarCloseAnimation)**|




## 详细描述
### 简介
MainWindow是计算器的主窗口，包含标题栏、功能栏、功能选择栏、能放置页面的窗体，历史记录栏等。风格模仿Windows UWP风格，大量采用样式表进行风格管理，便于修改。实例间通信采用QT内置信号槽机制，如向历史记录栏上传内容
### 添加自定义页面
向MPageList内传入想要添加页面的指针，并传入主窗口中将要加入页面位置的指针，在FunctionChooseBar中选择添加一个按钮，使其返回数值对应添加页面的编号（编号按照添加页面先后顺序指定），即可正常切换并使用此界面
## 成员函数文档


<span id="MainWindow"></span>
### MainWindow::MainWindow(QWidget *parent = nullptr)
此函数为构造函数，在程序运行开始时执行。内容包括以下几个方面。\
在初始化阶段，进行窗口大小设置，窗口标题栏设置，鼠标追踪等。\
在页面设置阶段，通过new分配页面实例，并接入内存管理类，同时设定默认界面。\
在信号连接阶段，连接与MainWindow相关的信号与槽。\
在Windows API阶段，设置与Windows API相关的内容。\
在qss样式表中，对样式表进行设置。

##
<span id="~MainWindow"></span>
### MainWindow::~MainWindow()
此函数为析构函数，进行内存的释放\
~~题外话：因为主窗口析构后程序就退出了，所以内存泄漏也没啥事~~

##
<span id="mouseMoveEvent"></span>
### MainWindow::mouseMoveEvent(QMouseEvent *\*event*)
此函数为QMainWindow类中函数的重载，在鼠标移动时自动调用，负责拖动窗口和窗口大小改变

##
<span id="mousePressEvent"></span>
### MainWindow::mousePressEvent(QMouseEvent *\*event*)
此函数为QMainWindow类中函数的重载，在鼠标按下时自动调用，负责拖动窗口和窗口大小改变

##
<span id="mouseReleaseEvent"></span>
### MainWindow::mouseReleaseEvent(QMouseEvent *\*event*)
此函数为QMainWindow类中函数的重载，在鼠标松开时自动调用，负责拖动窗口和窗口大小改变

##
<span id="mouseReleaseEvent"></span>
### MainWindow::resizeEvent(QResizeEvent *\*event*)
此函数为QMainWindow类中函数的重载，在窗口大小改变时自动调用，负责修改窗口管理类管理的控件大小修改

##
<span id="getReturnedMode"></span>
### MainWindow::getReturnedMode(int selectedMode)
此函数接收功能选择栏返回的页面编号，并将当前页面切换为对应编号的页面

##
<span id="updateHistoryPage"></span>
### MainWindow::updateHistoryPage(QString willupdate)
此函数接收所有其他页面发来的信号，将内容上传到历史记录栏

##
<span id="on_fixFront_clicked"></span>
### MainWindow::on_fixFront_clicked()
当窗口置顶按钮被按下时将窗口置顶，再次按下取消

##
<span id="void on_maximum_clicked"></span>
### MainWindow::void on_maximum_clicked()
当窗口最大化按钮按下时最大化，再次按下取消

##
<span id="void on_minimum_clicked"></span>
### MainWindow::void on_maximum_clicked()
当窗口最小化按钮按下时最小化

##
<span id="void on_shutdown_clicked"></span>
### MainWindow::void on_maximum_clicked()
当关闭按钮按下时关闭程序

##
<span id="on_showHis_clicked"></span>
### MainWindow::void on_maximum_clicked()
当显示历史记录按钮

##
<span id="on_modeSwitchButton_clicked"></span>
### MainWindow::void on_modeSwitchButton_clicked()
此函数会显示功能选择栏，并且发送启动动画信号

##
<span id="functionChooseBarOpenAnimation"></span>
### MainWindow::void functionChooseBarOpenAnimation()
此信号会启动功能选择栏开启动画

##
<span id="functionChooseBarCloseAnimation"></span>
### MainWindow::void functionChooseBarCloseAnimation()
此信号会启动功能选择栏关闭动画






