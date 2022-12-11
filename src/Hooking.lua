Hooking = {}

function Hooking:include(includes)
    if includes:handle(self:name()) then
        includedirs {
            path.join(ProjectFolder(), "Hooking")
        }
    end
end

function Hooking:link(links)
    asmjit:link(links)
    zydis:link(links)
    links:add(self:name())
end

function Hooking:use()
    
end

function Hooking:name()
    return "Hooking"
end

function Hooking:project()
    if os.target() ~= "windows" then
        return
    end
    
    local folder = ProjectFolder()
    local includes = Includes:create()

    project(self:name())
        targetdir(TargetDirectoryLib)
        location "%{wks.location}/src/%{prj.name}"
        kind "StaticLib"
        language "C++"
        
        files {
            path.join(folder, "Hooking/**.h"), 
            path.join(folder, "Hooking/**.cpp") 
        }
        
        self:include(includes)
        asmjit:include(includes)
        zydis:include(includes)
end
