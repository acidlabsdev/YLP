<!-- markdownlint-disable MD033 -->

# About

<div align="center">
  <a href="#">
    <img height="512" width="512"  alt="logo" src="https://github.com/xesdoog/YLP/blob/main/docs/img/logo.png">
  </a><br><br>
</div>

A launchpad for YimMenu Legacy and YimMenuV2 with opt-in automatic injection and Lua scripting.

## Getting Started

1. Download the latest version from the [Releases](https://github.com/xesdoog/ylp/releases) page.
2. Move it to your preferred location.
3. Run **YLP.exe**. No installation required.
4. The built-in updater will keep you up to date.

> [!Note]
> Windows will flag the executable on first launch. You'll need to whitelist both the executable and its data folder (`%AppData%\YLP`) in your anti-virus.

## Features

### Mod Management

- Downloads YimMenu and YimMenuV2 with the press of a button.
- Automatically checks for new releases of downloaded menus on init as well as on request.
- Optional lightweight process monitor (required for auto-inject).
- Automatically injects the menu precisely at the landing page. No manual configurations required.

### YimMenu-Lua Script Management

- Parses all Lua repositories from [YimMenu-Lua](https://github.com/YimMenu-Lua) (Legacy only).
- Browse/Download/Enable/Disable/Delete Lua scripts right from the UI.
- Automatically checks for new releases of downloaded Lua scripts on init.

### Standalone DLL Injector

- Add custom DLL files and inject them into any process *(standard `LoadLibrary`, no manual mapping)*.
- Any injected file will remember its last target process and automatically select it if it's running.

### Builtin Lua Scripting

- Provides an optional (opt-in) LuaJIT scripting environment.
- Feature can be toggled on/off at any time.
- All scripts placed in the `/Plugins` folder (`%AppData%\YLP\Plugins`) are automatically loaded on program start if the scripting feature is toggled on. Scripts must be placed in their own subfolders and have a main entry file named exactly `main.lua` *(case-insensitive)*.
- Lua code can be typed and executed directly in the UI as well.
- More info can be found in the [LuaAPI](./docs/Lua%20API/Readme.md) docs section.

## Themes

Visit the [themes section](./docs/themes/Readme.md) to read more about UI themes.

## Feedback & Issues

Please submit any bug reports or feature suggestions on the [Issues](https://github.com/xesdoog/ylp/issues/new/choose) page.

## Acknowledgments

A huge thanks to the open source community and their immense contributions. You can find out more in the [Third Party](./docs/thirdparty/Readme.md) section

## Preview

<div>
    <a href="https://github.com/xesdoog/YLP/blob/main/docs/img/screenshots/1.jpg">
        <img height="256" width="256" alt="Home" src="https://github.com/xesdoog/YLP/blob/main/docs/img/screenshots/1.jpg">&nbsp;&nbsp;
    </a>
    <a href="https://github.com/xesdoog/YLP/blob/main/docs/img/screenshots/2.jpg">
        <img height="256" width="256" alt="YimMenu-Lua" src="https://github.com/xesdoog/YLP/blob/main/docs/img/screenshots/2.jpg">&nbsp;&nbsp;
    </a>
    <a href="https://github.com/xesdoog/YLP/blob/main/docs/img/screenshots/3.jpg">
        <img height="256" width="256" alt="User DLLs" src="https://github.com/xesdoog/YLP/blob/main/docs/img/screenshots/3.jpg">&nbsp;&nbsp;
    </a>
    <a href="https://github.com/xesdoog/YLP/blob/main/docs/img/screenshots/5.jpg">
        <img height="256" width="256" alt="Settings" src="https://github.com/xesdoog/YLP/blob/main/docs/img/screenshots/5.jpg">&nbsp;&nbsp;
    </a>
    <a href="https://github.com/xesdoog/YLP/blob/main/docs/img/screenshots/4.jpg">
        <img height="512" width="512" alt="Code Executor" src="https://github.com/xesdoog/YLP/blob/main/docs/img/screenshots/4.jpg">&nbsp;&nbsp;
    </a>
</div>

___

> [!Important]
> YLP is provided **as is**, without any warranty of any kind, express or implied.
> The author shall not be held liable for any damages, data loss, or issues arising from the use or misuse of this software.
