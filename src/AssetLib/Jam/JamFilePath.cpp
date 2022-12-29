#include "JamFilePath.h"

#include <algorithm>
#include <stdexcept>

#include "FileUtils.h"
#include "StringUtils.h"

using namespace jam;

JamFilePath::JamFilePath()
    : m_depth(0u)
{
}

JamFilePath::JamFilePath(std::string path)
{
    if (path.find_first_of(utils::ILLEGAL_PATH_CHARS) != std::string::npos)
        throw std::runtime_error("Illegal path");

    std::replace(path.begin(), path.end(), '\\', '/');
    if (path.rfind("./", 0u) == 0u)
        path.erase(0u, 2u);

    if (!path.empty() && path[path.size() - 1] == '/')
        path.erase(path.size() - 1);

    utils::MakeStringUpperCase(path);
    m_path = std::move(path);
    m_depth = std::count(m_path.begin(), m_path.end(), '/');
}

// Private internal constructor
JamFilePath::JamFilePath(std::string path, const size_t depth)
    : m_path(std::move(path)),
      m_depth(depth)
{
}

namespace jam
{
    bool operator==(const JamFilePath& lhs, const JamFilePath& rhs)
    {
        return lhs.m_path == rhs.m_path;
    }

    bool operator!=(const JamFilePath& lhs, const JamFilePath& rhs)
    {
        return !(lhs == rhs);
    }

    bool operator<(const JamFilePath& lhs, const JamFilePath& rhs)
    {
        return lhs.m_path < rhs.m_path;
    }

    bool operator<=(const JamFilePath& lhs, const JamFilePath& rhs)
    {
        return !(rhs < lhs);
    }

    bool operator>(const JamFilePath& lhs, const JamFilePath& rhs)
    {
        return rhs < lhs;
    }

    bool operator>=(const JamFilePath& lhs, const JamFilePath& rhs)
    {
        return !(lhs < rhs);
    }

    std::size_t hash_value(const JamFilePath& obj)
    {
        std::size_t seed = 0x2CD55458;
        seed ^= (seed << 6) + (seed >> 2) + 0x2D165998 + std::hash<std::string>()(obj.m_path);
        seed ^= (seed << 6) + (seed >> 2) + 0x1D87BAC0 + static_cast<std::size_t>(obj.m_depth);
        return seed;
    }
}


namespace std
{
    std::size_t hash<JamFilePath>::operator()(const JamFilePath& v) const noexcept
    {
        return hash_value(v);
    }
}

JamFilePath JamFilePath::Parent() const
{
    if (m_depth <= 1)
        return JamFilePath();

    return JamFilePath(m_path.substr(0u, m_path.rfind('/')), m_depth - 1);
}

const std::string& JamFilePath::Path() const
{
    return m_path;
}

std::string JamFilePath::FileName() const
{
    if (!m_depth)
        return m_path;

    return m_path.substr(m_path.rfind('/') + 1);
}

size_t JamFilePath::Depth() const
{
    return m_depth;
}

std::vector<std::string> JamFilePath::GetPathFragments() const
{
    std::vector<std::string> result;
    result.reserve(m_depth);

    size_t head = 0u, tail = 0u;
    while (head < m_path.size())
    {
        head = m_path.find('/', head);
        if (head == std::string::npos)
            break;

        result.push_back(m_path.substr(tail, head - tail));
        tail = head + 1;
        head = tail;
    }

    return result;
}
