---@meta

-- Provides basic memory read/write functions.
-- 
-- It is exclusively returned by [Process](lua://Process) and can not be explicitly constructed.
---@class Pointer
---@operator (integer): Pointer
---@operator (integer): Pointer
Pointer = {}

-- Add
---@param offset integer The offset to add
---@return Pointer ptr A new pointer at the new address.
function Pointer:(offset) end

-- Sub
---@param offset integer The offset to subtract.
---@return Pointer ptr A new pointer at the new address.
function Pointer:(offset) end

-- Rip
---@return Pointer ptr A new pointer at the resolved RIP-relative address.
function Pointer:() end

-- Dereference
---@return Pointer ptr A new pointer at the dereferenced address.
function Pointer:() end

-- GetAddress
---@return integer address The pointer's memory address.
function Pointer:() end

-- IsNull
---@return boolean 
function Pointer:() end

-- AddBytePatch Creates a `BytePatch` object.
---@param byteArray {[integer]: integer} An array of bytes. Example: `{ 0x90, 0x90, 0x90 }`
---@param applyImmediately boolean? Optional: Apply the patch immediately.
---@return BytePatch? patch A `BytePatch` object or nil
function Pointer:(byteArray, applyImmediately) end

-- ReadBytes Reads up to `n` number of bytes
---@param numOfBytes integer Number of bytes to read.
---@return {[integer]: integer} byteArray An array of bytes
function Pointer:(numOfBytes) end

-- ReadString
---@return string 
function Pointer:() end

-- ReadInt8 Reads a signed 8bit integer
---@return integer s8 value
function Pointer:() end

-- ReadUint8 Reads an unsigned 8bit integer
---@return integer u8 value
function Pointer:() end

-- ReadInt16 Reads a signed 16bit integer
---@return integer s16 value
function Pointer:() end

-- ReadUint16 Reads an unsigned 16bit integer
---@return integer u16 value
function Pointer:() end

-- ReadInt32 Reads a signed 32bit integer
---@return integer s32 value
function Pointer:() end

-- ReadUint32 Reads an unsigned 32bit integer
---@return integer u32 value
function Pointer:() end

-- ReadInt64 Reads a signed 64bit integer
---@return integer s64 value
function Pointer:() end

-- ReadUint64 Reads an unsigned 64bit integer
---@return integer u64 value
function Pointer:() end

-- ReadFloat Reads a float
---@return number 
function Pointer:() end

-- ReadDouble Reads a double
---@return number 
function Pointer:() end

-- WriteBytes
---@param byteArray {[integer]: integer} An array of bytes.
---@return boolean success
function Pointer:(byteArray) end

-- WriteString
---@param str string 
---@return boolean success
function Pointer:(str) end

-- WriteInt8
---@param s8 integer 
---@return boolean success
function Pointer:(s8) end

-- WriteUint8
---@param u8 integer 
---@return boolean success
function Pointer:(u8) end

-- WriteInt16
---@param s16 integer 
---@return boolean success
function Pointer:(s16) end

-- WriteUint16
---@param u16 integer 
---@return boolean success
function Pointer:(u16) end

-- WriteInt32
---@param s32 integer 
---@return boolean success
function Pointer:(s32) end

-- WriteUint32
---@param u32 integer 
---@return boolean success
function Pointer:(u32) end

-- WriteInt64
---@param s64 integer 
---@return boolean success
function Pointer:(s64) end

-- WriteUint64
---@param u64 integer 
---@return boolean success
function Pointer:(u64) end

-- WriteFloat
---@param v number 
---@return boolean success
function Pointer:(v) end

-- WriteDouble
---@param v number 
---@return boolean 
function Pointer:(v) end
