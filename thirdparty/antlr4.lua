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
