<!-- markdownlint-disable MD033 MD041 -->

<details>
  <summary><strong>Table of Contents</strong></summary>
  <ul>
    <li><a href="#about">About</a></li>
    <li><a href="#getting-started">Getting Started</a></li>
    <li><a href="#features">Features</a></li>
    <li><a href="#themes">Themes</a></li>
    <li><a href="#feedback">Feedback</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
    <li><a href="#faq">FAQ</a></li>
    <li><a href="#preview">Preview</a></li>
  </ul>
</details>
<br>

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

- Add custom DLL files and inject them into any process.
- Offers standard WinAPI `LoadLibrary` as well as manual mapping.
- Successfully injected files will remember their last target process and automatically select it if it's running.
- The DLL list can be interacted with in a similar way to any other regular window, not necessarily ImGui list behavior:
  - Hold and drag items to reorder the list.
  - Left click an item to highlight it.
  - Right click an item to bring up its context menu.
  - Left click an empty space to reset your currently selected item.
  - Right click an empty space to bring up the list's context menu.

### Built-in Lua Scripting

- Provides an optional LuaJIT scripting environment, unrelated to any game or mod.
- Feature can be toggled on/off at any time.
- All scripts placed in the `/Plugins` folder (`%AppData%\YLP\Plugins`) are automatically loaded on program start if the scripting feature is toggled on. Plugins must be placed in their own subfolders and have a main entry file named exactly `main.lua` *(case-sensitive)*.
- Lua code can also be directly typed and executed in the `Lua Scripting` UI tab.
- Visit the [Lua API](./docs/Lua%20API/Readme.md) docs section to learn more.

## Themes

Visit the [themes section](./docs/themes/Readme.md) to read more about UI themes.

## Feedback

Please submit any bug reports or feature suggestions on the [Issues](https://github.com/xesdoog/ylp/issues/new/choose) page.

## Acknowledgments

A huge thanks to the open source community and their immense contributions. You can find out more in the [Third Party](./docs/thirdparty/Readme.md) section

## FAQ

### Troubleshooting

- **Q:** I can't find `YLP.exe` in the injector tab's process list.
- **A:** Yes.

- **Q:** Manual Map injection crashed my game.
- **A:** This depends on the DLL file and the mapper's config. Some will break if you erase their PE headers, others must have structured exception handling setup, while others expect their delayed imports to be resolved which we currently don't do.

- **Q:** Auto-Inject shows a warning that says it was skipped.
- **A:** This can happen due to one of these reasons:
  1. BattlEye was detected: Simply disable it.
  2. The DLL file had an issue (deleted by AV, wrong signature, wrong architecture, etc.).
  3. Game version mismatch *(Legacy only)*: Auto-Inject will also be skipped if the latest DLL is outdated.
  4. The game loaded past the landing page: In this case, simply make sure the landing page is not disabled in your game settings.

### Security

- **Q:** Windows SmartScreen blocked YLP and said it *"protected my PC"*.
- **A:** This can happen when Windows doesn't have enough reputation information for an application, particularly when it is distributed independently and isn't digitally signed. It does **not** necessarily mean that the program contains malware. The only way for a developer to get around this is to purchase a code signing certificate. I can not afford it, and even if I could, there's no reason for me to buy it because this is just a hobby.

  If you downloaded an official release from this repository and trust it, you can select *"More info"* -> *"Run anyway"* in the SmartScreen dialog. If you're unsure where the file came from, **delete it instead**.

- **Q:** Why did my antivirus flag YLP?
- **A:** Some antivirus programs may flag YLP because it interacts directly with other applications, reads/writes their memory, and loads files into them. These are legitimate features required for YLP's modding and automation functionality, but they are also techniques that malware can abuse, so security software may treat them as suspicious.

  YLP is open source. Its releases can be independently inspected and built from the source code.

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
        <img height="256" width="256" alt="Code Executor" src="https://github.com/xesdoog/YLP/blob/main/docs/img/screenshots/4.jpg">&nbsp;&nbsp;
    </a>
</div>

___

> [!Important]
> YLP is provided **as is**, without any warranty of any kind, express or implied.
> The author shall not be held liable for any damages, data loss, or issues arising from the use or misuse of this software.
