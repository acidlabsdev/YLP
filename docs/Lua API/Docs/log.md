# log

Provides functions to output text to console and log file.

## Methods

## `info`

```lua
function log.(...) end
```

Logs an information message.

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `...` | `any` | Any number of arguments of any type. |

## `warning`

```lua
function log.(...) end
```

Logs a warning message.

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `...` | `any` | Any number of arguments of any type. |

## `debug`

```lua
function log.(...) end
```

Logs a debug message.

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `...` | `any` | Any number of arguments of any type. |

## `error`

```lua
function log.(...) end
```

Logs an error message.

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `...` | `any` | Any number of arguments of any type. |

## `finfo`

```lua
function log.(msg, ...) end
```

Logs a formatted information message. Arguments are the same as `string.format`

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `msg` | `string` | Message. |
| `...` | `any` | Optional format arguments. |

## `fwarning`

```lua
function log.(msg, ...) end
```

Logs a formatted warning message. Arguments are the same as `string.format`

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `msg` | `string` | Message. |
| `...` | `any` | Optional format arguments. |

## `fdebug`

```lua
function log.(msg, ...) end
```

Logs a formatted debug message. Arguments are the same as `string.format`

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `msg` | `string` | Message. |
| `...` | `any` | Optional format arguments. |

## `ferror`

```lua
function log.(msg, ...) end
```

Logs a formatted error message. Arguments are the same as `string.format`

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `msg` | `string` | Message. |
| `...` | `any` | Optional format arguments. |
