AssetLib = {}

function AssetLib:include(includes)
    if includes:handle(self:name()) then
        includedirs {
            path.join(ProjectFolder(), "AssetLib")
        }
    end
end

function AssetLib:link(links)
    links:add(self:name())
    Utils:link(links)
    antlr4:link(links)
end

function AssetLib:use()
end

function AssetLib:name()
    return "AssetLib"
end

function AssetLib:project()
    local folder = ProjectFolder()
    local includes = Includes:create()
    local links = Links:create()

    project(self:name())
        targetdir(TargetDirectoryLib)
        location "%{wks.location}/src/%{prj.name}"
        kind "StaticLib"
        language "C++"
        
        files {
            path.join(folder, "AssetLib/**.h"), 
            path.join(folder, "AssetLib/**.inc"), 
            path.join(folder, "AssetLib/**.cpp") 
        }
        
        local parserWildcard = path.join(folder, "AssetLib/Parsing/Parser/**.g4")
        if _OPTIONS["generate-parsers"] then
            antlr4:installJar()

            files {
                path.join(folder, "AssetLib/**.g4")
            }

            filter("files:" .. parserWildcard)	
                buildmessage "Generating code for grammar %{file.basename}"
                buildcommands {
                    'java -jar "%{wks.location}/antlr.jar" -lib "%{wks.location}/../src/AssetLib/Parsing/Common" -Xexact-output-dir -o "%{file.reldirectory}/." -Dlanguage=Cpp -package "%{file.basename:lower()}" "%{file.relpath}"'
                }
                buildoutputs {
                    "%{file.directory}/%{file.basename}BaseListener.h",
                    "%{file.directory}/%{file.basename}BaseListener.cpp",
                    "%{file.directory}/%{file.basename}Lexer.h",
                    "%{file.directory}/%{file.basename}Lexer.cpp",
                    "%{file.directory}/%{file.basename}Listener.h",
                    "%{file.directory}/%{file.basename}Listener.cpp",
                    "%{file.directory}/%{file.basename}Parser.h",
                    "%{file.directory}/%{file.basename}Parser.cpp",
                }
                buildinputs {
                    path.join(folder, "AssetLib/Parsing/Common/Common.g4") 
                }
            filter {}
        end

        for i, file in ipairs(os.matchfiles(parserWildcard)) do
            local dir = path.getdirectory(file)

            filter("files:" .. dir .. "/**.cpp")
                -- Disable warnings. They do not have any value to us since it is not our code (ANTLR4 generated).
                warnings "off"
            filter {}
        end
        
        self:include(includes)
        Utils:include(includes)
        antlr4:include(includes)
        jsonlib:include(includes)
end
