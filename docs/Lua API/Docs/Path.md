<!-- markdownlint-disable -->

# Path

A path object limited to the `/Plugins` folder

## Constructors

## ``

```lua
function Path:(path) end
```

__call

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `path` | `string` |  |

__call

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `path` | `string` |  |
## Operators

### ``

```lua
---@operator __(string): Path
```

div

## Methods

## ``

```lua
function Path:() end
```

Exists

### Returns

| Type | Description |
| --- | --- |
| `boolean` |  |

## ``

```lua
function Path:() end
```

IsFile

### Returns

| Type | Description |
| --- | --- |
| `boolean` |  |

## ``

```lua
function Path:() end
```

IsDir

### Returns

| Type | Description |
| --- | --- |
| `boolean` |  |

## ``

```lua
function Path:() end
```

GetFilename

### Returns

| Type | Description |
| --- | --- |
| `string` |  |

## ``

```lua
function Path:() end
```

GetExtension

### Returns

| Type | Description |
| --- | --- |
| `string` | ext The file extension including the leading dot. Ex: `.json`. Returns empty string for folders. |

## ``

```lua
function Path:(subPath) end
```

Join

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `subPath` | `string` |  |

### Returns

| Type | Description |
| --- | --- |
| `Path` |  |

## ``

```lua
function Path:(mode) end
```

Open

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `mode` | `openmode?` |  |

### Returns

| Type | Description |
| --- | --- |
| `file*?` |  |
| `string` | failReason An error message if the operation fails. |

## ``

```lua
function Path:() end
```

IterDir Recursive directory iterator.

### Returns

| Type | Description |
| --- | --- |
| `fun():` | Path |

## ``

```lua
function Path:() end
```

Sha256Sum Calculates the file's SHA256 checksum. Throws if the path is not a file.

### Returns

| Type | Description |
| --- | --- |
| `string` | hash SHA256 checksum |
