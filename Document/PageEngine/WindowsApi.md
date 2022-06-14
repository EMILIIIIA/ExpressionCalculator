# [WindowsApi](../index.md)
WindowsApi提供了调用WindowsApi的接口，封装了窗口模糊效果与获取系统配色的函数。

|**头文件**|**#include "PageEngine/WindowsApi.h"**|
|----|:-------|
|**继承自**|**无**|

## 公有成员

|**struct**|**[RGBcolor](#PageManager)**|
|----|:-------|
|**static RGBColor**|**[getSystemColor()](#getSystemColor)**|
|**static void**|**[setWindowBlurEffect(HWND hwnd)](#setWindowBlurEffect)**|


## 私有成员

|**enum**|**ACCENT_STATE**|
|----|:-------|
|**enum**|**WINDOWCOMPOSITIONATTRIB**|
|**struct**|**WINDOWCOMPOSITIONATTRIBDATA**|
|**struct**|**ACCENT_POLICY**|

## 详细描述
获取系统配色是Dwmapi.dll中的函数DwmGetColorizationColor()的二次封装，返回一个结构体代表RGB颜色值。窗口模糊效果是user32.dll中SetWindowCompositionAttribute()函数的二次封装，给予一个窗口句柄，将这个窗口设置模糊效果
## 成员函数文档


<span id="getSystemColor"></span>
### static RGBColor WindowsApi::getSystemColor()
获取系统配色为RGB类型值，其中RGBColor是一个包含三个DWORD类型变量的结构体，分别代表RGB

##
<span id="setWindowBlurEffect"></span>
### static void WindowsApi::setWindowBlurEffect(HWND hwnd)
将传入句柄对应的窗口设置为模糊窗口

