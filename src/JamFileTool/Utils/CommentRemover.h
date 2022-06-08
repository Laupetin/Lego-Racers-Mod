#pragma once

#include <string>

class CommentRemover
{
public:
    CommentRemover(void* buffer, size_t bufferSize);

    void ConfigureDefaults();
    void ConfigureLineComment(std::string lineCommentStart);
    void ConfigureBlockComment(std::string blockCommentStart, std::string blockCommentEnd);
    void ConfigureConsiderStrings(bool enabled);

    void RemoveComments() const;

private:
    void* m_buffer;
    size_t m_buffer_size;
    std::string m_line_comment_start;
    std::string m_block_comment_start;
    std::string m_block_comment_end;
    bool m_consider_strings;
};
