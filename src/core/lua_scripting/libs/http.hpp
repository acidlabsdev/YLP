// Copyright (C) 2025 SAMURAI (xesdoog) & Contributors
// This file is part of YLP.
//
// YLP is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// YLP is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with YLP.  If not, see <https://www.gnu.org/licenses/>.


#pragma once

#include "../lua_library.hpp"
#include "../lua_module.hpp"
#include "../lua_path.hpp"


namespace YLP::LuaJIT
{
	using namespace YLP::Utils;

	class LuaHttpLib : public LuaLibrary
	{
		using LuaLibrary::LuaLibrary;

	public:
		void Register(sol::state& L) override
		{
			/* @ylp.table HTTP
			* description
				Provides basic HTTP GET requests.

			* function Get Performs a web request. NOTE: this is synchronous so it's recommended to execute it in its own [Task](lua://Task)
			* param host<string> URL host. Example: `github.com`
			* param path<string> URL path. Example: `/octocat/CoolRepo`
			* param headers<{ [integer]: string }?> Optional HTTP headers. Example: `{ "Content-Type: application/json", "Connection: keep-alive" }`
			* param outFile<Path?> Optional file destination to write to.
			* return HttpResponse response
			@*/
			auto httpTable = L["HTTP"].get_or_create<sol::table>();

			httpTable["Get"] = [](const std::string& host, const std::string& path, sol::optional<sol::table> optHeaders, sol::optional<LuaPath> outFile) {
				std::vector<std::wstring> headers{};
				if (optHeaders)
				{
					for (auto&& [i, v] : *optHeaders)
						headers.emplace_back(UTF8ToWide(v.as<std::string>() + "\r\n"));
				}

				const fs::path* writePath = outFile.has_value() ? &outFile.value().Get() : nullptr;
				return HttpRequest(UTF8ToWide(host), UTF8ToWide(path), headers, writePath);
			};


			/* @ylp.table HttpResponse
			* description
				Stores response data from the [HTTP](lua://HTTP) table.

			* field body string
			
			* field eTag string
			
			* field status integer
			
			* field success boolean
			@*/
			auto respTable = httpTable.new_usertype<HttpResponse>("HttpResponse",
			    sol::no_constructor,
			    // clang-format off
			    "body",    sol::readonly(&HttpResponse::body),
			    "eTag",    sol::readonly(&HttpResponse::eTag),
			    "status",  sol::readonly(&HttpResponse::status),
			    "success", sol::readonly(&HttpResponse::success)
				// clang-format on
			);
		};
	};

	LuaHttpLib _LuaHttpLib;
}
