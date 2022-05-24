JamFileTool = {}

function JamFileTool:include(includes)
	if includes:handle(self:name()) then
		includedirs {
			path.join(ProjectFolder(), "JamFileTool")
		}
	end
end

function JamFileTool:link(links)
    
end

function JamFileTool:use()
    dependson(self:name())
end

function JamFileTool:name()
	return "JamFileTool"
end

function JamFileTool:project()
	local folder = ProjectFolder()
	local includes = Includes:create()
	local links = Links:create()

	project(self:name())
        targetdir(TargetDirectoryBin)
		location "%{wks.location}/src/%{prj.name}"
		kind "ConsoleApp"
		language "C++"
		
		files {
			path.join(folder, "JamFileTool/**.h"), 
			path.join(folder, "JamFileTool/**.inc"), 
			path.join(folder, "JamFileTool/**.cpp") 
		}
		
		self:include(includes)
		Utils:include(includes)

		Utils:link(links)
		links:linkall()
end
