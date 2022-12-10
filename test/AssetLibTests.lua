AssetLibTests = {}

function AssetLibTests:include(includes)
	if includes:handle(self:name()) then
		includedirs {
			path.join(TestFolder(), "AssetLibTests")
		}
	end
end

function AssetLibTests:link(links)
end

function AssetLibTests:use()
end

function AssetLibTests:name()
    return "AssetLibTests"
end

function AssetLibTests:project()
	local folder = TestFolder()
	local includes = Includes:create()
	local links = Links:create()

	project(self:name())
        targetdir(TargetDirectoryTest)
		location "%{wks.location}/test/%{prj.name}"
		kind "ConsoleApp"
		language "C++"
		
		files {
			path.join(folder, "AssetLibTests/**.h"), 
			path.join(folder, "AssetLibTests/**.cpp")
		}
		
		self:include(includes)
		AssetLib:include(includes)
		catch2:include(includes)

		links:linkto(AssetLib)
		links:linkto(catch2)
		links:linkall()
end
