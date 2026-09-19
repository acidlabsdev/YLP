<!-- markdownlint-disable -->

# Path

A path object limited to the `/Plugins` folder

## Constructors

```lua
Path(path)
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `path` | `string` |  |
## Operators

### `div`

```lua
---@operator __div(string): Path
```

## Methods

## `Exists`

```lua
function Path:Exists() end
```

### Returns

| Type | Description |
| --- | --- |
| `boolean` |  |

## `IsFile`

```lua
function Path:IsFile() end
```

### Returns

| Type | Description |
| --- | --- |
| `boolean` |  |

## `IsDir`

```lua
function Path:IsDir() end
```

### Returns

| Type | Description |
| --- | --- |
| `boolean` |  |

## `GetFilename`

```lua
function Path:GetFilename() end
```

### Returns

| Type | Description |
| --- | --- |
| `string` |  |

## `GetExtension`

```lua
function Path:GetExtension() end
```

### Returns

| Type | Description |
| --- | --- |
| `string` | ext The file extension including the leading dot. Ex: `.json`. Returns empty string for folders. |

## `Join`

```lua
function Path:Join(subPath) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `subPath` | `string` |  |

### Returns

| Type | Description |
| --- | --- |
| `Path` |  |

## `Open`

```lua
function Path:Open(mode) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `mode` | `openmode?` |  |

### Returns

| Type | Description |
| --- | --- |
| `file*?` |  |
| `string` | failReason An error message if the operation fails. |

## `IterDir`

```lua
function Path:IterDir() end
```

Recursive directory iterator.

### Returns

| Type | Description |
| --- | --- |
| `fun():` | Path |

## `Sha256Sum`

```lua
function Path:Sha256Sum() end
```

Calculates the file's SHA256 checksum. Throws if the path is not a file.

### Returns

| Type | Description |
| --- | --- |
| `string` | hash SHA256 checksum |
