<!-- markdownlint-disable -->

# HTTP

Provides basic HTTP GET requests.

## Methods

## ``

```lua
function HTTP.(host, path, headers, outFile) end
```

Get Performs a web request. NOTE: this is synchronous so it's recommended to execute it in its own [Task](./Task.md)

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `host` | `string` | URL host. Example: `github.com` |
| `path` | `string` | URL path. Example: `/octocat/CoolRepo` |
| `headers` | `{ [integer]: string }?` | Optional HTTP headers. Example: `{ "Content-Type: application/json", "Connection: keep-alive" }` |
| `outFile` | `Path?` | Optional file destination to write to. |

### Returns

| Type | Description |
| --- | --- |
| `HttpResponse` | response |
