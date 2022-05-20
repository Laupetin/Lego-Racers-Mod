zycore = {}

function zycore:include(includes)
	if includes:handle(self:name()) then
        includedirs {
            path.join(ThirdPartyFolder(), "zydis/dependencies/zycore/include"),
            path.join(ThirdPartyFolder(), "zydis/msvc")
        }

        defines {
            "ZYCORE_STATIC_BUILD"
        }
	end
end

function zycore:link(links)
	links:add(self:name())
end

function zycore:use()
	
end

function zycore:name()
    return "zycore"
end

function zycore:project()
	local folder = ThirdPartyFolder()
	local includes = Includes:create()

	project(self:name())
        targetdir(TargetDirectoryLib)
		location "%{wks.location}/thirdparty/%{prj.name}"
		kind "StaticLib"
		language "C"
		
		files { 
			path.join(folder, "zydis/dependencies/zycore/src/**.c"),
			path.join(folder, "zydis/dependencies/zycore/include/**.h")
        }
        
        defines {
            "ZYCORE_EXPORTS",
            "_CRT_SECURE_NO_WARNINGS"
        }
		
		self:include(includes)

		-- Disable warnings. They do not have any value to us since it is not our code.
		warnings "off"
end
