## chalet-example-mono

This repository showcases how to setup a [Chalet](https://www.chalet-work.space) project with [Mono](https://www.mono-project.com) / C# Scripting in a C++ application across all platforms supported by Mono. It also includes some basic configuration for use with [Visual Studio Code](https://code.visualstudio.com/).

To get started, [download Chalet](https://www.chalet-work.space/download), check out some of the documentation for it, and either build with the various commands from the command line, or try out the [Chalet VS Code Extension](https://marketplace.visualstudio.com/items?itemName=chalet-org.vscode-chalet) (recommended).

### Windows

Download & Install (Mono Runtime 64-bit)[https://www.mono-project.com/download/stable/#download-win]

### MacOS

Download & Install (Mono (Either Channel))[https://www.mono-project.com/download/stable/#download-mac]

### Linux

If possible, use the distro directions [here](https://www.mono-project.com/download/stable/#download-lin)

For Arch Linux, you can try the `mono` package, but may need to build `mono-git` from the AUR, also make sure `msbuild` is installed.

### Debugging

* For MacOS: Install CodeLLDB and use the "LLDB" launch.json configuration
* For Windows: Install the C/C++ extension and Build with MSVC and use the "MSVC" configuration
* For Linux: Install the C/C++ extension and Use the "GDB" configuration
