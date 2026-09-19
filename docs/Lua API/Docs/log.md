<!-- markdownlint-disable -->

# log

Provides functions to output text to console and log file.

## Methods

## ``

```lua
function log.(...) end
```

info Logs an information message.

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `...` | `any` | Any number of arguments of any type. |

## ``

```lua
function log.(...) end
```

warning Logs a warning message.

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `...` | `any` | Any number of arguments of any type. |

## ``

```lua
function log.(...) end
```

debug Logs a debug message.

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `...` | `any` | Any number of arguments of any type. |

## ``

```lua
function log.(...) end
```

error Logs an error message.

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `...` | `any` | Any number of arguments of any type. |

## ``

```lua
function log.(msg, ...) end
```

finfo Logs a formatted information message. Arguments are the same as `string.format`

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `msg` | `string` | Message. |
| `...` | `any` | Optional format arguments. |

## ``

```lua
function log.(msg, ...) end
```

fwarning Logs a formatted warning message. Arguments are the same as `string.format`

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `msg` | `string` | Message. |
| `...` | `any` | Optional format arguments. |

## ``

```lua
function log.(msg, ...) end
```

fdebug Logs a formatted debug message. Arguments are the same as `string.format`

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `msg` | `string` | Message. |
| `...` | `any` | Optional format arguments. |

## ``

```lua
function log.(msg, ...) end
```

ferror Logs a formatted error message. Arguments are the same as `string.format`

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `msg` | `string` | Message. |
| `...` | `any` | Optional format arguments. |
