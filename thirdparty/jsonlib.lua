jsonlib = {}

function jsonlib:include(includes)
	if includes:handle(self:name()) then
        includedirs {
            path.join(ThirdPartyFolder(), "json/single_include")
        }
	end
end

function jsonlib:link(links)
end

function jsonlib:use()
	
end

function jsonlib:name()
    return "json"
end

function jsonlib:project()
end
