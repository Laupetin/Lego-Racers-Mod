#include "MdbCreator.h"

#include <iostream>
#include <sstream>
#include <vector>

#include <tao/pegtl.hpp>
#include <tao/pegtl/contrib/unescape.hpp>

#include "Mdb.h"
#include "Utils/Endianness.h"
#include "Utils/StringUtils.h"
#include "TokenStream.h"

namespace pegtl = TAO_PEGTL_NAMESPACE;

using namespace mdb;

class MdbCreationException final : public std::exception
{
public:
    explicit MdbCreationException(char const* msg)
        : exception(msg)
    {
    }
};

class MdbParserState
{
public:
    explicit MdbParserState(ITokenOutputStream* out)
        : m_material_count(0u),
          m_out(out)
    {
    }

    void BeginMaterial(const std::string& materialName)
    {
        m_material_count++;
        m_out->WriteCustom(TOKEN_MATERIAL);
        m_out->WriteString(materialName);
        m_out->WriteLeftCurly();
    }

    void EndMaterial()
    {
        m_out->WriteRightCurly();
    }
    
    size_t m_material_count;
    ITokenOutputStream* m_out;
};

namespace mdb
{
    struct ws : pegtl::one<' ', '\t', '\n', '\r'> {};

    template<typename R, typename P = ws>
    struct padr : pegtl::seq<R, pegtl::star<P>> {};

    struct xdigit : pegtl::xdigit {};
    struct unicode : pegtl::list<pegtl::seq<pegtl::one<'u'>, pegtl::rep<4, xdigit>>, pegtl::one<'\\'>> {};
    struct escaped_char : pegtl::one<'"', '\\', '/', 'b', 'f', 'n', 'r', 't'> {};
    struct escaped : pegtl::sor<escaped_char, unicode> {};
    struct unescaped : pegtl::utf8::range<0x20, 0x10FFFF> {};
    struct char_ : pegtl::if_then_else<pegtl::one<'\\'>, escaped, unescaped> {};
    struct string_content : pegtl::until<pegtl::at<pegtl::one<'"'>>, char_ > {};
    struct str : pegtl::seq<pegtl::one<'"'>, string_content, pegtl::any>
    {
        using content = string_content;
    };

    struct key_materials : padr<TAO_PEGTL_KEYWORD("materials")> {};
    struct key_material : padr<TAO_PEGTL_KEYWORD("material")> {};

    struct key_color0 : padr<TAO_PEGTL_KEYWORD("color0")> {};
    struct key_color1 : padr<TAO_PEGTL_KEYWORD("color1")> {};
    struct key_texture : padr<TAO_PEGTL_KEYWORD("texture")> {};
    struct key_keyword2A : padr<TAO_PEGTL_KEYWORD("keyword2A")> {};
    struct key_keyword2B : padr<TAO_PEGTL_KEYWORD("keyword2B")> {};
    struct key_keyword2D : padr<TAO_PEGTL_KEYWORD("keyword2D")> {};
    struct key_keyword2E : padr<TAO_PEGTL_KEYWORD("keyword2E")> {};
    struct key_keyword2F : padr<TAO_PEGTL_KEYWORD("keyword2F")> {};
    struct key_keyword30 : padr<TAO_PEGTL_KEYWORD("keyword30")> {};
    struct key_keyword31 : padr<TAO_PEGTL_KEYWORD("keyword31")> {};
    struct key_keyword32 : padr<TAO_PEGTL_KEYWORD("keyword32")> {};
    struct key_keyword33 : padr<TAO_PEGTL_KEYWORD("keyword33")> {};
    struct key_keyword34 : padr<TAO_PEGTL_KEYWORD("keyword34")> {};
    struct key_keyword35 : padr<TAO_PEGTL_KEYWORD("keyword35")> {};
    struct key_keyword36 : padr<TAO_PEGTL_KEYWORD("keyword36")> {};
    struct key_keyword37 : padr<TAO_PEGTL_KEYWORD("keyword37")> {};
    struct key_keyword38 : padr<TAO_PEGTL_KEYWORD("keyword38")> {};
    struct key_keyword39 : padr<TAO_PEGTL_KEYWORD("keyword39")> {};
    struct key_keyword3A : padr<TAO_PEGTL_KEYWORD("keyword3A")> {};
    struct key_keyword3B : padr<TAO_PEGTL_KEYWORD("keyword3B")> {};
    struct key_keyword3C : padr<TAO_PEGTL_KEYWORD("keyword3C")> {};
    struct key_keyword3D : padr<TAO_PEGTL_KEYWORD("keyword3D")> {};
    struct key_keyword3E : padr<TAO_PEGTL_KEYWORD("keyword3E")> {};
    struct key_keyword3F : padr<TAO_PEGTL_KEYWORD("keyword3F")> {};
    struct key_keyword40 : padr<TAO_PEGTL_KEYWORD("keyword40")> {};
    struct key_keyword41 : padr<TAO_PEGTL_KEYWORD("keyword41")> {};
    struct key_keyword42 : padr<TAO_PEGTL_KEYWORD("keyword42")> {};
    struct key_keyword43 : padr<TAO_PEGTL_KEYWORD("keyword43")> {};
    struct key_keyword44 : padr<TAO_PEGTL_KEYWORD("keyword44")> {};
    struct key_keyword45 : padr<TAO_PEGTL_KEYWORD("keyword45")> {};
    struct key_opacity : padr<TAO_PEGTL_KEYWORD("opacity")> {};
    struct key_keyword47 : padr<TAO_PEGTL_KEYWORD("keyword47")> {};
    struct key_keyword48 : padr<TAO_PEGTL_KEYWORD("keyword48")> {};
    struct key_keyword49 : padr<TAO_PEGTL_KEYWORD("keyword49")> {};
    struct key_keyword4A : padr<TAO_PEGTL_KEYWORD("keyword4A")> {};
    struct key_keyword4B : padr<TAO_PEGTL_KEYWORD("keyword4B")> {};
    struct key_keyword4C : padr<TAO_PEGTL_KEYWORD("keyword4C")> {};
    struct key_keyword4D : padr<TAO_PEGTL_KEYWORD("keyword4D")> {};
    struct key_keyword4E : padr<TAO_PEGTL_KEYWORD("keyword4E")> {};
    struct key_keyword4F : padr<TAO_PEGTL_KEYWORD("keyword4F")> {};
    struct key_keyword50 : padr<TAO_PEGTL_KEYWORD("keyword50")> {};

    struct block_open : padr<pegtl::one<'{'>> {};
    struct block_close : padr<pegtl::one<'}'>> {};

    struct int_ : pegtl::sor<pegtl::one<'0'>, pegtl::plus<pegtl::digit>> {};

    struct uint8_value : padr<int_> {};
    struct int_value : padr<int_> {};
    struct str_value : str {};
    struct padr_str_value : padr<str_value> {};

    struct material_color0 : pegtl::seq<key_color0, uint8_value, uint8_value, uint8_value, uint8_value> {};
    struct material_color1 : pegtl::seq<key_color1, uint8_value, uint8_value, uint8_value, uint8_value> {};
    struct material_texture : pegtl::seq<key_texture, padr_str_value> {};
    struct material_keyword31 : pegtl::seq<key_keyword31, int_value> {};
    struct material_keyword32 : pegtl::seq<key_keyword32, int_value> {};
    struct material_keyword33 : pegtl::seq<key_keyword33, int_value> {};
    struct material_keyword34 : pegtl::seq<key_keyword34, int_value> {};
    struct material_keyword35 : pegtl::seq<key_keyword35, int_value> {};
    struct material_keyword37 : pegtl::seq<key_keyword37, int_value> {};
    struct material_opacity : pegtl::seq<key_opacity, uint8_value> {};
    struct material_keyword4E : pegtl::seq<key_keyword4E, int_value> {};
    struct material_keyword4F : pegtl::seq<key_keyword4F, int_value> {};
    struct material_keyword4D : pegtl::seq<key_keyword4D, int_value> {};
    struct material_keyword50 : pegtl::seq<key_keyword50, int_value> {};

    struct material_keyword2F_subtoken : pegtl::sor<
        key_keyword30,
        material_keyword31,
        material_keyword32,
        material_keyword33,
        material_keyword34,
        material_keyword35,
        key_keyword36,
        material_keyword37
    > {};
    struct material_keyword2F : pegtl::seq<key_keyword2F, int_value> {};

    struct material_keyword38_subtoken : pegtl::sor<
        key_keyword39,
        key_keyword3A,
        key_keyword3B,
        key_keyword3C,
        key_keyword3D,
        key_keyword3E,
        key_keyword3F,
        key_keyword40,
        key_keyword41,
        key_keyword42,
        key_keyword43
    > {};
    struct material_keyword38 : pegtl::seq<key_keyword38, material_keyword38_subtoken, material_keyword38_subtoken> {};

    struct material_property : pegtl::sor<
        material_color0,
        material_color1,
        material_texture,
        material_opacity,
        material_keyword4E,
        material_keyword4F,
        material_keyword4D,
        material_keyword50,
        key_keyword2A,
        key_keyword2B,
        key_keyword2D,
        key_keyword2E,
        key_keyword44,
        key_keyword45,
        key_keyword47,
        key_keyword48,
        key_keyword49,
        key_keyword4A,
        key_keyword4B,
        key_keyword4C
    > {};
    struct material_property_list : pegtl::until<pegtl::at<block_close>, pegtl::must<material_property>> {};

    struct material_name : str {};
    struct material : pegtl::seq<key_material, padr<material_name>, block_open, material_property_list, block_close> {};
    struct material_list : pegtl::until<pegtl::at<block_close>, pegtl::must<material>> {};
    struct materials : pegtl::must<key_materials, block_open, material_list, block_close> {};

    struct grammar : pegtl::must<materials> {};

    // Actions
    
    template<typename Rule> struct mdb_unescape_action {};

    template<> struct mdb_unescape_action<unicode> : pegtl::unescape::unescape_j {};
    template<> struct mdb_unescape_action<escaped_char > : pegtl::unescape::unescape_c<escaped_char, '"', '\\', '/', '\b', '\f', '\n', '\r', '\t' > {};
    template<> struct mdb_unescape_action<unescaped > : pegtl::unescape::append_all {};
    using mdb_unescape = pegtl::change_action_and_states<mdb_unescape_action, std::string>;

    template<typename Rule>
    struct action : pegtl::nothing<Rule> {};

    template<>
    struct action<material_name> : mdb_unescape
    {
        template< typename ParseInput >
        static void success([[maybe_unused]] const ParseInput& in, std::string& s, MdbParserState& state)
        {
            state.BeginMaterial(s);
        }
    };

    template<>
    struct action<material>
    {
        template<typename ActionInput>
        static void apply(const ActionInput& in, MdbParserState& state)
        {
            state.EndMaterial();
        }
    };

    template<>
    struct action<uint8_value>
    {
        template<typename ActionInput>
        static void apply(const ActionInput& in, MdbParserState& state)
        {
            const auto value = std::stoul(in.string());
            state.m_out->WriteUInt8(static_cast<uint8_t>(value));
        }
    };

    template<>
    struct action<int_value>
    {
        template<typename ActionInput>
        static void apply(const ActionInput& in, MdbParserState& state)
        {
            const auto value = std::stol(in.string());
            state.m_out->WriteInteger(static_cast<int>(value));
        }
    };

    template<>
    struct action<str_value> : mdb_unescape
    {
        template< typename ParseInput >
        static void success([[maybe_unused]] const ParseInput& in, std::string& s, MdbParserState& state)
        {
            state.m_out->WriteString(s);
        }
    };

    template<token_type_t TokenType>
    struct action_write_keyword
    {
        template<typename ActionInput>
        static void apply(const ActionInput& in, MdbParserState& state)
        {
            state.m_out->WriteCustom(TokenType);
        }
    };

    template<> struct action<key_color0> : action_write_keyword<TOKEN_KEYWORD_COLOR_0> {};
    template<> struct action<key_color1> : action_write_keyword<TOKEN_KEYWORD_COLOR_1> {};
    template<> struct action<key_texture> : action_write_keyword<TOKEN_KEYWORD_TEXTURE> {};
    template<> struct action<key_keyword2A> : action_write_keyword<TOKEN_KEYWORD_2A> {};
    template<> struct action<key_keyword2B> : action_write_keyword<TOKEN_KEYWORD_2B> {};
    template<> struct action<key_keyword2D> : action_write_keyword<TOKEN_KEYWORD_2D> {};
    template<> struct action<key_keyword2E> : action_write_keyword<TOKEN_KEYWORD_2E> {};
    template<> struct action<key_keyword2F> : action_write_keyword<TOKEN_KEYWORD_2F> {};
    template<> struct action<key_keyword30> : action_write_keyword<TOKEN_KEYWORD_2F_SUB_30> {};
    template<> struct action<key_keyword31> : action_write_keyword<TOKEN_KEYWORD_2F_SUB_31> {};
    template<> struct action<key_keyword32> : action_write_keyword<TOKEN_KEYWORD_2F_SUB_32> {};
    template<> struct action<key_keyword33> : action_write_keyword<TOKEN_KEYWORD_2F_SUB_33> {};
    template<> struct action<key_keyword34> : action_write_keyword<TOKEN_KEYWORD_2F_SUB_34> {};
    template<> struct action<key_keyword35> : action_write_keyword<TOKEN_KEYWORD_2F_SUB_35> {};
    template<> struct action<key_keyword36> : action_write_keyword<TOKEN_KEYWORD_2F_SUB_36> {};
    template<> struct action<key_keyword37> : action_write_keyword<TOKEN_KEYWORD_2F_SUB_37> {};
    template<> struct action<key_keyword38> : action_write_keyword<TOKEN_KEYWORD_38> {};
    template<> struct action<key_keyword39> : action_write_keyword<TOKEN_KEYWORD_38_SUB_39> {};
    template<> struct action<key_keyword3A> : action_write_keyword<TOKEN_KEYWORD_38_SUB_3A> {};
    template<> struct action<key_keyword3B> : action_write_keyword<TOKEN_KEYWORD_38_SUB_3B> {};
    template<> struct action<key_keyword3C> : action_write_keyword<TOKEN_KEYWORD_38_SUB_3C> {};
    template<> struct action<key_keyword3D> : action_write_keyword<TOKEN_KEYWORD_38_SUB_3D> {};
    template<> struct action<key_keyword3E> : action_write_keyword<TOKEN_KEYWORD_38_SUB_3E> {};
    template<> struct action<key_keyword3F> : action_write_keyword<TOKEN_KEYWORD_38_SUB_3F> {};
    template<> struct action<key_keyword40> : action_write_keyword<TOKEN_KEYWORD_38_SUB_40> {};
    template<> struct action<key_keyword41> : action_write_keyword<TOKEN_KEYWORD_38_SUB_41> {};
    template<> struct action<key_keyword42> : action_write_keyword<TOKEN_KEYWORD_38_SUB_42> {};
    template<> struct action<key_keyword43> : action_write_keyword<TOKEN_KEYWORD_38_SUB_43> {};
    template<> struct action<key_keyword44> : action_write_keyword<TOKEN_KEYWORD_44> {};
    template<> struct action<key_keyword45> : action_write_keyword<TOKEN_KEYWORD_45> {};
    template<> struct action<key_opacity> : action_write_keyword<TOKEN_KEYWORD_OPACITY> {};
    template<> struct action<key_keyword47> : action_write_keyword<TOKEN_KEYWORD_47> {};
    template<> struct action<key_keyword48> : action_write_keyword<TOKEN_KEYWORD_48> {};
    template<> struct action<key_keyword49> : action_write_keyword<TOKEN_KEYWORD_49> {};
    template<> struct action<key_keyword4A> : action_write_keyword<TOKEN_KEYWORD_4A> {};
    template<> struct action<key_keyword4B> : action_write_keyword<TOKEN_KEYWORD_4B> {};
    template<> struct action<key_keyword4C> : action_write_keyword<TOKEN_KEYWORD_4C> {};
    template<> struct action<key_keyword4D> : action_write_keyword<TOKEN_KEYWORD_4D> {};
    template<> struct action<key_keyword4E> : action_write_keyword<TOKEN_KEYWORD_4E> {};
    template<> struct action<key_keyword4F> : action_write_keyword<TOKEN_KEYWORD_4F> {};
    template<> struct action<key_keyword50> : action_write_keyword<TOKEN_KEYWORD_50> {};
}

bool MdbCreator::SupportFileExtension(const std::string& extension) const
{
    return extension == ".MDB";
}

void MdbCreator::ProcessFile(const std::string& filePath, const void* inputData, const size_t inputDataSize, std::ostream& output) const
{
    std::cout << "Mdb creating \"" << filePath << "\"\n";

    pegtl::memory_input<pegtl::tracking_mode::lazy> in(static_cast<const char*>(inputData), &static_cast<const char*>(inputData)[inputDataSize], filePath);

    std::ostringstream materialData;
    const auto materialDataTokens = ITokenOutputStream::Create(materialData);
    MdbParserState parserState(materialDataTokens.get());
    try
    {
        pegtl::parse<grammar, action>(in, parserState);
    }
    catch (const pegtl::parse_error& e)
    {
        const auto p = e.positions().front();
        std::cerr << e.what() << std::endl
            << in.line_at(p) << '\n'
            << std::setw(p.column) << '^' << std::endl;
        throw MdbCreationException("Parsing exception");
    }

    const auto tokenOut = ITokenOutputStream::Create(output);
    tokenOut->WriteCustom(TOKEN_MATERIAL_DB);
    tokenOut->WriteLeftBracket();
    tokenOut->WriteInteger(static_cast<int>(parserState.m_material_count));
    tokenOut->WriteRightBracket();
    tokenOut->WriteLeftCurly();

    output << materialData.str();

    tokenOut->WriteRightCurly();

    std::cout << "Successfully created Mdb \"" << filePath << "\" with " << parserState.m_material_count << " materials\n";
}
