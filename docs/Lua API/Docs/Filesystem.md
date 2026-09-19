<!-- markdownlint-disable -->

# Filesystem

Provides file system functions. Paths are limited to the `/Plugins` folder only.

## Fields

| Name | Type | Description |
| --- | --- | --- |
| `Path` | `Path` | The Path class. |

## Methods

## ``

```lua
function Filesystem.() end
```

MyRoot Returns the module's root path.

### Returns

| Type | Description |
| --- | --- |
| `Path` |  |

## ``

```lua
function Filesystem.(path) end
```

IterDir Recursive directory iterator.

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `path` | `Path` |  |

### Returns

| Type | Description |
| --- | --- |
| `fun():` | Path |

## ``

```lua
function Filesystem.(oldPath, newPath) end
```

Rename

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `oldPath` | `Path` |  |
| `newPath` | `Path` |  |

### Returns

| Type | Description |
| --- | --- |
| `boolean` | successOrFailure |
| `string` | failReason |

## ``

```lua
function Filesystem.(path) end
```

Remove

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `path` | `Path` |  |

### Returns

| Type | Description |
| --- | --- |
| `boolean` | successOrFailure |
| `string` | failReason |
