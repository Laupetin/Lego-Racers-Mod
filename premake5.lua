include "tools/scripts/folders.lua"
include "tools/scripts/including.lua"
include "tools/scripts/linking.lua"
include "tools/scripts/options.lua"
include "tools/scripts/platform.lua"

-- ==================
-- Workspace
-- ==================
workspace "LegoRacersMod"
    location "build"
    objdir "%{wks.location}/obj"
    symbols "On"
    systemversion "latest"
    cppdialect "C++17"

	flags {
		"MultiProcessorCompile"
	}

    configurations { 
        "Debug",
        "Release" 
    }

    platforms {
        "x86"
    }
    defaultplatform "x86"

    disablewarnings {
        "26812" -- Prefer enum class over unscoped
    }

    filter "platforms:x86"
        architecture "x86"
        defines "ARCH_x86"
    filter {}

    filter "configurations:Debug"
        defines "_DEBUG"
        optimize "Debug"
    filter {}

    filter "configurations:Release"
        defines "NDEBUG"
        optimize "Full"
        flags {
            "FatalWarnings"
        }
    filter {}

    defines {
        "__STDC_LIB_EXT1__",
        "__STDC_WANT_LIB_EXT1__=1",
        "_CRT_SECURE_NO_WARNINGS"
    }

-- ========================
-- ThirdParty
-- ========================
--include "thirdparty/sample.lua"

-- ThirdParty group: All projects that are external dependencies
group "ThirdParty"
    -- sample:project()
group ""

-- ========================
-- Projects
-- ========================
include "src/Utils.lua"
include "src/ProxyLibrary.lua"

-- Main projects
Utils:project()
ProxyLibrary:project()

-- ========================
-- Tests
-- ========================
-- include "test/sample.lua"

-- Tests group: Unit test and other tests projects
group "Tests"
    -- sample:project()
group ""