<!-- markdownlint-disable MD046 -->

# Builtin LuaJIT

> [!Warning]
> The scripting feature is **disabled** by default. It is highly recommended to only enable it if you trust the source of the code you intend to execute.

## About

YLP offers power-users the ability to extend its functionality however they like through a LuaJIT environment.

During the lifetime of this project, a few requests have been made to add support for other mods and/or add new functionality outside the project's scope. The thing is, no matter the framework one ends up creating *(especially as someone who's not a programmer)*, it will never satisfy everyone's needs; and so the decision was made, despite the potential risks, to embed a scripting language that's both tiny and powerful.

Since most of YLP's users are technical enough and almost all of them come from the GTA modding scene, it made perfect sense to choose Lua *(also dev bias)*.

As of now, the API is in its baby stage so expect bugs and possibly undefined behavior.

## Plugin Structure

Lua plugins must be placed in their own subfolders inside `%AppData%\YLP\Plugins` and **must** have a main entry file named `main.lua`. You can have as many subfolders and files as you want inside your plugin directory, but only main.lua will be automatically loaded when YLP starts. Example:

```bash
├─ YLP/
│  ├─ Plugins/
│  │  ├─ disabled/      # disabled modules.
│  │  ├─ shared/        # shared modules that can be imported by any plugin. You can place icons.lua from "docs/Lua API/shared" in this folder to use Icons in your ImGui code.
│  │  └─ MyCustomPlugin # Your plugin.
│  │     ├─ includes/   # Optional subfolder to neatly store any other files that may be required by your plugin. Folder name and contents do not matter to YLP.
│  │     └─ main.lua    # Your plugin's entry point. Without this file, your plugin will not be loaded.
```

## Usage Example

A few example scripts can be found in the [Examples](./Examples/) folder.

For advanced users, the `JIT` and `FFI` libs are open. `debug` is not. If you experience crashes/instability with certain shared modules *(JSON/XML parsers, web scrapers, etc.)* try disabling jit either for those specific modules only or for your entire plugin.

## Language Server

To have type hints in your code editor, follow these steps:

1. Install Lua Language Server *([VS Code Extension](https://marketplace.visualstudio.com/items?itemName=sumneko.lua), [GitHub repository](https://github.com/LuaLS/lua-language-server))*.
2. Download the [/LuaLS](./LuaLS/) folder and place it in `%AppData%\YLP\Plugins\shared`.
3. For Visual Studio Code users, create a `.code-workspace` file in your plugin folder *(next to your `main.lua` file)* and paste this in it:

    ```JSON
    {
        "folders": [
            {
                "path": ".",
            },
        ],
        "settings": {
            "Lua.runtime.version": "LuaJIT",
            "Lua.runtime.enableLuaJITExtensions": true,
            "Lua.workspace.checkThirdParty": false,
            "Lua.workspace.library": [
                "../shared"
            ],
            "Lua.runtime.builtin": {
                "debug": "disable"
            },
        }
    }
    ```

## API Docs

Documentation for YLP's bindings are in the [/Docs](./Docs/) folder.

## LuaJIT Version Specification

The embedded version is v2.1 with 3.0 extensions backport. These extensions include:

- **Bit Operators:**

    ```Lua
    local x = a & b
    local y = a | b
    local z = a ~ b
    local w = ~a
    local foo = a << 4
    local bar = a >> 2
    local baz = a ~>> 0
    ```

- **C-style Operators:**

    ```Lua
    if a != b then ... end
    if !value then ... end
    if a && b then ... end
    if a || b then ... end
    ```

- **Ternary:**

    ```Lua
    local x = condition ? first : second
    ```

- **`nil` Coalescing:**

    ```Lua
    local x = value ?? fallback
    local y = maybeTable?.value
    local z = Class:MaybeMethod?(args)
    ```

- **Compound Assignment:**

    ```Lua
    i += 1
    bs &= mask
    str ..= "foo"
    ```

- **Other Additions:**

    ```Lua
    continue
    const x = 123
    local fn = (x, y) => x + y
    local n = 1_000_000
    ```

You can learn more about 3.0 extensions at [LuaJIT#1475](https://github.com/LuaJIT/LuaJIT/issues/1475).
