# Win32 Xaml Island
This project is a fork from the original [Microsoft Xaml Island Samples](https://github.com/microsoft/Xaml-Islands-Samples), pruned to only containing Win32 native window with Xaml island.

I found it exceptionally difficulty to get everything working, mismatched documentations are all over the places. And I found the official samples that are actually working, so I made some changes to it to make xaml island easier to get started with.

--- 
What's working in this project:
- Xaml Island with WinUI 2.8 (and it should also work with any later versions)
- Webview2
- Non-packaged mode (able to run with directly coping the build output exe and dlls) 
- Packaged mode (packaged with msix)
- Build with Visual Studio 2022

---
Things to be remembered:
- Do NOT upgrade the CppWinRT nuget! Or you get compile errors! See [this issue](https://github.com/microsoft/cppwinrt/issues/884)