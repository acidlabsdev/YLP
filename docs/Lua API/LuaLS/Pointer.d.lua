---@meta

-- Provides basic Pointer manipulation methods.
-- It is exclusively returned by [Process](lua://Process), it can not be explicitly constructed.
---@class Pointer
---@operator add(integer): Pointer
---@operator sub(integer): Pointer
Pointer = {}

---@param offset integer The offset to add
---@return Pointer -- A new pointer at the new address.
function Pointer:Add(offset) end

---@param offset integer The offset to subtract.
---@return Pointer -- A new pointer at the new address.
function Pointer:Sub(offset) end

---@return Pointer -- A new pointer at the resolved RIP-relative address.
function Pointer:Rip() end

---@return Pointer -- A new pointer at the dereferenced address.
function Pointer:Dereference() end

---@return integer address The pointer's memory address.
function Pointer:GetAddress() end

---@return boolean 
function Pointer:IsNull() end

---@return string 
function Pointer:ReadString() end

---@return integer 
function Pointer:ReadInt8() end

---@return integer 
function Pointer:ReadUint8() end

---@return integer 
function Pointer:ReadInt16() end

---@return integer 
function Pointer:ReadUint16() end

---@return integer 
function Pointer:ReadInt32() end

---@return integer 
function Pointer:ReadUint32() end

---@return integer 
function Pointer:ReadInt64() end

---@return integer 
function Pointer:ReadUint64() end

---@return number 
function Pointer:ReadFloat() end

---@return number 
function Pointer:ReadDouble() end

---@param arg string 
function Pointer:WriteString(arg) end

---@param arg integer 
function Pointer:WriteInt8(arg) end

---@param arg integer 
function Pointer:WriteUint8(arg) end

---@param arg integer 
function Pointer:WriteInt16(arg) end

---@param arg integer 
function Pointer:WriteUint16(arg) end

---@param arg integer 
function Pointer:WriteInt32(arg) end

---@param arg integer 
function Pointer:WriteUint32(arg) end

---@param arg integer 
function Pointer:WriteInt64(arg) end

---@param arg integer 
function Pointer:WriteUint64(arg) end

---@param arg number 
function Pointer:WriteFloat(arg) end

---@param arg number 
function Pointer:WriteDouble(arg) end

