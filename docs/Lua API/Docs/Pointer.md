<!-- markdownlint-disable -->

# Pointer

Provides basic memory read/write functions.

It is exclusively returned by [Process](./Process.md) and can not be explicitly constructed.

## Operators

### ``

```lua
---@operator __(integer): Pointer
```

add

### ``

```lua
---@operator __(integer): Pointer
```

sub

## Methods

## ``

```lua
function Pointer:(offset) end
```

Add

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `offset` | `integer` | The offset to add |

### Returns

| Type | Description |
| --- | --- |
| `Pointer` | ptr A new pointer at the new address. |

## ``

```lua
function Pointer:(offset) end
```

Sub

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `offset` | `integer` | The offset to subtract. |

### Returns

| Type | Description |
| --- | --- |
| `Pointer` | ptr A new pointer at the new address. |

## ``

```lua
function Pointer:() end
```

Rip

### Returns

| Type | Description |
| --- | --- |
| `Pointer` | ptr A new pointer at the resolved RIP-relative address. |

## ``

```lua
function Pointer:() end
```

Dereference

### Returns

| Type | Description |
| --- | --- |
| `Pointer` | ptr A new pointer at the dereferenced address. |

## ``

```lua
function Pointer:() end
```

GetAddress

### Returns

| Type | Description |
| --- | --- |
| `integer` | address The pointer's memory address. |

## ``

```lua
function Pointer:() end
```

IsNull

### Returns

| Type | Description |
| --- | --- |
| `boolean` |  |

## ``

```lua
function Pointer:(byteArray, applyImmediately) end
```

AddBytePatch Creates a `BytePatch` object.

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `byteArray` | `{[integer]: integer}` | An array of bytes. Example: `{ 0x90, 0x90, 0x90 }` |
| `applyImmediately` | `boolean?` | Optional: Apply the patch immediately. |

### Returns

| Type | Description |
| --- | --- |
| `BytePatch?` | patch A `BytePatch` object or nil |

## ``

```lua
function Pointer:(numOfBytes) end
```

ReadBytes Reads up to `n` number of bytes

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `numOfBytes` | `integer` | Number of bytes to read. |

### Returns

| Type | Description |
| --- | --- |
| `{[integer]:` | integer} byteArray An array of bytes |

## ``

```lua
function Pointer:() end
```

ReadString

### Returns

| Type | Description |
| --- | --- |
| `string` |  |

## ``

```lua
function Pointer:() end
```

ReadInt8 Reads a signed 8bit integer

### Returns

| Type | Description |
| --- | --- |
| `integer` | s8 value |

## ``

```lua
function Pointer:() end
```

ReadUint8 Reads an unsigned 8bit integer

### Returns

| Type | Description |
| --- | --- |
| `integer` | u8 value |

## ``

```lua
function Pointer:() end
```

ReadInt16 Reads a signed 16bit integer

### Returns

| Type | Description |
| --- | --- |
| `integer` | s16 value |

## ``

```lua
function Pointer:() end
```

ReadUint16 Reads an unsigned 16bit integer

### Returns

| Type | Description |
| --- | --- |
| `integer` | u16 value |

## ``

```lua
function Pointer:() end
```

ReadInt32 Reads a signed 32bit integer

### Returns

| Type | Description |
| --- | --- |
| `integer` | s32 value |

## ``

```lua
function Pointer:() end
```

ReadUint32 Reads an unsigned 32bit integer

### Returns

| Type | Description |
| --- | --- |
| `integer` | u32 value |

## ``

```lua
function Pointer:() end
```

ReadInt64 Reads a signed 64bit integer

### Returns

| Type | Description |
| --- | --- |
| `integer` | s64 value |

## ``

```lua
function Pointer:() end
```

ReadUint64 Reads an unsigned 64bit integer

### Returns

| Type | Description |
| --- | --- |
| `integer` | u64 value |

## ``

```lua
function Pointer:() end
```

ReadFloat Reads a float

### Returns

| Type | Description |
| --- | --- |
| `number` |  |

## ``

```lua
function Pointer:() end
```

ReadDouble Reads a double

### Returns

| Type | Description |
| --- | --- |
| `number` |  |

## ``

```lua
function Pointer:(byteArray) end
```

WriteBytes

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `byteArray` | `{[integer]: integer}` | An array of bytes. |

### Returns

| Type | Description |
| --- | --- |
| `boolean` | success |

## ``

```lua
function Pointer:(str) end
```

WriteString

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `str` | `string` |  |

### Returns

| Type | Description |
| --- | --- |
| `boolean` | success |

## ``

```lua
function Pointer:(s8) end
```

WriteInt8

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `s8` | `integer` |  |

### Returns

| Type | Description |
| --- | --- |
| `boolean` | success |

## ``

```lua
function Pointer:(u8) end
```

WriteUint8

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `u8` | `integer` |  |

### Returns

| Type | Description |
| --- | --- |
| `boolean` | success |

## ``

```lua
function Pointer:(s16) end
```

WriteInt16

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `s16` | `integer` |  |

### Returns

| Type | Description |
| --- | --- |
| `boolean` | success |

## ``

```lua
function Pointer:(u16) end
```

WriteUint16

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `u16` | `integer` |  |

### Returns

| Type | Description |
| --- | --- |
| `boolean` | success |

## ``

```lua
function Pointer:(s32) end
```

WriteInt32

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `s32` | `integer` |  |

### Returns

| Type | Description |
| --- | --- |
| `boolean` | success |

## ``

```lua
function Pointer:(u32) end
```

WriteUint32

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `u32` | `integer` |  |

### Returns

| Type | Description |
| --- | --- |
| `boolean` | success |

## ``

```lua
function Pointer:(s64) end
```

WriteInt64

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `s64` | `integer` |  |

### Returns

| Type | Description |
| --- | --- |
| `boolean` | success |

## ``

```lua
function Pointer:(u64) end
```

WriteUint64

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `u64` | `integer` |  |

### Returns

| Type | Description |
| --- | --- |
| `boolean` | success |

## ``

```lua
function Pointer:(v) end
```

WriteFloat

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `v` | `number` |  |

### Returns

| Type | Description |
| --- | --- |
| `boolean` | success |

## ``

```lua
function Pointer:(v) end
```

WriteDouble

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `v` | `number` |  |

### Returns

| Type | Description |
| --- | --- |
| `boolean` |  |
