<!-- markdownlint-disable -->

# HTTP

Provides basic HTTP GET requests.

## Methods

## `Get`

```lua
function HTTP.Get(host, path, headers, outFile) end
```

Performs a web request. NOTE: this is synchronous so it's recommended to execute it in its own [Task](./Task)

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
