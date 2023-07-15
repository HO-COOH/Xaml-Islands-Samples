#include "pch.h"

#include "framework.h"
#include "SampleApp.h"
#include "XamlBridge.h"

#include <winrt/Microsoft.Toolkit.Win32.UI.XamlHost.h>

const wchar_t c_WindowClass[] = L"SimpleCppAppWindowClass";

class AppWindow : public DesktopWindowT<AppWindow>
{
    int MessageLoop()
    {
        return DesktopWindow::MessageLoop(m_accelerators.get());
    }
public:
    static int Show(HINSTANCE hInstance, int nCmdShow)
    {
        return AppWindow{ hInstance }
            .CreateAndShowWindow(nCmdShow)
            .MessageLoop();
    }

    LRESULT MessageHandler(UINT message, WPARAM wParam, LPARAM lParam) noexcept
    {
        switch (message)
        {
            HANDLE_MSG(WindowHandle(), WM_CREATE, OnCreate);
            HANDLE_MSG(WindowHandle(), WM_DESTROY, OnDestroy);
            HANDLE_MSG(WindowHandle(), WM_SIZE, OnResize);
        default:
            return base_type::MessageHandler(message, wParam, lParam);
        }
    }

private:
    AppWindow(HINSTANCE hInstance) noexcept : m_instance(hInstance)
    {
    }

    AppWindow& CreateAndShowWindow(int nCmdShow)
    {
        m_accelerators.reset(LoadAcceleratorsW(m_instance, MAKEINTRESOURCE(IDC_SAMPLECPPAPP)));

        WNDCLASSEXW wcex = { sizeof(wcex) };
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = WndProc;
        wcex.hInstance = m_instance;
        wcex.hIcon = LoadIconW(m_instance, MAKEINTRESOURCE(IDI_SAMPLECPPAPP));
        wcex.hCursor = LoadCursorW(nullptr, IDC_ARROW);
        wcex.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
        wcex.lpszClassName = c_WindowClass;
        wcex.hIconSm = LoadIconW(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
        RegisterClassExW(&wcex); // don't test result, handle error at CreateWindow

        wchar_t title[64];
        LoadStringW(m_instance, IDS_APP_TITLE, title, ARRAYSIZE(title));

        HWND window = CreateWindowW(c_WindowClass, title, WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, InitialWidth, InitialHeight,
            nullptr, nullptr, m_instance, this);
        THROW_LAST_ERROR_IF(!window);

        ShowWindow(window, nCmdShow);
        UpdateWindow(window);
        SetFocus(window);
        return *this;
    }


    bool OnCreate(HWND, LPCREATESTRUCT) noexcept
    {
        m_mainUserControl = winrt::MyApp::MainUserControl();
        m_xamlIsland = CreateDesktopWindowsXamlSource(WS_TABSTOP, m_mainUserControl);

        return true;
    }

    void OnDestroy(HWND hwnd) noexcept
    {
        base_type::OnDestroy(hwnd);
    }

    void OnResize(HWND, UINT state, int cx, int cy) noexcept
    {
        //This will be called after initial window creation and ALSO dpi changes
        const auto newHeight = cy;
        const auto newWidth = cx;
        const auto islandHeight = newHeight - (ButtonHeight * 2) - ButtonMargin;
        const auto islandWidth = newWidth - (ButtonMargin * 2);
        SetWindowPos(m_xamlIsland, 0, 0, XamlIslandMargin, islandWidth, islandHeight, SWP_SHOWWINDOW);
    }

    const HINSTANCE m_instance;
    HWND m_xamlIsland{};
    wil::unique_haccel m_accelerators;
    winrt::MyApp::MainUserControl m_mainUserControl{ nullptr };
};


int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR lpCmdLine, int nCmdShow)
{
    winrt::init_apartment(winrt::apartment_type::single_threaded);

    winrt::MyApp::App app;

    const auto result = AppWindow::Show(hInstance, nCmdShow);

    app.Close();

    return result;
}
