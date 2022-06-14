#ifndef WINDOWSAPI_H
#define WINDOWSAPI_H
#include <Windows.h>
#include <dwmapi.h>


class WindowsApi
{

private:
    //几个枚举和结构体，参考官方api文档
    enum WINDOWCOMPOSITIONATTRIB
    {
        WCA_UNDEFINED = 0,
        WCA_NCRENDERING_ENABLED = 1,
        WCA_NCRENDERING_POLICY = 2,
        WCA_TRANSITIONS_FORCEDISABLED = 3,
        WCA_ALLOW_NCPAINT = 4,
        WCA_CAPTION_BUTTON_BOUNDS = 5,
        WCA_NONCLIENT_RTL_LAYOUT = 6,
        WCA_FORCE_ICONIC_REPRESENTATION = 7,
        WCA_EXTENDED_FRAME_BOUNDS = 8,
        WCA_HAS_ICONIC_BITMAP = 9,
        WCA_THEME_ATTRIBUTES = 10,
        WCA_NCRENDERING_EXILED = 11,
        WCA_NCADORNMENTINFO = 12,
        WCA_EXCLUDED_FROM_LIVEPREVIEW = 13,
        WCA_VIDEO_OVERLAY_ACTIVE = 14,
        WCA_FORCE_ACTIVEWINDOW_APPEARANCE = 15,
        WCA_DISALLOW_PEEK = 16,
        WCA_CLOAK = 17,
        WCA_CLOAKED = 18,
        WCA_ACCENT_POLICY = 19,
        WCA_FREEZE_REPRESENTATION = 20,
        WCA_EVER_UNCLOAKED = 21,
        WCA_VISUAL_OWNER = 22,
        WCA_LAST = 23
    };

    struct WINDOWCOMPOSITIONATTRIBDATA
    {
        WINDOWCOMPOSITIONATTRIB Attrib;
        PVOID pvData;
        SIZE_T cbData;
    };

    enum ACCENT_STATE
    {
        ACCENT_DISABLED = 0,
        ACCENT_ENABLE_GRADIENT = 1,
        ACCENT_ENABLE_TRANSPARENTGRADIENT = 2,
        ACCENT_ENABLE_BLURBEHIND = 3,
        ACCENT_ENABLE_ACRYLICBLURBEHIND = 4,
        ACCENT_INVALID_STATE = 5
    };

    struct ACCENT_POLICY
    {
        ACCENT_STATE AccentState;
        DWORD AccentFlags;
        DWORD GradientColor;
        DWORD AnimationId;
    };

    //将要从动态库中取出的函数原型,负责模糊效果，详见WindowsApi参考文档 BOOL SetWindowCompositionAttribute(HWND hWnd, WINDOWCOMPOSITIONATTRIBDATA* pAttrData)
    //某位已经不可考的大神写的typedef，简化声明。使用时直接将myBlurFunction替换即可
    typedef BOOL(WINAPI*myBlurFunction)(HWND, WINDOWCOMPOSITIONATTRIBDATA*);
    //将要从动态库取出的函数原型，负责获取系统颜色，详见WindowsApi参考文档 HRESULT DwmGetColorizationColor
    typedef HRESULT(WINAPI*myColorFunction)(DWORD*, BOOL*);

public:
    struct RGBColor
    {
        DWORD r,g,b;
    };
    static RGBColor getSystemColor();               //获取系统配色
    static void setWindowBlurEffect(HWND hwnd);     //设置窗口透明效果
};
#endif // WINDOWSAPI_H
