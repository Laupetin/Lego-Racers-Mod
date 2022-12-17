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

    filter "platforms:x64"
        architecture "x86_64"
        defines "ARCH_x64"
    filter {}

    filter "system:windows"
        defines "OS_TARGET_WINDOWS"
    filter {}

    filter "system:linux"
        defines "OS_TARGET_LINUX"
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
        "_CRT_SECURE_NO_WARNINGS",
        "NOMINMAX"
    }

-- ========================
-- ThirdParty
-- ========================
include "thirdparty/antlr4.lua"
include "thirdparty/asmjit.lua"
include "thirdparty/catch2.lua"
include "thirdparty/jsonlib.lua"
include "thirdparty/zycore.lua"
include "thirdparty/zydis.lua"

-- ThirdParty group: All projects that are external dependencies
group "ThirdParty"
    antlr4:project()
    asmjit:project()
    catch2:project()
    jsonlib:project()
    zycore:project()
    zydis:project()
group ""

-- ========================
-- Components
-- ========================
include "src/AssetLib.lua"
include "src/Hooking.lua"
include "src/Utils.lua"

-- Components group: All projects that are static libs for executables
group "Components"
    AssetLib:project()
    Hooking:project()
    Utils:project()
group ""


-- ========================
-- Executables
-- ========================
include "src/AssetConverter.lua"
include "src/JamFileTool.lua"
include "src/LRCompiler.lua"
include "src/ProxyLibrary.lua"

-- Main projects
AssetConverter:project()
JamFileTool:project()
LRCompiler:project()
ProxyLibrary:project()

-- ========================
-- Tests
-- ========================
include "test/AssetLibTests.lua"

-- Tests group: Unit test and other tests projects
group "Tests"
    AssetLibTests:project()
group ""