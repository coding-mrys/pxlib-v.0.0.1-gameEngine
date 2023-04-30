#define WIN32_LEAN_AND_MEAN
#define UNICODE
#include <windows.h>
#include <stdint.h>
#include "pxlib.h"

using namespace std;

typedef uint32_t u32;

//main window
int WINAPI main(HINSTANCE Instance, HINSTANCE PrevInstance, PWSTR CmdLine, int CmdShow) {

    //config
    WNDCLASS WindowClass = {};
    const wchar_t ClassName[] = L"mryspxlib v.0.0.1";
    WindowClass.lpfnWndProc = WindowProc;
    WindowClass.hInstance = Instance;
    WindowClass.lpszClassName = ClassName;
    WindowClass.hCursor = LoadCursor(0, IDC_CROSS);

    if (!RegisterClass(&WindowClass)) {
        return GetLastError();
    }

    HWND Window = CreateWindowEx(0, ClassName, L"pxlib001",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT,
        0, 0, Instance, 0);


    RECT ClientRect;
    GetClientRect(Window, &ClientRect);
    ClientWidth = ClientRect.right - ClientRect.left;
    ClientHeight = ClientRect.bottom - ClientRect.top;

    BitmapWidth = ClientWidth;
    BitmapHeight = ClientHeight;

    int bpp = 4;

    BitmapMemory = VirtualAlloc(0,
        BitmapWidth * BitmapHeight * bpp,
        MEM_RESERVE | MEM_COMMIT,
        PAGE_READWRITE
    );

    BITMAPINFO BitmapInfo;
    BitmapInfo.bmiHeader.biSize = sizeof(BitmapInfo.bmiHeader);
    BitmapInfo.bmiHeader.biWidth = BitmapWidth;
    BitmapInfo.bmiHeader.biHeight = -BitmapHeight;
    BitmapInfo.bmiHeader.biPlanes = 1;
    BitmapInfo.bmiHeader.biBitCount = 32;
    BitmapInfo.bmiHeader.biCompression = BI_RGB;
     
    HDC DeviceContext = GetDC(Window);

    bool Running = true;

    //---

    triangle ta1,ta2;

    float a = 0, b = 0, c = 0;
    float i = 0 ;

    //---

    while (Running) {
        MSG Message;
        while (PeekMessage(&Message, nullptr, 0, 0, PM_REMOVE)) {
            if (Message.message == WM_QUIT) Running = false;
            TranslateMessage(&Message);
            DispatchMessage(&Message);
        }

        //---

        background(0x111115);

        cam.init(100,300,100, 1000, 90);
        cam.rotate(0, 0, 0);
        cam.simulate();

        ta1.build(300, 500, 50, 100, 80, 0x00ffff);
        ta1.rotate(a, b, c);

        ta2.build(1000, 700, 50, 200, 80, 0xffff00);
        ta2.rotate(a, b, c);
        
        a+=0.1; b+=0.1, c+=0.1;

        //---

        Sleep(0.1);

        StretchDIBits(DeviceContext,
            0, 0,
            BitmapWidth, BitmapHeight, 
            0, 0,
            ClientWidth, ClientHeight,
            BitmapMemory, &BitmapInfo,
            DIB_RGB_COLORS, SRCCOPY);
    }

    return 0;
}
