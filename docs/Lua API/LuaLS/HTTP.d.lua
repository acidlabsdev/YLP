---@meta

-- Provides basic HTTP GET requests.
---@class HTTP
HTTP = {}

-- Performs a web request. NOTE: this is synchronous so it's recommended to execute it in its own [Task](lua://Task)
---@param host string URL host. Example: `github.com`
---@param path string URL path. Example: `/octocat/CoolRepo`
---@param headers { [integer]: string }? Optional HTTP headers. Example: `{ "Content-Type: application/json", "Connection: keep-alive" }`
---@param outFile Path? Optional file destination to write to.
---@return HttpResponse response
function HTTP.Get(host, path, headers, outFile) end
