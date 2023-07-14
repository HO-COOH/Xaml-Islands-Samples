#include "pch.h"
#include "MainUserControl.h"

namespace winrt::MyApp::implementation
{
    MainUserControl::MainUserControl()
    {  
        InitializeComponent();
    }


    void winrt::MyApp::implementation::MainUserControl::Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const&)
    {
        sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Content(winrt::box_value(L"Clicked!"));
    }


}

