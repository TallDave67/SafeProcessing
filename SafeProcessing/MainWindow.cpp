#include "MainWindow.h"
#include <objbase.h>

MainWindow::MainWindow()
{
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE); 
    if (FAILED(hr))
    {
        // Handle the error.
        MessageBox(NULL, (LPCWSTR)L"Could not initialize COM", (LPCWSTR)L"Failure", MB_ICONERROR | MB_OK);
    }
    else
    {
        // The function succeeded.
        //MessageBox(NULL, (LPCWSTR)L"COM initialized", (LPCWSTR)L"Success", MB_ICONINFORMATION | MB_OK);
    }
}

MainWindow::~MainWindow()
{
    CoUninitialize();
}

PCWSTR MainWindow::ClassName() const
{
    return L"Main Window Class";
}

PCWSTR MainWindow::WindowName() const
{
    return L"Safe Processing";
}

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(m_hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), m_hwnd, About);
            break;
        case ID_PROCESS:
            m_process.process();
            break;
        case IDM_EXIT:
            DestroyWindow(m_hwnd);
            break;
        default:
            return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
        }
    }
    return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(m_hwnd, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
        EndPaint(m_hwnd, &ps);
    }
    return 0;

    default:
        return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
    }
    return TRUE;
}

// Message handler for about box.
INT_PTR CALLBACK MainWindow::About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

