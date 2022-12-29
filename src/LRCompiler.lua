LRCompiler = {}

function LRCompiler:include(includes)
    if includes:handle(self:name()) then
        includedirs {
            path.join(ProjectFolder(), "LRCompiler")
        }
    end
end

function LRCompiler:link(links)
end

function LRCompiler:use()
    dependson(self:name())
end

function LRCompiler:name()
    return "LRCompiler"
end

function LRCompiler:project()
    local folder = ProjectFolder()
    local includes = Includes:create()
    local links = Links:create()

    project(self:name())
        targetdir(TargetDirectoryBin)
        targetname "lrcompile"
        location "%{wks.location}/src/%{prj.name}"
        kind "ConsoleApp"
        language "C++"
        
        files {
            path.join(folder, "LRCompiler/**.h"),
            path.join(folder, "LRCompiler/**.cpp") 
        }
              
        self:include(includes)
        AssetLib:include(includes)
        jsonlib:include(includes)
        Utils:include(includes)

        AssetLib:link(links)
        Utils:link(links)
        links:linkall()
end
