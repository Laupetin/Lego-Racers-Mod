#include "Asset/Gdb/GdbStructWriter.h"
#include "Asset/Gdb/GdbTextReader.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <limits>
#include <sstream>
#include <string>

using namespace Catch::Matchers;

using namespace gdb;

namespace test::asset::gdb::text_reader
{
    constexpr auto FLOAT_EPS = static_cast<double>(std::numeric_limits<float>::epsilon());

    static void RequirePositionMatch(const Vertex& vertex, const float x, const float y, const float z)
    {
        REQUIRE_THAT(vertex.m_position.x, WithinAbs(static_cast<double>(x), FLOAT_EPS));
        REQUIRE_THAT(vertex.m_position.y, WithinAbs(static_cast<double>(y), FLOAT_EPS));
        REQUIRE_THAT(vertex.m_position.z, WithinAbs(static_cast<double>(z), FLOAT_EPS));
    }

    static void RequireUvMatch(const Vertex& vertex, const float u, const float v)
    {
        REQUIRE_THAT(vertex.m_uv.x, WithinAbs(static_cast<double>(u), FLOAT_EPS));
        REQUIRE_THAT(vertex.m_uv.y, WithinAbs(static_cast<double>(v), FLOAT_EPS));
    }

    static void RequireNormalMatch(const Vertex& vertex, const float x, const float y, const float z)
    {
        REQUIRE_THAT(vertex.m_normal.x, WithinAbs(static_cast<double>(x), FLOAT_EPS));
        REQUIRE_THAT(vertex.m_normal.y, WithinAbs(static_cast<double>(y), FLOAT_EPS));
        REQUIRE_THAT(vertex.m_normal.z, WithinAbs(static_cast<double>(z), FLOAT_EPS));
    }

    TEST_CASE("GdbTextReader: Ensure can read simple gdb", "[token][input]")
    {
        constexpr static auto GDB_DATA = "materials {\n"
                                         "  \"testmaterial\"\n"
                                         "}\n"

                                         "vertices {\n"
                                         "  v 3.5 4 -500.1\n"
                                         "  uv 5 -1\n"
                                         "  vn 0. -0.09 07\n"

                                         "  v -68.672043 0.000000 100.999977\n"
                                         "  uv 7.000000 0.000000\n"
                                         "  vn 0.135200 -0.108100 0.984900\n"

                                         "  v 101.000015 34.667980 2.920081\n"
                                         "  uv 0.000000 0.000000\n"
                                         "  vn 0.135200 -0.108100 0.984900\n"

                                         "  v 8.000011 35.000000 -2.000000\n"
                                         "  uv -2.998455 0.468691\n"
                                         "  vn 0.093800 -0.121700 0.988100\n"

                                         "  v 7.999974 -68.672005 -2.000000\n"
                                         "  uv 5.248343 0.295957\n"
                                         "  vn 0.438400 -0.898800 0.000000\n"
                                         "}\n"

                                         "faces {\n"
                                         "  f 0 1 2"
                                         "  f 3 4 1"
                                         "  f 4 2 0"
                                         "}\n"

                                         "meta {\n"
                                         "  object 0"
                                         "  vertices 0 0 5"
                                         "  faces 0 3"
                                         "}";

        std::istringstream inputDataStream(GDB_DATA);

        Model model;
        const auto writer = GdbStructWriter::Create(model);
        REQUIRE_NOTHROW(GdbTextReader::Read(inputDataStream, *writer));

        REQUIRE(model.m_materials.size() == 1u);
        REQUIRE(model.m_materials[0] == "testmaterial");

        REQUIRE(model.m_vertices.size() == 5u);

        RequirePositionMatch(model.m_vertices[0], 3.5f, 4.0f, -500.1f);
        RequireUvMatch(model.m_vertices[0], 5.0f, -1.0f);
        RequireNormalMatch(model.m_vertices[0], 0.0f, -0.09f, 7.0f);

        RequirePositionMatch(model.m_vertices[1], -68.672043f, 0.0f, 100.999977f);
        RequireUvMatch(model.m_vertices[1], 7.0f, 0.0f);
        RequireNormalMatch(model.m_vertices[1], 0.135200f, -0.108100f, 0.984900f);

        RequirePositionMatch(model.m_vertices[2], 101.000015f, 34.667980f, 2.920081f);
        RequireUvMatch(model.m_vertices[2], 0.0f, 0.0f);
        RequireNormalMatch(model.m_vertices[2], 0.135200f, -0.108100f, 0.984900f);

        RequirePositionMatch(model.m_vertices[3], 8.000011f, 35.000000f, -2.000000f);
        RequireUvMatch(model.m_vertices[3], -2.998455f, 0.468691f);
        RequireNormalMatch(model.m_vertices[3], 0.093800f, -0.121700f, 0.988100f);

        RequirePositionMatch(model.m_vertices[4], 7.999974f, -68.672005f, -2.000000f);
        RequireUvMatch(model.m_vertices[4], 5.248343f, 0.295957f);
        RequireNormalMatch(model.m_vertices[4], 0.438400f, -0.898800f, 0.0f);

        REQUIRE(model.m_faces.size() == 3u);

        REQUIRE(model.m_faces[0].m_indices[0] == 0);
        REQUIRE(model.m_faces[0].m_indices[1] == 1);
        REQUIRE(model.m_faces[0].m_indices[2] == 2);

        REQUIRE(model.m_faces[1].m_indices[0] == 3);
        REQUIRE(model.m_faces[1].m_indices[1] == 4);
        REQUIRE(model.m_faces[1].m_indices[2] == 1);

        REQUIRE(model.m_faces[2].m_indices[0] == 4);
        REQUIRE(model.m_faces[2].m_indices[1] == 2);
        REQUIRE(model.m_faces[2].m_indices[2] == 0);

        REQUIRE(model.m_meta.size() == 3u);

        REQUIRE(model.m_meta[0].m_keyword == TOKEN_META_NEW_OBJECT);
        REQUIRE(model.m_meta[0].m_value0 == 0);

        REQUIRE(model.m_meta[1].m_keyword == TOKEN_META_VERTICES);
        REQUIRE(model.m_meta[1].m_value0 == 0);
        REQUIRE(model.m_meta[1].m_value1 == 0);
        REQUIRE(model.m_meta[1].m_value2 == 5);

        REQUIRE(model.m_meta[2].m_keyword == TOKEN_META_FACES);
        REQUIRE(model.m_meta[2].m_value0 == 0);
        REQUIRE(model.m_meta[2].m_value1 == 3);
    }
} // namespace test::asset::gdb::text_reader
