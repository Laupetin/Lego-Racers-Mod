#pragma once
#include <string>

namespace gltf
{
    class Scene
    {
        
    };

    class Node
    {
    public:
        int m_mesh_index;
        std::string m_name;
        float m_translation[3];
        float m_scale[3];
    };

    class Mesh
    {
        
    };

    enum class AccessorComponentType
    {
        BYTE = 5120,
        UNSIGNED_BYTE = 5121,
        SHORT = 5122,
        UNSIGNED_SHORT = 5123,
        UNSIGNED_INT = 5125,
        FLOAT = 5126
    };

    enum class AccessorType
    {
        SCALAR,
        VEC2,
        VEC3,
        VEC4,
        MAT2,
        MAT3,
        MAT4
    };

    class Accessor
    {
    public:
        int m_buffer_view_index;
        AccessorComponentType m_component_type;
        int m_count;
        bool m_has_min_max;
        float m_min[3];
        float m_max[3];
        AccessorType m_type;
    };

    enum class BufferViewTarget
    {
        ARRAY_BUFFER = 34962,
        ELEMENT_ARRAY_BUFFER = 34963
    };

    class BufferView
    {
    public:
        int m_buffer_index;
        int m_byte_length;
        int m_byte_offset;
        int m_target;
    };

    class Buffer
    {
    public:
        int m_byte_length;
        std::string m_uri;
    };
}
