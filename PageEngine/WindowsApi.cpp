#include "PageEngine/WindowsApi.h"
#include "CalEngine/CalException.h"

using CalEngine::CalException;
using CalEngine::ErrorName;

WindowsApi::RGBColor WindowsApi::getSystemColor()
{
    myColorFunction DwmGetColorizationColor;
    DWORD *color =new DWORD;
    BOOL opaque = FALSE;
    HMODULE dwmapimodule;
    dwmapimodule=LoadLibrary(L"Dwmapi.dll");
    DwmGetColorizationColor = myColorFunction(GetProcAddress(dwmapimodule, "DwmGetColorizationColor"));
    HRESULT hr = DwmGetColorizationColor(color, &opaque);
    WindowsApi::RGBColor gettedColor;
    if(hr==0)
    {
        gettedColor={(*color >> 16) % 256, (*color >> 8) % 256 , (*color) % 256};
        delete color;
        return gettedColor;
    }
    else
    {
        delete color;
        throw CalException(ErrorName::CalSystemError);
    }
    delete color;
}

void WindowsApi::setWindowBlurEffect(HWND hwnd)
{
    HMODULE blurHuser;
    myBlurFunction setWindowCompositionAttribute;
    blurHuser = GetModuleHandle(L"user32.dll");//获取已经载入进程空间的模块句柄
    if(blurHuser==NULL)
        blurHuser=LoadLibrary(L"user32.dll");//如果进程空间未载入user32则手动载入，当然user32是默认载入的这句没啥用
    if(blurHuser)
    {
        setWindowCompositionAttribute = myBlurFunction(GetProcAddress(blurHuser, "SetWindowCompositionAttribute"));
        //从动态库中取出函数
        if(setWindowCompositionAttribute)
        {
            //DWORD gradientColor = DWORD(0x50FFFFFF);
            ACCENT_POLICY accent = { ACCENT_ENABLE_BLURBEHIND, 0, 0, 0};
            WINDOWCOMPOSITIONATTRIBDATA setting;
            setting.Attrib = WCA_ACCENT_POLICY;
            setting.pvData = &accent;
            setting.cbData = sizeof(accent);
            setWindowCompositionAttribute(hwnd, &setting);
        }
        else
           throw CalException(ErrorName::CalSystemError);
    }
    else
        throw CalException(ErrorName::CalSystemError);
}

