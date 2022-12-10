#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <cstdint>
#include <sstream>
#include <string>

#include "Asset/Mdb/MdbTextReader.h"

using namespace mdb;

namespace test::asset::mdb::text_reader
{
    class MdbTestEmitter final : public IMdbEmitter
    {
    public:
        void StartMaterials() override
        {
            m_str << "materials ";
        }

        void EndMaterials() override
        {
            m_str << "end_materials ";
        }

        void StartMaterial(const std::string name) override
        {
            m_str << "material:" << name << " ";
        }

        void EmitColor0(const uint8_t value0, const uint8_t value1, const uint8_t value2, const uint8_t value3) override
        {
            m_str << "color0:" << static_cast<int>(value0) << ":" << static_cast<int>(value1) << ":" << static_cast<int>(value2) << ":" << static_cast<int>(value3) << " ";
        }

        void EmitColor1(const uint8_t value0, const uint8_t value1, const uint8_t value2, const uint8_t value3) override
        {
            m_str << "color1:" << static_cast<int>(value0) << ":" << static_cast<int>(value1) << ":" << static_cast<int>(value2) << ":" << static_cast<int>(value3) << " ";
        }

        void EmitTexture(const std::string textureName) override
        {
            m_str << "texture:" << textureName << " ";
        }

        void EmitOpacity(const uint8_t value) override
        {
            m_str << "opacity:" << static_cast<int>(value) << " ";
        }

        void EmitKeyword4D(const int value) override
        {
            m_str << "keyword4d:" << value << " ";
        }

        void EmitKeyword4E(const int value) override
        {
            m_str << "keyword4e:" << value << " ";
        }

        void EmitKeyword4F(const int value) override
        {
            m_str << "keyword4f:" << value << " ";
        }

        void EmitKeyword50(const int value) override
        {
            m_str << "keyword50:" << value << " ";
        }

        void EmitKeyword2A() override
        {
            m_str << "keyword2a ";
        }

        void EmitKeyword2B() override
        {
            m_str << "keyword2b ";
        }

        void EmitKeyword2D() override
        {
            m_str << "keyword2d ";
        }

        void EmitKeyword2E() override
        {
            m_str << "keyword2e ";
        }

        void EmitKeyword44() override
        {
            m_str << "keyword44 ";
        }

        void EmitKeyword45() override
        {
            m_str << "keyword45 ";
        }

        void EmitKeyword47() override
        {
            m_str << "keyword47 ";
        }

        void EmitKeyword48() override
        {
            m_str << "keyword48 ";
        }

        void EmitKeyword49() override
        {
            m_str << "keyword49 ";
        }

        void EmitKeyword4A() override
        {
            m_str << "keyword4a ";
        }

        void EmitKeyword4B() override
        {
            m_str << "keyword4b ";
        }

        void EmitKeyword4C() override
        {
            m_str << "keyword4c ";
        }

        void EmitKeyword2F(const MaterialToken subToken, const int subTokenValue) override
        {
            m_str << "keyword2f:" << subToken << ":" << subTokenValue << " ";
        }

        void EmitKeyword38(const MaterialToken subToken0, const MaterialToken subToken1) override
        {
            m_str << "keyword38:" << subToken0 << ":" << subToken1 << " ";
        }

        void EndMaterial() override
        {
            m_str << "end_material ";
        }

        [[nodiscard]] std::string DebugStr() const
        {
            return m_str.str();
        }

    private:
        std::ostringstream m_str;
    };

    TEST_CASE("MdbTextReader: Ensure can read simple mdb", "[token][input]")
    {
        constexpr static auto MDB_DATA =
            "materials\n"
            "{\n"
            "  material \"wave\"\n"
            "  {\n"
            "    texture \"warp\"\n"
            "    color0 12 34 56 78\n"
            "    keyword48\n"
            "  }\n"
            "  \n"
            "  material \"otherMaterial\"\n"
            "  {\n"
            "    texture \"funny-cat\"\n"
            "  }\n"
            "}\n";
        constexpr static auto EXPECTED_RESULT =
            "materials material:wave texture:warp color0:12:34:56:78 keyword48 end_material material:otherMaterial texture:funny-cat end_material end_materials ";

        std::istringstream inputDataStream(MDB_DATA);
        MdbTestEmitter emitter;
        MdbTextReader::Read(inputDataStream, emitter);

        REQUIRE(emitter.DebugStr() == EXPECTED_RESULT);
    }

    TEST_CASE("MdbTextReader: Ensure can read color0", "[token][input]")
    {
        constexpr static auto MDB_DATA =
            "materials\n"
            "{\n"
            "  material \"wave\"\n"
            "  {\n"
            "    color0 12 34 56 78\n"
            "  }\n"
            "}\n";
        constexpr static auto EXPECTED_RESULT =
            "materials material:wave color0:12:34:56:78 end_material end_materials ";

        std::istringstream inputDataStream(MDB_DATA);
        MdbTestEmitter emitter;
        MdbTextReader::Read(inputDataStream, emitter);

        REQUIRE(emitter.DebugStr() == EXPECTED_RESULT);
    }

    TEST_CASE("MdbTextReader: Ensure can read color1", "[token][input]")
    {
        constexpr static auto MDB_DATA =
            "materials\n"
            "{\n"
            "  material \"wave\"\n"
            "  {\n"
            "    color1 255 0 12 62\n"
            "  }\n"
            "}\n";
        constexpr static auto EXPECTED_RESULT =
            "materials material:wave color1:255:0:12:62 end_material end_materials ";

        std::istringstream inputDataStream(MDB_DATA);
        MdbTestEmitter emitter;
        MdbTextReader::Read(inputDataStream, emitter);

        REQUIRE(emitter.DebugStr() == EXPECTED_RESULT);
    }

    TEST_CASE("MdbTextReader: Ensure can read texture", "[token][input]")
    {
        constexpr static auto MDB_DATA =
            "materials\n"
            "{\n"
            "  material \"wave\"\n"
            "  {\n"
            "    texture \"tex\"\n"
            "  }\n"
            "}\n";
        constexpr static auto EXPECTED_RESULT =
            "materials material:wave texture:tex end_material end_materials ";

        std::istringstream inputDataStream(MDB_DATA);
        MdbTestEmitter emitter;
        MdbTextReader::Read(inputDataStream, emitter);

        REQUIRE(emitter.DebugStr() == EXPECTED_RESULT);
    }

    TEST_CASE("MdbTextReader: Ensure can read opacity", "[token][input]")
    {
        const auto opacityValue = GENERATE(0, 127, 255);
        INFO("Opacity: " << opacityValue);

        const auto mdbData =
            "materials\n"
            "{\n"
            "  material \"wave\"\n"
            "  {\n"
            "    opacity " + std::to_string(opacityValue) + "\n"
            "  }\n"
            "}\n";
        const auto expectedResult = "materials material:wave opacity:" + std::to_string(opacityValue) + " end_material end_materials ";

        std::istringstream inputDataStream(mdbData);
        MdbTestEmitter emitter;
        MdbTextReader::Read(inputDataStream, emitter);

        REQUIRE(emitter.DebugStr() == expectedResult);
    }

    TEST_CASE("MdbTextReader: Ensure can read keyword with int value", "[token][input]")
    {
        const auto testValue = GENERATE(-42, 0, 1337, 500000);
        INFO("Value: " << testValue);

        std::string keyword;
        std::string expectedValue;

        SECTION("...keyword4D")
        {
            keyword = "keyword4D";
            expectedValue = "keyword4d";
        }

        SECTION("...keyword4E")
        {
            keyword = "keyword4E";
            expectedValue = "keyword4e";
        }

        SECTION("...keyword4F")
        {
            keyword = "keyword4D";
            expectedValue = "keyword4d";
        }

        SECTION("...keyword50")
        {
            keyword = "keyword50";
            expectedValue = "keyword50";
        }

        const auto mdbData =
            "materials\n"
            "{\n"
            "  material \"wave\"\n"
            "  {\n"
            "    " + keyword + " " + std::to_string(testValue) + "\n"
            "  }\n"
            "}\n";
        const auto expectedResult =
            "materials material:wave " + expectedValue + ":" + std::to_string(testValue) + " end_material end_materials ";

        std::istringstream inputDataStream(mdbData);
        MdbTestEmitter emitter;
        MdbTextReader::Read(inputDataStream, emitter);

        REQUIRE(emitter.DebugStr() == expectedResult);
    }

    TEST_CASE("MdbTextReader: Ensure can read simple keywords", "[token][input]")
    {
        std::string keyword;
        std::string expectedValue;

        SECTION("...keyword2A")
        {
            keyword = "keyword2A";
            expectedValue = "keyword2a";
        }

        SECTION("...keyword2B")
        {
            keyword = "keyword2B";
            expectedValue = "keyword2b";
        }

        SECTION("...keyword2D")
        {
            keyword = "keyword2D";
            expectedValue = "keyword2d";
        }

        SECTION("...keyword2E")
        {
            keyword = "keyword2E";
            expectedValue = "keyword2e";
        }

        SECTION("...keyword44")
        {
            keyword = "keyword44";
            expectedValue = "keyword44";
        }

        SECTION("...keyword45")
        {
            keyword = "keyword45";
            expectedValue = "keyword45";
        }

        SECTION("...keyword47")
        {
            keyword = "keyword47";
            expectedValue = "keyword47";
        }

        SECTION("...keyword48")
        {
            keyword = "keyword48";
            expectedValue = "keyword48";
        }

        SECTION("...keyword49")
        {
            keyword = "keyword49";
            expectedValue = "keyword49";
        }

        SECTION("...keyword4A")
        {
            keyword = "keyword4A";
            expectedValue = "keyword4a";
        }

        SECTION("...keyword4B")
        {
            keyword = "keyword4B";
            expectedValue = "keyword4b";
        }

        SECTION("...keyword4C")
        {
            keyword = "keyword4C";
            expectedValue = "keyword4c";
        }

        const auto mdbData =
            "materials\n"
            "{\n"
            "  material \"wave\"\n"
            "  {\n"
            "    " + keyword + "\n"
            "  }\n"
            "}\n";
        const auto expectedResult = "materials material:wave " + expectedValue + " end_material end_materials ";

        std::istringstream inputDataStream(mdbData);
        MdbTestEmitter emitter;
        MdbTextReader::Read(inputDataStream, emitter);

        REQUIRE(emitter.DebugStr() == expectedResult);
    }

    TEST_CASE("MdbTextReader: Ensure can read keyword2F without value", "[token][input]")
    {
        std::string keyword;
        std::string expectedKeyword;

        SECTION("...keyword30")
        {
            keyword = "keyword30";
            expectedKeyword = "48"; // TOKEN_KEYWORD_2F_SUB_30
        }

        SECTION("...keyword36")
        {
            keyword = "keyword36";
            expectedKeyword = "54"; // TOKEN_KEYWORD_2F_SUB_36
        }

        const auto mdbData =
            "materials\n"
            "{\n"
            "  material \"wave\"\n"
            "  {\n"
            "    keyword2F " + keyword + "\n"
            "  }\n"
            "}\n";
        const auto expectedResult = "materials material:wave keyword2f:" + expectedKeyword + ":0 end_material end_materials ";

        std::istringstream inputDataStream(mdbData);
        MdbTestEmitter emitter;
        MdbTextReader::Read(inputDataStream, emitter);

        REQUIRE(emitter.DebugStr() == expectedResult);
    }

    TEST_CASE("MdbTextReader: Ensure can read keyword2F with additional value", "[token][input]")
    {
        std::string keyword;
        std::string expectedKeyword;

        SECTION("...keyword31")
        {
            keyword = "keyword31";
            expectedKeyword = "49"; // TOKEN_KEYWORD_2F_SUB_31
        }

        SECTION("...keyword32")
        {
            keyword = "keyword32";
            expectedKeyword = "50"; // TOKEN_KEYWORD_2F_SUB_32
        }

        SECTION("...keyword33")
        {
            keyword = "keyword33";
            expectedKeyword = "51"; // TOKEN_KEYWORD_2F_SUB_33
        }

        SECTION("...keyword34")
        {
            keyword = "keyword34";
            expectedKeyword = "52"; // TOKEN_KEYWORD_2F_SUB_34
        }

        SECTION("...keyword35")
        {
            keyword = "keyword35";
            expectedKeyword = "53"; // TOKEN_KEYWORD_2F_SUB_35
        }

        SECTION("...keyword37")
        {
            keyword = "keyword37";
            expectedKeyword = "55"; // TOKEN_KEYWORD_2F_SUB_37
        }

        const auto mdbData =
            "materials\n"
            "{\n"
            "  material \"wave\"\n"
            "  {\n"
            "    keyword2F " + keyword + " 1337\n"
            "  }\n"
            "}\n";
        const auto expectedResult = "materials material:wave keyword2f:" + expectedKeyword + ":1337 end_material end_materials ";

        std::istringstream inputDataStream(mdbData);
        MdbTestEmitter emitter;
        MdbTextReader::Read(inputDataStream, emitter);

        REQUIRE(emitter.DebugStr() == expectedResult);
    }

    TEST_CASE("MdbTextReader: Ensure can read keyword38", "[token][input]")
    {
        std::string keyword;
        std::string expectedKeyword;

        SECTION("...Keyword39")
        {
            keyword = "keyword39";
            expectedKeyword = "57"; // TOKEN_KEYWORD_38_SUB_39
        }

        SECTION("...Keyword3A")
        {
            keyword = "keyword3A";
            expectedKeyword = "58"; // TOKEN_KEYWORD_38_SUB_3A
        }

        SECTION("...Keyword3B")
        {
            keyword = "keyword3B";
            expectedKeyword = "59"; // TOKEN_KEYWORD_38_SUB_3B
        }

        SECTION("...Keyword3C")
        {
            keyword = "keyword3C";
            expectedKeyword = "60"; // TOKEN_KEYWORD_38_SUB_3C
        }

        SECTION("...Keyword3D")
        {
            keyword = "keyword3D";
            expectedKeyword = "61"; // TOKEN_KEYWORD_38_SUB_3D
        }

        SECTION("...Keyword3E")
        {
            keyword = "keyword3E";
            expectedKeyword = "62"; // TOKEN_KEYWORD_38_SUB_3E
        }

        SECTION("...Keyword3F")
        {
            keyword = "keyword3F";
            expectedKeyword = "63"; // TOKEN_KEYWORD_38_SUB_3F
        }

        SECTION("...Keyword40")
        {
            keyword = "keyword40";
            expectedKeyword = "64"; // TOKEN_KEYWORD_38_SUB_40
        }

        SECTION("...Keyword41")
        {
            keyword = "keyword41";
            expectedKeyword = "65"; // TOKEN_KEYWORD_38_SUB_41
        }

        SECTION("...Keyword42")
        {
            keyword = "keyword42";
            expectedKeyword = "66"; // TOKEN_KEYWORD_38_SUB_42
        }

        SECTION("...Keyword43")
        {
            keyword = "keyword43";
            expectedKeyword = "67"; // TOKEN_KEYWORD_38_SUB_43
        }

        const auto mdbData =
            "materials\n"
            "{\n"
            "  material \"wave\"\n"
            "  {\n"
            "    keyword38 " + keyword + " " + keyword + "\n"
            "  }\n"
            "}\n";
        const auto expectedResult = "materials material:wave keyword38:" + expectedKeyword + ":" + expectedKeyword + " end_material end_materials ";

        std::istringstream inputDataStream(mdbData);
        MdbTestEmitter emitter;
        MdbTextReader::Read(inputDataStream, emitter);

        REQUIRE(emitter.DebugStr() == expectedResult);
    }
}
