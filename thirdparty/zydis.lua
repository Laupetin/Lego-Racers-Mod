zydis = {}

function zydis:include(includes)
	if includes:handle(self:name()) then
        zycore:include(includes)

        includedirs {
            path.join(ThirdPartyFolder(), "zydis/include"),
            path.join(ThirdPartyFolder(), "zydis/msvc")
        }

        defines {
            "ZYDIS_STATIC_BUILD"
        }
    end
end

function zydis:link(links)
	links:add(self:name())
end

function zydis:use()
	
end

function zydis:name()
    return "zydis"
end

function zydis:project()
    if os.target() ~= "windows" then
        return
    end
	
	local folder = ThirdPartyFolder()
	local includes = Includes:create()

	project(self:name())
        targetdir(TargetDirectoryLib)
		location "%{wks.location}/thirdparty/%{prj.name}"
		kind "StaticLib"
		language "C"
		
		files { 
			path.join(folder, "zydis/src/**.inc"),
			path.join(folder, "zydis/src/**.h"),
			path.join(folder, "zydis/src/**.c"),
			path.join(folder, "zydis/include/**.h")
        }

        removefiles {
			path.join(folder, "zydis/include/Formatter.h"),
			path.join(folder, "zydis/include/FormatterBuffer.h"),
			path.join(folder, "zydis/include/Encoder.h"),
			path.join(folder, "zydis/include/Internal/FormatterATT.h"),
			path.join(folder, "zydis/include/Internal/FormatterBase.h"),
			path.join(folder, "zydis/include/Internal/FormatterIntel.h"),
			path.join(folder, "zydis/include/Internal/EncoderData.h"),
			path.join(folder, "zydis/src/Formatter.c"),
			path.join(folder, "zydis/src/FormatterBuffer.c"),
			path.join(folder, "zydis/src/FormatterATT.c"),
			path.join(folder, "zydis/src/FormatterBase.c"),
			path.join(folder, "zydis/src/FormatterIntel.c"),
			path.join(folder, "zydis/src/Encoder.c"),
			path.join(folder, "zydis/src/EncoderData.c")
        }
        
        defines {
            "ZYDIS_EXPORTS",
            "ZYDIS_DISABLE_FORMATTER",
            "ZYDIS_DISABLE_AVX512",
            "ZYDIS_DISABLE_KNC",
            "ZYDIS_DISABLE_ENCODER",
            "_CRT_SECURE_NO_WARNINGS"
        }

        includedirs {
            path.join(ThirdPartyFolder(), "zydis/src")
        }
		
        self:include(includes)

		-- Disable warnings. They do not have any value to us since it is not our code.
		warnings "off"
end
