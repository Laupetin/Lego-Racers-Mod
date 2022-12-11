ProxyLibrary = {}

function ProxyLibrary:include(includes)
    if includes:handle(self:name()) then
        includedirs {
            path.join(ProjectFolder(), "ProxyLibrary")
        }
    end
end

function ProxyLibrary:link(links)
    
end

function ProxyLibrary:use()
    dependson(self:name())
end

function ProxyLibrary:name()
    return "ProxyLibrary"
end

function ProxyLibrary:project()
    if os.target() ~= "windows" then
        return
    end

    local folder = ProjectFolder()
    local includes = Includes:create()
    local links = Links:create()

    project(self:name())
        targetdir(TargetDirectoryBin)
        targetname "DINPUT"
        location "%{wks.location}/src/%{prj.name}"
        kind "SharedLib"
        language "C++"
        
        files {
            path.join(folder, "ProxyLibrary/**.h"), 
            path.join(folder, "ProxyLibrary/**.inc"), 
            path.join(folder, "ProxyLibrary/**.cpp") 
        }
        
        self:include(includes)
        Hooking:include(includes)
        Utils:include(includes)

        Hooking:link(links)
        Utils:link(links)
        links:linkall()
        
        -- Post-build
        if _OPTIONS["copy-to"] then
            saneCopyToPath = string.gsub(_OPTIONS["copy-to"] .. "\\", "\\\\", "\\")
            postbuildcommands {
                "if not exist \"" .. saneCopyToPath .. "\" mkdir \"" .. saneCopyToPath .. "\"",
            }

            -- This has to be the last one, as otherwise VisualStudio will succeed building even if copying fails
            postbuildcommands {
                "copy /y \"$(TargetDir)*.dll\" \"" .. saneCopyToPath .. "\"",
            }
        end
end
