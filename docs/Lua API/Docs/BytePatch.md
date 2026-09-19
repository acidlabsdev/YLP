<!-- markdownlint-disable -->

# BytePatch

Provides an abstraction around byte patching.

It is exclusively returned by [Pointer](./Pointer.md) and can not be explicitly constructed.

## Methods

## ``

```lua
function BytePatch:() end
```

Apply Applies the patch to the target pointer's memory.

### Returns

| Type | Description |
| --- | --- |
| `boolean` | success Success or failure. |

## ``

```lua
function BytePatch:() end
```

Restore Restores the target pointer's original bytes.

### Returns

| Type | Description |
| --- | --- |
| `boolean` | success Success or failure. |

## ``

```lua
function BytePatch:() end
```

IsApplied Whether this patch is currently applied.

### Returns

| Type | Description |
| --- | --- |
| `boolean` |  |
