asmjit = {}

function asmjit:include(includes)
	if includes:handle(self:name()) then
        defines {
            "ASMJIT_BUILD_X86",
            "ASMJIT_NO_DEPRECATED",
            "ASMJIT_EMBED",
            "ASMJIT_STATIC"
        }

        includedirs {
            path.join(ThirdPartyFolder(), "asmjit/src/asmjit")
        }
	end
end

function asmjit:link(links)
	links:add(self:name())
end

function asmjit:use()
	
end

function asmjit:name()
    return "asmjit"
end

function asmjit:project()
	local folder = ThirdPartyFolder()
	local includes = Includes:create()

	project(self:name())
        targetdir(TargetDirectoryLib)
		location "%{wks.location}/thirdparty/%{prj.name}"
		kind "StaticLib"
		language "C++"
		
		files { 
			path.join(folder, "asmjit/src/asmjit/**.h"),
			path.join(folder, "asmjit/src/asmjit/**.cpp")
		}
		
        self:include(includes)

		-- Disable warnings. They do not have any value to us since it is not our code.
		warnings "off"
end
