# Win32 Console Game

Weird experimental side-project about building a 2D game inside the Windows cmd.

Use arrows to move player.

Tested on Windows 10 but should also work on Windows 7 and higher.

## Build Steps

Requirements are:
- [Visual Studio 2022](https://visualstudio.microsoft.com/downloads/) or
[JetBrains Rider](https://www.jetbrains.com/rider/) (Recommended).
- [vcpkg](https://vcpkg.io/) with `spdlog` and `fmt` packages installed.

1. Load project in Visual Studio/Rider.
2. Select a `x64` build configuration (`Debug` or `Release`).
3. Hit the build button.
4. Run it (if using rider, check the `Use external console` under the `Edit Configurations...` panel).
