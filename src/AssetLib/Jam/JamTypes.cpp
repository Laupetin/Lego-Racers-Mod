#include "JamTypes.h"

#include "StringUtils.h"

#include <algorithm>

using namespace jam;

FileEntry::FileEntry(const jam_id_t id, std::string name)
    : m_id(id)
{
    if (name.size() > MAX_NAME_LENGTH)
    {
        const auto characterCountToErase = name.size() - MAX_NAME_LENGTH;
        name.erase(name.size() - characterCountToErase, characterCountToErase);
    }

    utils::MakeStringUpperCase(name);
    m_name = std::move(name);
}

jam_id_t FileEntry::Id() const
{
    return m_id;
}

const std::string& FileEntry::Name() const
{
    return m_name;
}

DirectoryEntry::DirectoryEntry(const jam_id_t id, std::string name)
    : m_id(id)
{
    if (name.size() > MAX_NAME_LENGTH)
    {
        const auto characterCountToErase = name.size() - MAX_NAME_LENGTH;
        auto extensionPos = name.find_last_of('.');
        if (extensionPos == std::string::npos)
            extensionPos = name.size();

        name.erase(extensionPos - characterCountToErase, characterCountToErase);
    }

    utils::MakeStringUpperCase(name);
    m_name = std::move(name);
}

jam_id_t DirectoryEntry::Id() const
{
    return m_id;
}

const std::string& DirectoryEntry::Name() const
{
    return m_name;
}

const std::vector<std::unique_ptr<DirectoryEntry>>& DirectoryEntry::SubDirectories() const
{
    return m_sub_directories;
}

const std::vector<std::unique_ptr<FileEntry>>& DirectoryEntry::Files() const
{
    return m_files;
}

const std::unique_ptr<DirectoryEntry>& DirectoryEntry::AddSubDirectory(std::unique_ptr<DirectoryEntry> directory)
{
    return m_sub_directories.emplace_back(std::move(directory));
}

const std::unique_ptr<FileEntry>& DirectoryEntry::AddFile(std::unique_ptr<FileEntry> file)
{
    return m_files.emplace_back(std::move(file));
}

void DirectoryEntry::Sort()
{
    std::sort(m_sub_directories.begin(),
              m_sub_directories.end(),
              [](const std::unique_ptr<DirectoryEntry>& d0, const std::unique_ptr<DirectoryEntry>& d1)
              {
                  return d0->Name() < d1->Name();
              });

    std::sort(m_files.begin(),
              m_files.end(),
              [](const std::unique_ptr<FileEntry>& f0, const std::unique_ptr<FileEntry>& f1)
              {
                  return f0->Name() < f1->Name();
              });
}

DirectoryTree::DirectoryTree()
    : m_next_directory_id(0u),
      m_next_file_id(0u)
{
}

const std::unique_ptr<DirectoryEntry>& DirectoryTree::RootDirectory() const
{
    return m_root_directory;
}

FileEntry& DirectoryTree::AddFile(const JamFilePath& path)
{
    const auto pathSegments = path.GetPathFragments();

    if (!m_root_directory)
        m_root_directory = std::make_unique<DirectoryEntry>(m_next_directory_id++, std::string());

    auto* currentDirectory = m_root_directory.get();

    for (const auto& pathSegment : pathSegments)
    {
        const auto& subDirectories = currentDirectory->SubDirectories();

        const auto existingSubDirectory = std::find_if(subDirectories.begin(),
                                                       subDirectories.end(),
                                                       [&pathSegment](const std::unique_ptr<DirectoryEntry>& dir)
                                                       {
                                                           return dir->Name() == pathSegment;
                                                       });

        if (existingSubDirectory == subDirectories.end())
        {
            currentDirectory = currentDirectory->AddSubDirectory(std::make_unique<DirectoryEntry>(m_next_directory_id++, pathSegment)).get();
        }
        else
        {
            currentDirectory = existingSubDirectory->get();
        }
    }

    return *currentDirectory->AddFile(std::make_unique<FileEntry>(m_next_file_id++, path.FileName()));
}

size_t DirectoryTree::DirectoryCount() const
{
    return m_next_directory_id;
}

size_t DirectoryTree::FileCount() const
{
    return m_next_file_id;
}
