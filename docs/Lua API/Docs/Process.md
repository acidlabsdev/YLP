<!-- markdownlint-disable -->

# Process

A process abstraction providing basic process interactions.

## Constructors

## ``

```lua
function Process:(processName) end
```

__call

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `processName` | `string` |  |

__call

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `processName` | `string` |  |
## Methods

## ``

```lua
function Process:() end
```

IsRunning

### Returns

| Type | Description |
| --- | --- |
| `boolean` |  |

## ``

```lua
function Process:(moduleName) end
```

IsModuleLoaded

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `moduleName` | `string` | Name of the module. Example: `"kernelbase.dll"` |

### Returns

| Type | Description |
| --- | --- |
| `boolean` |  |

## ``

```lua
function Process:() end
```

GetModuleSize

### Returns

| Type | Description |
| --- | --- |
| `integer` |  |

## ``

```lua
function Process:() end
```

GetModuleBase

### Returns

| Type | Description |
| --- | --- |
| `integer` | -- The module's base address |

## ``

```lua
function Process:() end
```

Update Updates the process object's internal state. This is useful because the `Process` class does not poll for status on its own.

## ``

```lua
function Process:(pattern, name, chunkSize) end
```

FindPattern

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `pattern` | `string` | IDA-style byte signature. Example: `"8B 88 C0 ?? ?? ?? 89 8F"` |
| `name` | `string?` | Optional name of the pattern to scan. Purely for logging purposes. |
| `chunkSize` | `integer?` | Optional memory chunk size. Defaults to 4096 |

### Returns

| Type | Description |
| --- | --- |
| `Pointer` | ptr A pointer at the found address or a null pointer if the scan fails. This is guaranteed to always return a Pointer object. |
