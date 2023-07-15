#include "pch.h"

#include "framework.h"
#include "SampleApp.h"
#include "XamlBridge.h"

#include <winrt/Microsoft.Toolkit.Win32.UI.XamlHost.h>



class AppWindow : public DesktopWindowT<AppWindow>
{
    int MessageLoop()
    {
        return DesktopWindow::MessageLoop(m_accelerators.get());
    }
    constexpr static auto c_WindowClass = L"SimpleCppAppWindowClass";
    constexpr static auto c_WindowTitle = L"MyApp";
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


        HWND window = CreateWindowW(c_WindowClass, c_WindowTitle, WS_OVERLAPPEDWINDOW,
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


    void OnResize(HWND, UINT state, int cx, int cy) noexcept
    {
        //This will be called after initial window creation and ALSO dpi changes
        SetWindowPos(m_xamlIsland, 0, 0, 0, cx, cy, SWP_SHOWWINDOW);
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
