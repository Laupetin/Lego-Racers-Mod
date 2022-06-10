antlr4 = {}

function antlr4:include(includes)
	if includes:handle(self:name()) then
        defines {
            "ANTLR4CPP_STATIC"
        }

        includedirs {
            path.join(ThirdPartyFolder(), "antlr4/runtime/Cpp/runtime/src")
        }
	end
end

function antlr4:link(links)
	links:add(self:name())
end

function antlr4:use()
	
end

function antlr4:name()
    return "libantlr4"
end

function antlr4:project()
	local folder = ThirdPartyFolder()
	local includes = Includes:create()

	project(self:name())
        targetdir(TargetDirectoryLib)
		location "%{wks.location}/thirdparty/%{prj.name}"
		kind "StaticLib"
		language "C++"
		
		files { 
			path.join(folder, "antlr4/runtime/Cpp/runtime/src/**.h"),
			path.join(folder, "antlr4/runtime/Cpp/runtime/src/**.cpp"),
		}
		
        self:include(includes)

		-- Disable warnings. They do not have any value to us since it is not our code.
		warnings "off"
end

function antlr4:installJar()
	local version = "4.10.1"
	local versionFile = path.join(BuildFolder(), "antlr-version.txt")
	local antlrFile = path.join(BuildFolder(), "antlr.jar")
	local url = "http://www.antlr.org/download/antlr-4.10.1-complete.jar"

	local installedVersion = io.readfile(versionFile)
	if os.isfile(antlrFile) and installedVersion == version then
		return
	end

	function progress(total, current)		
		local ratio = current / total;
		ratio = math.min(math.max(ratio, 0), 1);
		local percent = math.floor(ratio * 100);
		io.write("\rDownload progress (" .. percent .. "%/100%)")
	end

	print("Downloading ANTLR4 " .. version .. "...")
	local result_str, response_code = http.download(url, antlrFile, {
		progress = progress
	})

	io.write("\n")
	
	if result_str ~= "OK" then
		premake.error("Failed to download ANTRL4")
	end

	io.writefile(versionFile, version)
end