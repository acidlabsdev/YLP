<!-- markdownlint-disable -->

# YLP

### YLP namespace

## Methods

## ``

```lua
function YLP.() end
```

GetVersion

### Returns

| Type | Description |
| --- | --- |
| `string` | version The current YLP version. |

## ``

```lua
function YLP.(processName, callback, delay) end
```

RegisterProcessWatcher Registers a callback to be executed once when a process is first seen.

You can call `Task.Yield` and `Task.Sleep` in your callback function.

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `processName` | `string` | The name of the process |
| `callback` | `fun(process: Process)` | The function to execute. YLP will pass a Process object to the function as an argument. |
| `delay` | `integer?` | Optional delay in milliseconds |

### Returns

| Type | Description |
| --- | --- |
| `boolean` | success Whether the registration was successful or not. |

## ``

```lua
function YLP.(callback) end
```

RegisterGui Registers an ImGui callback to be drawn in the 'Lua Scripting' tab.

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `callback` | `function` | The UI to draw. ImGui functions can only be called here. |

## ``

```lua
function YLP.(dllPath, processName, manualMap, manualMapArgs) end
```

InjectDll Injects a dynamic link library into a target process.

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `dllPath` | `Path` | DLL file path. Must be a [Path](./Path.md) object. |
| `processName` | `string` | Name of the target process. |
| `manualMap` | `boolean?` | Use manual mapping instead of standard `LoadLibrary` |
| `manualMapArgs` | `{ eraseHeaders: boolean?, enableSEH: boolean?, randomizeBaseAddress: boolean?}?` | Optional manual mapping configuration. |

### Returns

| Type | Description |
| --- | --- |
| `boolean` | status Success or failure. |
| `string?` | failReason Optional error message if injection fails. |

## ``

```lua
function YLP.(callback) end
```

OnShutdown Registers a function to be executed when YLP is shutting down.

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `callback` | `function` | The function to execute |

## ``

```lua
function YLP.() end
```

UnloadThisModule Unloads the caller module.

The module can only be loaded again from the Settings tab in YLP's UI.
