jsonlib = {}

function jsonlib:include(includes)
	if includes:handle(self:name()) then
        includedirs {
            path.join(ThirdPartyFolder(), "json/single_include")
        }
        defines {
            "JSON_USE_IMPLICIT_CONVERSIONS=0"
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
