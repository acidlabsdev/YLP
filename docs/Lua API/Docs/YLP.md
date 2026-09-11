# YLP

### YLP namespace

## Methods

## `GetVersion`

```lua
function YLP.GetVersion() end
```

### Returns

| Type | Description |
| --- | --- |
| `string` | version The current YLP version. |

## `RegisterProcessWatcher`

```lua
function YLP.RegisterProcessWatcher(processName, callback, delay) end
```

Registers a callback to be executed once when a process is first seen.

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

## `InjectDll`

```lua
function YLP.InjectDll(dllPath, processName) end
```

Injects a dynamic link library into a target process.

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `dllPath` | `string` | Path to the DLL file. |
| `processName` | `string` | Name of the target process. |

### Returns

| Type | Description |
| --- | --- |
| `boolean` | status Success or failure. |
| `string?` | failReason Optional error message if injection fails. |

## `OnShutdown`

```lua
function YLP.OnShutdown(callback) end
```

Registers a function to be executed when YLP is shutting down.

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `callback` | `function` | The function to execute |
