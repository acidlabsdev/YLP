# Pointer

Provides basic Pointer manipulation methods.
It is exclusively returned by [Process](lua://Process), it can not be explicitly constructed.

## Operators

### `add`

```lua
---@operator __add(integer): Pointer
```

### `sub`

```lua
---@operator __sub(integer): Pointer
```

## Methods

## `Add`

```lua
function Pointer:(offset) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `offset` | `integer` | The offset to add |

### Returns

| Type | Description |
| --- | --- |
| `Pointer` | ptr A new pointer at the new address. |

## `Sub`

```lua
function Pointer:(offset) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `offset` | `integer` | The offset to subtract. |

### Returns

| Type | Description |
| --- | --- |
| `Pointer` | ptr A new pointer at the new address. |

## `Rip`

```lua
function Pointer:() end
```

### Returns

| Type | Description |
| --- | --- |
| `Pointer` | ptr A new pointer at the resolved RIP-relative address. |

## `Dereference`

```lua
function Pointer:() end
```

### Returns

| Type | Description |
| --- | --- |
| `Pointer` | ptr A new pointer at the dereferenced address. |

## `GetAddress`

```lua
function Pointer:() end
```

### Returns

| Type | Description |
| --- | --- |
| `integer` | address The pointer's memory address. |

## `IsNull`

```lua
function Pointer:() end
```

### Returns

| Type | Description |
| --- | --- |
| `boolean` |  |

## `ReadInt8`

```lua
function Pointer:() end
```

### Returns

| Type | Description |
| --- | --- |
| `integer` |  |

## `ReadInt16`

```lua
function Pointer:() end
```

### Returns

| Type | Description |
| --- | --- |
| `integer` |  |

## `ReadInt32`

```lua
function Pointer:() end
```

### Returns

| Type | Description |
| --- | --- |
| `integer` |  |

## `ReadInt64`

```lua
function Pointer:() end
```

### Returns

| Type | Description |
| --- | --- |
| `integer` |  |

## `ReadFloat`

```lua
function Pointer:() end
```

### Returns

| Type | Description |
| --- | --- |
| `number` |  |

## `WriteString`

```lua
function Pointer:(arg) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `arg` | `string` |  |

## `WriteUint8`

```lua
function Pointer:(arg) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `arg` | `integer` |  |

## `WriteUint16`

```lua
function Pointer:(arg) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `arg` | `integer` |  |

## `WriteUint32`

```lua
function Pointer:(arg) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `arg` | `integer` |  |

## `WriteUint64`

```lua
function Pointer:(arg) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `arg` | `integer` |  |

## `WriteDouble`

```lua
function Pointer:(arg) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `arg` | `number` |  |
