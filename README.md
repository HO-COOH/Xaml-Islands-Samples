# Win32 Xaml Island
This project is a fork from the original [Microsoft Xaml Island Samples](https://github.com/microsoft/Xaml-Islands-Samples), pruned to only containing Win32 native window with Xaml island.

I found it exceptionally difficulty to get everything working, mismatched documentations are all over the places. And I found the official samples that are actually working, so I made some changes to it to make xaml island easier to get started with.

--- 
What's working in this project:
- Xaml Island with WinUI 2.8.2 pre-release (and it should also work with any later versions)
- Webview2
- Non-packaged mode (able to run with directly coping the build output exe and dlls) 
- Packaged mode (packaged with msix)
- Build with Visual Studio 2022

| <!-- -->    | <!-- -->    |
|-------------|-------------|
|Running with debugger (unpackaged)| ![image](https://github.com/HO-COOH/Xaml-Islands-Samples/assets/42881734/81c8e162-1e72-4e02-9326-fe9f08a20320)|
|Running the exe (unpackaged)|![image](https://github.com/HO-COOH/Xaml-Islands-Samples/assets/42881734/7463a41a-ae40-4087-95f9-584c0bbd1046)|
|Packaged| ![image](https://github.com/HO-COOH/Xaml-Islands-Samples/assets/42881734/687ae35d-6974-42fb-9689-0622c4d621fa)|

---
Things to be remembered:
- Do NOT upgrade the CppWinRT nuget! Or you get compile errors! See [this issue](https://github.com/microsoft/cppwinrt/issues/884)
- To debug, choose the startup project to the main win32 project (that is **SampleCppApp**).
