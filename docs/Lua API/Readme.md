# Builtin LuaJIT

YLP offers power-users the ability to extend its functionality however they like through a LuaJIT environment.

During the lifetime of this project, a few requests have been made to add support for other mods and/or add new functionality unrelated to YLP's focus. The thing is, no matter the framework one ends up creating, it will never satisfy everyone's needs; and so the decision was made, despite the potential dangers of doing so, to embed a scripting language that's both tiny and powerful. Since most YLP users are technical enough and almost all of them come from the GTA modding scene, it made perfect sense to choose Lua *(also dev bias)*.

Right now, the API is in its baby stage. It doesn't have much going on but eventually it will grow.

For advanced users, the JIT and FFI libs are open. os, io, and debug are not.

> [!Warning]
> The scripting feature is **disabled** by default. It is highly recommended to only enable it if you know what you're doing or trust the source of the code you intend to execute.
>
> If someone asks you to paste code and execute it or tries to trick you into loading arbitrary scripts, you have the right to beat their ass *(metaphorically of course, I don't want another GitHub warning)*.

## Implementation

The current version is v2.1 with 3.0 extensions backport. These extensions include:

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
    local z = Class:MaybeMethod.?(args)
    ```

- **Compound Assignment:**

    ```Lua
    x += 1
    x &= mask
    x ..= "foo"
    ```

- **Other Additions:**

    ```Lua
    continue
    const x = 123
    local fn = (x, y) => x + y
    local n = 1_000_000
    ```

___

You can learn more about 3.0 extensions on [LuaJIT#1475](https://github.com/LuaJIT/LuaJIT/issues/1475).

Documentation for YLP's bindings are in the [/Docs](./Docs/) folder and language server stubs are in the [/LuaLS](./LuaLS/) folder.
