#pragma once

#include "JamFilePath.h"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace jam
{
    using jam_id_t = size_t;

    class FileEntry
    {
    public:
        static constexpr auto MAX_NAME_LENGTH = 12u;

        FileEntry(jam_id_t id, std::string name);

        [[nodiscard]] jam_id_t Id() const;
        [[nodiscard]] const std::string& Name() const;

    private:
        jam_id_t m_id;
        std::string m_name;
    };

    class DirectoryEntry
    {
    public:
        static constexpr auto MAX_NAME_LENGTH = 12u;

        DirectoryEntry(jam_id_t id, std::string name);

        [[nodiscard]] jam_id_t Id() const;
        [[nodiscard]] const std::string& Name() const;
        [[nodiscard]] const std::vector<std::unique_ptr<DirectoryEntry>>& SubDirectories() const;
        [[nodiscard]] const std::vector<std::unique_ptr<FileEntry>>& Files() const;

        const std::unique_ptr<DirectoryEntry>& AddSubDirectory(std::unique_ptr<DirectoryEntry> directory);
        const std::unique_ptr<FileEntry>& AddFile(std::unique_ptr<FileEntry> file);
        void Sort();

    private:
        jam_id_t m_id;
        std::string m_name;
        std::vector<std::unique_ptr<DirectoryEntry>> m_sub_directories;
        std::vector<std::unique_ptr<FileEntry>> m_files;
    };

    class DirectoryTree
    {
    public:
        DirectoryTree();

        [[nodiscard]] const std::unique_ptr<DirectoryEntry>& RootDirectory() const;

        FileEntry& AddFile(const JamFilePath& path);

        [[nodiscard]] size_t DirectoryCount() const;
        [[nodiscard]] size_t FileCount() const;

    private:
        std::unique_ptr<DirectoryEntry> m_root_directory;
        jam_id_t m_next_directory_id;
        jam_id_t m_next_file_id;
    };
} // namespace jam
