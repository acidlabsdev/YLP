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
function Pointer:Add(offset) end
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
function Pointer:Sub(offset) end
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
function Pointer:Rip() end
```

### Returns

| Type | Description |
| --- | --- |
| `Pointer` | ptr A new pointer at the resolved RIP-relative address. |

## `Dereference`

```lua
function Pointer:Dereference() end
```

### Returns

| Type | Description |
| --- | --- |
| `Pointer` | ptr A new pointer at the dereferenced address. |

## `GetAddress`

```lua
function Pointer:GetAddress() end
```

### Returns

| Type | Description |
| --- | --- |
| `integer` | address The pointer's memory address. |

## `IsNull`

```lua
function Pointer:IsNull() end
```

### Returns

| Type | Description |
| --- | --- |
| `boolean` |  |

## `ReadInt8`

```lua
function Pointer:ReadInt8() end
```

### Returns

| Type | Description |
| --- | --- |
| `integer` |  |

## `ReadInt16`

```lua
function Pointer:ReadInt16() end
```

### Returns

| Type | Description |
| --- | --- |
| `integer` |  |

## `ReadInt32`

```lua
function Pointer:ReadInt32() end
```

### Returns

| Type | Description |
| --- | --- |
| `integer` |  |

## `ReadInt64`

```lua
function Pointer:ReadInt64() end
```

### Returns

| Type | Description |
| --- | --- |
| `integer` |  |

## `ReadFloat`

```lua
function Pointer:ReadFloat() end
```

### Returns

| Type | Description |
| --- | --- |
| `number` |  |

## `WriteString`

```lua
function Pointer:WriteString(arg) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `arg` | `string` |  |

## `WriteUint8`

```lua
function Pointer:WriteUint8(arg) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `arg` | `integer` |  |

## `WriteUint16`

```lua
function Pointer:WriteUint16(arg) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `arg` | `integer` |  |

## `WriteUint32`

```lua
function Pointer:WriteUint32(arg) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `arg` | `integer` |  |

## `WriteUint64`

```lua
function Pointer:WriteUint64(arg) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `arg` | `integer` |  |

## `WriteDouble`

```lua
function Pointer:WriteDouble(arg) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `arg` | `number` |  |
