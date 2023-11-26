#pragma once

#include "BaseWindow.hpp"
#include "Process.h"

class MainWindow : public BaseWindow<MainWindow>
{
public:
    MainWindow();
    ~MainWindow();

    PCWSTR ClassName() const;
    PCWSTR WindowName() const;

    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    static INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

private:
    Process m_process;
};
