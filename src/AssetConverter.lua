AssetConverter = {}

function AssetConverter:include(includes)
    if includes:handle(self:name()) then
        includedirs {
            path.join(ProjectFolder(), "AssetConverter")
        }
    end
end

function AssetConverter:link(links)
    
end

function AssetConverter:use()
    dependson(self:name())
end

function AssetConverter:name()
    return "AssetConverter"
end

function AssetConverter:project()
    local folder = ProjectFolder()
    local includes = Includes:create()
    local links = Links:create()

    project(self:name())
        targetdir(TargetDirectoryBin)
        location "%{wks.location}/src/%{prj.name}"
        kind "ConsoleApp"
        language "C++"
        
        files {
            path.join(folder, "AssetConverter/**.h"),
            path.join(folder, "AssetConverter/**.cpp") 
        }
        
        self:include(includes)
        Utils:include(includes)

        Utils:link(links)
        links:linkall()
end
