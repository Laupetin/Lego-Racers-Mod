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
		
		if _OPTIONS["generate-parsers"] then
			antlr4:installJar()

			files {
				path.join(folder, "JamFileTool/**.g4")
			}

			filter "files:**.g4"
				buildmessage "Generating code for grammar %{file.basename}"
				buildcommands {
					'java -jar "%{wks.location}/antlr.jar" -Xexact-output-dir -o "%{file.reldirectory}/Parser" -Dlanguage=Cpp -package "%{file.basename:lower()}" "%{file.relpath}"'
				}
				buildoutputs {
					"%{file.directory}/Parser/%{file.basename}BaseListener.h",
					"%{file.directory}/Parser/%{file.basename}BaseListener.cpp",
					"%{file.directory}/Parser/%{file.basename}Lexer.h",
					"%{file.directory}/Parser/%{file.basename}Lexer.cpp",
					"%{file.directory}/Parser/%{file.basename}Listener.h",
					"%{file.directory}/Parser/%{file.basename}Listener.cpp",
					"%{file.directory}/Parser/%{file.basename}Parser.h",
					"%{file.directory}/Parser/%{file.basename}Parser.cpp",
				}
			filter {}
		end

		for i, file in ipairs(os.matchfiles(path.join(folder, "JamFileTool/**.g4"))) do
			local dir = path.getdirectory(file)

			filter("files:" .. dir .. "/**")
				-- Disable warnings. They do not have any value to us since it is not our code (ANTLR4 generated).
				warnings "off"
			filter {}
        end
		
		self:include(includes)
		Utils:include(includes)
		antlr4:include(includes)

		Utils:link(links)
		antlr4:link(links)
		links:linkall()
end
