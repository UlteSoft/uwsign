set_xmakever("2.9.8")

set_project("uwsign")

-- Version
set_version("1.0.0.0")
add_defines("UWSIGN_VERSION_X=1")
add_defines("UWSIGN_VERSION_Y=0")
add_defines("UWSIGN_VERSION_Z=0")
add_defines("UWSIGN_VERSION_S=0")

set_allowedplats("windows", "mingw", "cygwin", "linux", "djgpp", "unix", "bsd", "freebsd", "dragonflybsd", "netbsd",
	"openbsd", "macosx", "iphoneos", "watchos", "wasm-wasi", "wasm-wasip1", "wasm-wasip2", "wasm-wasip3",
	"wasm-wasi-threads", "wasm-wasip1-threads", "wasm-wasip2-threads", "wasm-wasip3-threads", "wasm-emscripten",
	"serenity", "sun", "cross", "none")

includes("xmake/impl.lua")
includes("xmake/platform/impl.lua")
add_moduledirs("xmake")

-- Currently, there are no plugins.
-- add_plugindirs("xmake/plugins")

set_defaultmode("release")
set_allowedmodes(support_rules_table)

function def_build(opt)
	opt = opt or {}
	if is_mode("debug") then
		add_rules("debug")
	elseif is_mode("release") then
		add_rules("release")
	elseif is_mode("minsizerel") then
		add_rules("minsizerel")
	elseif is_mode("releasedbg") then
		add_rules("releasedbg")
	end

	set_languages("c23", "cxx26")

	set_encodings("utf-8")
	set_warnings("all", "extra", "pedantic", "error")

	local enable_cxx_module = get_config("use-cxx-module")
	if enable_cxx_module then
		add_defines("UWSIGN_MODULE")
		add_cxflags("-std=c++26", { force = true })
		set_policy("build.c++.modules", true)
		-- set_policy("build.c++.modules.std", true)
	end

	local use_stdlib = get_config("stdlib")
	if use_stdlib ~= "default" and use_stdlib then
		local flags = "-stdlib=" .. use_stdlib
		add_cxflags(flags)
		add_ldflags(flags)
	end

	if is_plat("windows") then
		windows_target()
	elseif is_plat("mingw") then
		mingw_target()
	elseif is_plat("linux") then
		linux_target()
	elseif is_plat("macosx", "iphoneos", "watchos") then
		darwin_target(opt)
	elseif is_plat("djgpp") then
		djgpp_target()
	elseif is_plat("unix", "bsd", "freebsd", "dragonflybsd", "netbsd", "openbsd") then
		bsd_target()
	elseif is_plat("wasm-wasi", "wasm-wasip1", "wasm-wasip2", "wasm-wasip3", "wasm-wasi-threads", "wasm-wasip1-threads", "wasm-wasip2-threads", "wasm-wasip3-threads") then
		wasm_wasi_target()
	elseif is_plat("wasm-emscripten") then
		wasm_emscripten_target()
	elseif is_plat("cygwin") then
		cygwin_target()
	elseif is_plat("none") then
		none_target()
	end

	local use_llvm_compiler = get_config("use-llvm-compiler")
	if use_llvm_compiler then
		local llvm_target = get_config("llvm-target")
		if llvm_target ~= "detect" and llvm_target then
			local llvm_target_cvt = "--target=" .. llvm_target
			add_cxflags(llvm_target_cvt, { force = true })
			add_ldflags(llvm_target_cvt, { force = true })
		end

		-- Since neither LLVM nor Wextra supports this parameter by default, this addition prevents compilation.
		add_cxflags("-Wimplicit-fallthrough", { force = true })
	else
		-- Keep the non-LLVM toolchain path portable: some Clang builds do not
		-- recognize this warning class at all, which turns the suppression into a
		-- hard error under `-Werror`.
	end

	before_build(
		function(target)
			try
			{
				function()
					local function git_available()
						local result = os.iorun("git --version")
						return result and not result:find("fatal:") and not result:find("not found")
					end

					local function is_git_repo()
						if not git_available() then return false end
						local result = os.iorun("git rev-parse --is-inside-work-tree")
						return result and result:trim() == "true"
					end

					if not git_available() or not is_git_repo() then
						return
					end

					-- General Git commands execute functions and return results or nil
					local function git_command(cmd)
						local result = os.iorun(cmd)
						if result and not result:find("fatal:") then
							return result:trim()
						end
						return nil
					end

					-- Get Commit ID
					local commit_id = git_command("git rev-parse HEAD") or "unknown"

					-- Get the current branch name (may be empty, such as the separation HEAD status)
					local current_branch = git_command("git branch --show-current")

					-- Dynamically resolve the associated remote name
					local remote_name = nil
					if current_branch then
						-- Get the traced remote name through git config
						remote_name = git_command("git config branch." .. current_branch .. ".remote")
					end

					-- If the remote name is not found, try to resolve it through HEAD upstream
					local upstream_branch = git_command("git rev-parse --abbrev-ref --symbolic-full-name HEAD") or "unknown"
					if not remote_name then
						local upstream_branch_tmp = git_command("git rev-parse --abbrev-ref --symbolic-full-name @{u}")
						if upstream_branch_tmp then
							-- Resolve the remote name of the upstream branch (format: remote_name/branch_name)
							remote_name = upstream_branch_tmp:match("^(.-)/")
						end
					end

					-- If there is still no remote name, go back to the first remote or default value
					local remote_url = "unknown"
					if remote_name then
						remote_url = git_command("git remote get-url " .. remote_name) or "unknown"
					else
						-- Get all remote lists, the first one
						local remotes = git_command("git remote")
						if remotes then
							local first_remote = remotes:match("[^\r\n]+")
							if first_remote then
								remote_url = git_command("git remote get-url " .. first_remote) or "unknown"
							end
						end
					end

					-- Get submission timestamp (UTC)
					local timestamp_str = git_command("git log -1 --format=%ct HEAD")
					local timestamp = tonumber(timestamp_str) or 0

					-- Convert timestamp to date string (UTC time zone)
					local commit_date = "unknown"
					if timestamp > 0 then
						commit_date = os.date("!%Y-%m-%d", timestamp) -- Attention '! 'means forcing UTC
					end

					local is_dirty = false
					local status_output = git_command("git status --porcelain")
					if status_output and status_output ~= "" then
						is_dirty = true -- There are uncommitted modifications or untracked files
					end

					target:add("defines", "UWSIGN_GIT_COMMIT_ID=u8\"" .. commit_id .. "\"")
					target:add("defines", "UWSIGN_GIT_REMOTE_URL=u8\"" .. remote_url .. "\"")
					target:add("defines", "UWSIGN_GIT_COMMIT_DATA=u8\"" .. commit_date .. "\"")
					target:add("defines", "UWSIGN_GIT_UPSTREAM_BRANCH=u8\"" .. upstream_branch .. "\"")
					if is_dirty then
						target:add("defines", "UWSIGN_GIT_HAS_UNCOMMITTED_MODIFICATIONS")
					end
				end,
				catch
				{
					function()
						return nil
					end
				}
			}
		end
	)
end

target("uwsign")
	set_kind("binary")
	def_build()

	-- uwsign uses precise floating-point model to ensure determinism.
	set_fpmodels("precise") 

	local is_debug_mode = is_mode("debug")  -- public all modules in debug mode
	local enable_cxx_module = get_config("use-cxx-module")

	-- third-parties/fast_io
	add_includedirs("third-parties/fast_io/include")

	if not is_plat("wasm-wasi", "wasm-wasip1", "wasm-wasip2", "wasm-wasip3", "wasm-wasi-threads", "wasm-wasip1-threads", "wasm-wasip2-threads", "wasm-wasip3-threads", "wasm-emscripten", "none") then
		for _, openssl_prefix in ipairs({"/opt/homebrew/opt/openssl@3", "/usr/local/opt/openssl@3"}) do
			local openssl_include = path.join(openssl_prefix, "include")
			local openssl_lib = path.join(openssl_prefix, "lib")
			if os.isdir(openssl_include) then
				add_includedirs(openssl_include, { system = true })
			end
			if os.isdir(openssl_lib) then
				add_linkdirs(openssl_lib)
			end
		end
		add_links("ssl", "crypto")
	end

	if enable_cxx_module then
		add_files("third-parties/fast_io/share/fast_io/fast_io.cppm", { public = is_debug_mode })
		add_files("third-parties/fast_io/share/fast_io/fast_io_crypto.cppm", { public = is_debug_mode })
	end

	-- uwsign
	add_defines("UWSIGN")

	-- src
	add_includedirs("src/")

	add_headerfiles("src/**.h")

	if enable_cxx_module then
		add_files("src/uwsign/**.cppm", { public = is_debug_mode })
		-- uwsign main
		add_files("src/uwsign/uwsign/main.module.cpp")
	else
		-- uwsign main
		add_files("src/uwsign/uwsign/main.default.cpp")
	end

target_end()

target("uwsign_wasm_signature_section_test")
	set_kind("binary")
	def_build({skip_static_libcxx = true})

	add_includedirs("third-parties/fast_io/include")
	add_includedirs("src/")
	add_files("test/wasm_signature_section_test.cc")
target_end()
