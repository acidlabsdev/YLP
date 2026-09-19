<!-- markdownlint-disable -->

# Task

Provides functions to run tasks in YLP's thread.

## Methods

## ``

```lua
function Task.(callback) end
```

Run

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `callback` | `function` | The callback to execute |

## ``

```lua
function Task.(delay, callback) end
```

RunDelayed Execute a callback after a delay

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `delay` | `integer` | Delay in milliseconds |
| `callback` | `function` | The function to execute |

## ``

```lua
function Task.(ms) end
```

Sleep

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `ms` | `integer` | Sleep time in milliseconds |

## ``

```lua
function Task.(ms) end
```

Yield

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `ms` | `integer?` | Optional yield time in milliseconds |
