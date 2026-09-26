# GTA V ScriptGlobal Implementation Demo

This example demonstrates how the API can be used to externally read and write GTA 5 script globals.

```Lua
local SG_PTR ---@type Pointer?

------------------------------------
------------------------------------
------------------------------------

---@class ScriptGlobal
---@field private m_ptr Pointer
---@overload fun(address: integer): ScriptGlobal
local ScriptGlobal = setmetatable({}, {
    __call = function(t, address)
        return t:new(address)
    end
}); ScriptGlobal.__index = ScriptGlobal

---@param ptr Pointer
---@return ScriptGlobal
local function fromptr(ptr)
    ---@diagnostic disable-next-line
    return setmetatable({ m_ptr = ptr }, ScriptGlobal)
end

---@param index integer
---@return ScriptGlobal
function ScriptGlobal:new(index)
    assert(SG_PTR and not SG_PTR:IsNull(), "Globals table pointer is null!")
    assert(type(index) == "number", "Address must be an integer.")
    return setmetatable({
        m_ptr = SG_PTR:Add(((index >> 0x12) & 0x3F) * 8):Dereference():Add((index & 0x3FFFF) * 8)
    }, self)
end

---@nodiscard
---@return boolean
function ScriptGlobal:IsValid()
    return self.m_ptr:GetAddress() >= 0x1000
end

---@param offset number
function ScriptGlobal:At(offset)
    return fromptr(self.m_ptr:Add(offset * 8))
end

---@return integer
function ScriptGlobal:GetAddress()
    return self.m_ptr:GetAddress()
end

-- For the sake of demonstrtion, we're only going to define a `ReadFloat` method.
--
-- You can add all read/write methods from the [Pointer](lua://Pointer) class.
---@return number
function ScriptGlobal:ReadFloat()
    return self.m_ptr:ReadFloat()
end

----------------------------------------
----------------------------------------
----------------------------------------

local function test()
    local fKickVotesNeededRatio = ScriptGlobal(262145):At(6)
    if (not fKickVotesNeededRatio:IsValid()) then
        log.warning("Please reload the script after loading into a game mode.")
        return
    end

    printf("fKickVotesNeededRatio: %.2ff", fKickVotesNeededRatio:ReadFloat())
end

YLP.RegisterProcessWatcher("GTA5.exe", function(process)
    local ptr = process:FindPattern("48 8D 15 ? ? ? ? 4C 8B C0 E8 ? ? ? ? 48 85 FF 48 89 1D", "Script Globals")
    if (ptr:IsNull()) then
        return
    end

    SG_PTR = ptr:Add(0x3):Rip()
    test()
end)
```
