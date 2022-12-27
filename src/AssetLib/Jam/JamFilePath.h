#pragma once

#include <string>
#include <vector>

namespace jam
{
    class JamFilePath
    {
    public:
        JamFilePath();
        explicit JamFilePath(std::string path);

        ~JamFilePath() = default;
        JamFilePath(const JamFilePath& other) = default;
        JamFilePath(JamFilePath&& other) noexcept = default;
        JamFilePath& operator=(const JamFilePath& other) = default;
        JamFilePath& operator=(JamFilePath&& other) noexcept = default;

        friend bool operator==(const JamFilePath& lhs, const JamFilePath& rhs);
        friend bool operator!=(const JamFilePath& lhs, const JamFilePath& rhs);
        friend bool operator<(const JamFilePath& lhs, const JamFilePath& rhs);
        friend bool operator<=(const JamFilePath& lhs, const JamFilePath& rhs);
        friend bool operator>(const JamFilePath& lhs, const JamFilePath& rhs);
        friend bool operator>=(const JamFilePath& lhs, const JamFilePath& rhs);
        friend std::size_t hash_value(const JamFilePath& obj);

        [[nodiscard]] JamFilePath Parent() const;
        [[nodiscard]] const std::string& Path() const;
        [[nodiscard]] std::string FileName() const;
        [[nodiscard]] size_t Depth() const;
        [[nodiscard]] std::vector<std::string> GetPathFragments() const;

    private:
        JamFilePath(std::string path, size_t depth);

        std::string m_path;
        size_t m_depth;
    };
}

template <>
struct std::hash<jam::JamFilePath>
{
    std::size_t operator()(const jam::JamFilePath& v) const noexcept;
};
