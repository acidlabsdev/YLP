---@meta

---@class ImGui
ImGui = {}

---@param id integer 
function ImGui.PushID(id) end

function ImGui.PopID() end

function ImGui.Bullet() end

---@param text string 
function ImGui.Text(text) end

---@param text string 
function ImGui.TextDisabled(text) end

---@param text string 
function ImGui.TextWrapped(text) end

---@param text string 
function ImGui.TextUnformatted(text) end

---@param text string 
function ImGui.BulletText(text) end

---@param r number A number between `0.0` and `1.0` representing the `Red` component of the color.
---@param g number A number between `0.0` and `1.0` representing the `Green` component of the color.
---@param b number A number between `0.0` and `1.0` representing the `Blue` component of the color.
---@param a number A number between `0.0` and `1.0` representing the `Alpha` component of the color.
---@param text string 
function ImGui.TextColored(r, g, b, a, text) end

---@param label string 
---@param sizeX number? Optional button width
---@param sizeY number? Optional button height
---@return boolean clicked
function ImGui.Button(label, sizeX, sizeY) end

---@param label string 
---@return boolean clicked
function ImGui.SmallButton(label) end

---@param label string 
---@param direction integer [ImGuiDir](lua://ImGuiDir)
---@return boolean clicked
function ImGui.ArrowButton(label, direction) end

---@param label string 
---@param sizeX number Button width
---@param sizeY number Button height
---@return boolean clicked
function ImGui.InvisibleButton(label, sizeX, sizeY) end

---@param label string 
---@param v boolean 
---@return boolean value
---@return boolean clicked
function ImGui.Checkbox(label, v) end

---@param label string 
---@param active boolean 
---@return boolean clicked
function ImGui.RadioButton(label, active) end

---@param label string 
---@param v integer Current index
---@param vButton integer Index to change to
---@return integer newValue
---@return boolean clicked
function ImGui.RadioButton(label, v, vButton) end

---@param fraction number 
---@param sizeX number? Optional frame width
---@param sizeY number? Optional frame height
---@param overlayText string? Optional overlay text. Defaults to precentage.
function ImGui.ProgressBar(fraction, sizeX, sizeY, overlayText) end

---@param label string 
---@param currentItem integer 
---@param itemsSeparatedByZeros string A string with items separated by null terminators. Ex: `"Item1\0Item2\0Item3"`
---@return integer currentItem
---@return boolean opened
function ImGui.Combo(label, currentItem, itemsSeparatedByZeros) end

---@param label string 
---@param preview string 
---@param flags integer? Optional [ImGuiComboFlags](lua://ImGuiComboFlags)
---@return boolean opened
function ImGui.BeginCombo(label, preview, flags) end

function ImGui.EndCombo() end

---@param name string 
---@param sizeX number? Optional child width.
---@param sizeY number? Optional child height.
---@param childFlags integer? Optional [ImGuiChildFlags](lua://ImGuiChildFlags)
---@param windowFlags integer? Optional [ImGuiWindowFlags](lua://ImGuiWindowFlags)
---@return boolean visible
function ImGui.BeginChild(name, sizeX, sizeY, childFlags, windowFlags) end

function ImGui.EndChild() end

---@param offsetX number Optional X position to start at. Defaults to `0`.
---@param spacing number Optional spacing after the previous item. Defaults to the current item spacing.
function ImGui.SameLine(offsetX, spacing) end

function ImGui.NewLine() end

function ImGui.Spacing() end

function ImGui.Separator() end

---@param flags integer [ImGuiSeparatorFlags](lua://ImGuiSeparatorFlags)
---@param thickness number 
function ImGui.SeparatorEx(flags, thickness) end

---@param flags integer [ImGuiSeparatorFlags](lua://ImGuiSeparatorFlags)
---@param thickness number 
function ImGui.SeparatorEx(flags, thickness) end

---@param indentX number? Optional indentation width. Defaults to the current item spacing.
function ImGui.Indent(indentX) end

---@param indentX number? Optional indentation width. Defaults to the current item spacing.
function ImGui.Unindent(indentX) end

---@param sizeX number Width of the dummy item.
---@param sizeY number Height of the dummy item.
function ImGui.Dummy(sizeX, sizeY) end

---@param x number X position relative to the current window.
---@param y number Y position relative to the current window.
function ImGui.SetCursorPos(x, y) end

---@param x number X position relative to the current window.
function ImGui.SetCursorPosX(x) end

---@param y number Y position relative to the current window.
function ImGui.SetCursorPosY(y) end

---@return number x Current X position relative to the current window.
---@return number y Current Y position relative to the current window.
function ImGui.GetCursorPos() end

---@return number x Current X position relative to the current window.
function ImGui.GetCursorPosX() end

---@return number y Current Y position relative to the current window.
function ImGui.GetCursorPosY() end

---@return number x Available width in the current content region.
---@return number y Available height in the current content region.
function ImGui.GetContentRegionAvail() end

---@return number x Current window width.
---@return number y Current window height.
function ImGui.GetWindowSize() end

---@return number x Current window X position.
---@return number y Current window Y position.
function ImGui.GetWindowPos() end

---@param width number Width of the next item.
function ImGui.SetNextItemWidth(width) end

---@param width number Width of subsequent items.
function ImGui.PushItemWidth(width) end

function ImGui.PopItemWidth() end

---@param styleVar integer [ImGuiStyleVar](lua://ImGuiStyleVar) index
---@param v number style value
function ImGui.PushStyleVar(styleVar, v) end

---@param styleVar integer [ImGuiStyleVar](lua://ImGuiStyleVar) index
---@param vX number x value
---@param vY number y value
function ImGui.PushStyleVar(styleVar, vX, vY) end

---@param count integer? Count of pushed style variables to pop. Defaults to 1; Must match the number of pushed style vars.
function ImGui.PopStyleVar(count) end

---@param colIdx integer [ImGuiCol](lua://ImGuiCol) index
---@param r number A number between `0.0` and `1.0` representing the `Red` component of the color.
---@param g number A number between `0.0` and `1.0` representing the `Green` component of the color.
---@param b number A number between `0.0` and `1.0` representing the `Blue` component of the color.
---@param a number A number between `0.0` and `1.0` representing the `Alpha` component of the color.
function ImGui.PushStyleColor(colIdx, r, g, b, a) end

---@param count integer? Count of pushed style colors to pop. Defaults to 1; Must match the number of pushed style cols.
function ImGui.PopStyleColor(count) end

---@param cursorIdx integer [ImGuiMouseCursor](lua://ImGuiMouseCursor) index
function ImGui.PopStyleColor(cursorIdx) end
