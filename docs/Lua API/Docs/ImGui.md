<!-- markdownlint-disable -->

# ImGui

## Methods

## `PushID`

```lua
function ImGui.PushID(id) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `id` | `integer` |  |

## `PopID`

```lua
function ImGui.PopID() end
```

## `Bullet`

```lua
function ImGui.Bullet() end
```

## `Text`

```lua
function ImGui.Text(text) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `text` | `string` |  |

## `TextDisabled`

```lua
function ImGui.TextDisabled(text) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `text` | `string` |  |

## `TextWrapped`

```lua
function ImGui.TextWrapped(text) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `text` | `string` |  |

## `TextUnformatted`

```lua
function ImGui.TextUnformatted(text) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `text` | `string` |  |

## `BulletText`

```lua
function ImGui.BulletText(text) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `text` | `string` |  |

## `TextColored`

```lua
function ImGui.TextColored(r, g, b, a, text) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `r` | `number` | A number between `0.0` and `1.0` representing the `Red` component of the color. |
| `g` | `number` | A number between `0.0` and `1.0` representing the `Green` component of the color. |
| `b` | `number` | A number between `0.0` and `1.0` representing the `Blue` component of the color. |
| `a` | `number` | A number between `0.0` and `1.0` representing the `Alpha` component of the color. |
| `text` | `string` |  |

## `Button`

```lua
function ImGui.Button(label, sizeX, sizeY) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `label` | `string` |  |
| `sizeX` | `number?` | Optional button width |
| `sizeY` | `number?` | Optional button height |

### Returns

| Type | Description |
| --- | --- |
| `boolean` | clicked |

## `SmallButton`

```lua
function ImGui.SmallButton(label) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `label` | `string` |  |

### Returns

| Type | Description |
| --- | --- |
| `boolean` | clicked |

## `ArrowButton`

```lua
function ImGui.ArrowButton(label, direction) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `label` | `string` |  |
| `direction` | `integer` | [ImGuiDir](./ImGuiDir.md) |

### Returns

| Type | Description |
| --- | --- |
| `boolean` | clicked |

## `InvisibleButton`

```lua
function ImGui.InvisibleButton(label, sizeX, sizeY) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `label` | `string` |  |
| `sizeX` | `number` | Button width |
| `sizeY` | `number` | Button height |

### Returns

| Type | Description |
| --- | --- |
| `boolean` | clicked |

## `Checkbox`

```lua
function ImGui.Checkbox(label, v) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `label` | `string` |  |
| `v` | `boolean` |  |

### Returns

| Type | Description |
| --- | --- |
| `boolean` | value |
| `boolean` | clicked |

## `RadioButton`

```lua
function ImGui.RadioButton(label, active) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `label` | `string` |  |
| `active` | `boolean` |  |

### Returns

| Type | Description |
| --- | --- |
| `boolean` | clicked |

## `RadioButton`

```lua
function ImGui.RadioButton(label, v, vButton) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `label` | `string` |  |
| `v` | `integer` | Current index |
| `vButton` | `integer` | Index to change to |

### Returns

| Type | Description |
| --- | --- |
| `integer` | newValue |
| `boolean` | clicked |

## `ProgressBar`

```lua
function ImGui.ProgressBar(fraction, sizeX, sizeY, overlayText) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `fraction` | `number` |  |
| `sizeX` | `number?` | Optional frame width |
| `sizeY` | `number?` | Optional frame height |
| `overlayText` | `string?` | Optional overlay text. Defaults to precentage. |

## `Combo`

```lua
function ImGui.Combo(label, currentItem, itemsSeparatedByZeros) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `label` | `string` |  |
| `currentItem` | `integer` |  |
| `itemsSeparatedByZeros` | `string` | A string with items separated by null terminators. Ex: `"Item1\0Item2\0Item3"` |

### Returns

| Type | Description |
| --- | --- |
| `integer` | currentItem |
| `boolean` | opened |

## `BeginCombo`

```lua
function ImGui.BeginCombo(label, preview, flags) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `label` | `string` |  |
| `preview` | `string` |  |
| `flags` | `integer?` | Optional [ImGuiComboFlags](./ImGuiComboFlags.md) |

### Returns

| Type | Description |
| --- | --- |
| `boolean` | opened |

## `EndCombo`

```lua
function ImGui.EndCombo() end
```

## `BeginChild`

```lua
function ImGui.BeginChild(name, sizeX, sizeY, childFlags, windowFlags) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `name` | `string` |  |
| `sizeX` | `number?` | Optional child width. |
| `sizeY` | `number?` | Optional child height. |
| `childFlags` | `integer?` | Optional [ImGuiChildFlags](./ImGuiChildFlags.md) |
| `windowFlags` | `integer?` | Optional [ImGuiWindowFlags](./ImGuiWindowFlags.md) |

### Returns

| Type | Description |
| --- | --- |
| `boolean` | visible |

## `EndChild`

```lua
function ImGui.EndChild() end
```

## `SameLine`

```lua
function ImGui.SameLine(offsetX, spacing) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `offsetX` | `number` | Optional X position to start at. Defaults to `0`. |
| `spacing` | `number` | Optional spacing after the previous item. Defaults to the current item spacing. |

## `NewLine`

```lua
function ImGui.NewLine() end
```

## `Spacing`

```lua
function ImGui.Spacing() end
```

## `Separator`

```lua
function ImGui.Separator() end
```

## `SeparatorEx`

```lua
function ImGui.SeparatorEx(flags, thickness) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `flags` | `integer` | [ImGuiSeparatorFlags](./ImGuiSeparatorFlags.md) |
| `thickness` | `number` |  |

## `SeparatorEx`

```lua
function ImGui.SeparatorEx(flags, thickness) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `flags` | `integer` | [ImGuiSeparatorFlags](./ImGuiSeparatorFlags.md) |
| `thickness` | `number` |  |

## `Indent`

```lua
function ImGui.Indent(indentX) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `indentX` | `number?` | Optional indentation width. Defaults to the current item spacing. |

## `Unindent`

```lua
function ImGui.Unindent(indentX) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `indentX` | `number?` | Optional indentation width. Defaults to the current item spacing. |

## `Dummy`

```lua
function ImGui.Dummy(sizeX, sizeY) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `sizeX` | `number` | Width of the dummy item. |
| `sizeY` | `number` | Height of the dummy item. |

## `SetCursorPos`

```lua
function ImGui.SetCursorPos(x, y) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `x` | `number` | X position relative to the current window. |
| `y` | `number` | Y position relative to the current window. |

## `SetCursorPosX`

```lua
function ImGui.SetCursorPosX(x) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `x` | `number` | X position relative to the current window. |

## `SetCursorPosY`

```lua
function ImGui.SetCursorPosY(y) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `y` | `number` | Y position relative to the current window. |

## `GetCursorPos`

```lua
function ImGui.GetCursorPos() end
```

### Returns

| Type | Description |
| --- | --- |
| `number` | x Current X position relative to the current window. |
| `number` | y Current Y position relative to the current window. |

## `GetCursorPosX`

```lua
function ImGui.GetCursorPosX() end
```

### Returns

| Type | Description |
| --- | --- |
| `number` | x Current X position relative to the current window. |

## `GetCursorPosY`

```lua
function ImGui.GetCursorPosY() end
```

### Returns

| Type | Description |
| --- | --- |
| `number` | y Current Y position relative to the current window. |

## `GetContentRegionAvail`

```lua
function ImGui.GetContentRegionAvail() end
```

### Returns

| Type | Description |
| --- | --- |
| `number` | x Available width in the current content region. |
| `number` | y Available height in the current content region. |

## `GetWindowSize`

```lua
function ImGui.GetWindowSize() end
```

### Returns

| Type | Description |
| --- | --- |
| `number` | x Current window width. |
| `number` | y Current window height. |

## `GetWindowPos`

```lua
function ImGui.GetWindowPos() end
```

### Returns

| Type | Description |
| --- | --- |
| `number` | x Current window X position. |
| `number` | y Current window Y position. |

## `SetNextItemWidth`

```lua
function ImGui.SetNextItemWidth(width) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `width` | `number` | Width of the next item. |

## `PushItemWidth`

```lua
function ImGui.PushItemWidth(width) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `width` | `number` | Width of subsequent items. |

## `PopItemWidth`

```lua
function ImGui.PopItemWidth() end
```

## `PushStyleVar`

```lua
function ImGui.PushStyleVar(styleVar, v) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `styleVar` | `integer` | [ImGuiStyleVar](./ImGuiStyleVar.md) index |
| `v` | `number` | style value |

## `PushStyleVar`

```lua
function ImGui.PushStyleVar(styleVar, vX, vY) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `styleVar` | `integer` | [ImGuiStyleVar](./ImGuiStyleVar.md) index |
| `vX` | `number` | x value |
| `vY` | `number` | y value |

## `PopStyleVar`

```lua
function ImGui.PopStyleVar(count) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `count` | `integer?` | Count of pushed style variables to pop. Defaults to 1; Must match the number of pushed style vars. |

## `PushStyleColor`

```lua
function ImGui.PushStyleColor(colIdx, r, g, b, a) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `colIdx` | `integer` | [ImGuiCol](./ImGuiCol.md) index |
| `r` | `number` | A number between `0.0` and `1.0` representing the `Red` component of the color. |
| `g` | `number` | A number between `0.0` and `1.0` representing the `Green` component of the color. |
| `b` | `number` | A number between `0.0` and `1.0` representing the `Blue` component of the color. |
| `a` | `number` | A number between `0.0` and `1.0` representing the `Alpha` component of the color. |

## `PopStyleColor`

```lua
function ImGui.PopStyleColor(count) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `count` | `integer?` | Count of pushed style colors to pop. Defaults to 1; Must match the number of pushed style cols. |

## `PopStyleColor`

```lua
function ImGui.PopStyleColor(cursorIdx) end
```

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `cursorIdx` | `integer` | [ImGuiMouseCursor](./ImGuiMouseCursor.md) index |
