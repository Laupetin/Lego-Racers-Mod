pegtl = {}

function pegtl:include(includes)
	if includes:handle(self:name()) then
		includedirs {
			path.join(ThirdPartyFolder(), "pegtl", "include")
		}
	end
end

function pegtl:link()
end

function pegtl:use()
	
end

function pegtl:name()
    return "pegtl"
end

function pegtl:project()
end
