#include "CommentRemover.h"

CommentRemover::CommentRemover(void* buffer, const size_t bufferSize)
    : m_buffer(buffer),
      m_buffer_size(bufferSize),
      m_consider_strings(false)
{
}

void CommentRemover::ConfigureDefaults()
{
    ConfigureLineComment("//");
    ConfigureBlockComment("/*", "*/");
    ConfigureConsiderStrings(true);
}

void CommentRemover::ConfigureLineComment(std::string lineCommentStart)
{
    m_line_comment_start = std::move(lineCommentStart);
}

void CommentRemover::ConfigureBlockComment(std::string blockCommentStart, std::string blockCommentEnd)
{
    m_block_comment_start = std::move(blockCommentStart);
    m_block_comment_end = std::move(blockCommentEnd);
}

void CommentRemover::ConfigureConsiderStrings(const bool enabled)
{
    m_consider_strings = enabled;
}

void CommentRemover::RemoveComments() const
{
    static constexpr auto STRING_CHAR = '"';

    const auto lineCommentEnabled = !m_line_comment_start.empty();
    const auto lineCommentChar = lineCommentEnabled ? m_line_comment_start[0] : '\0';
    const auto lineCommentLen = lineCommentEnabled ? m_line_comment_start.size() : 0u;

    const auto blockCommentEnabled = !m_block_comment_start.empty() && !m_block_comment_end.empty();
    const auto blockCommentStartChar = blockCommentEnabled ? m_block_comment_start[0] : '\0';
    const auto blockCommentStartLen = blockCommentEnabled ? m_block_comment_start.size() : 0u;
    const auto blockCommentEndChar = blockCommentEnabled ? m_block_comment_end[0] : '\0';
    const auto blockCommentEndLen = blockCommentEnabled ? m_block_comment_end.size() : 0u;

    auto insideLineComment = false;
    auto insideBlockComment = false;
    auto insideString = false;

    auto* cBuffer = static_cast<char*>(m_buffer);
    for (size_t i = 0u; i < m_buffer_size; i++)
    {
        const auto c = cBuffer[i];

        if (insideLineComment)
        {
            if (c == '\n' || c == '\r' && i + 1 < m_buffer_size && cBuffer[i + 1] == '\n')
                insideLineComment = false;
            else
                cBuffer[i] = ' ';

            continue;
        }

        if (insideBlockComment)
        {
            if (c == blockCommentEndChar && m_block_comment_end.compare(0u, blockCommentEndLen, &cBuffer[i], blockCommentEndLen) == 0)
            {
                insideBlockComment = false;
                for (auto j = 0u; j < blockCommentEndLen; j++)
                    cBuffer[i + j] = ' ';
            }
            else if (c != '\n' && !(c == '\r' && i + 1 < m_buffer_size && cBuffer[i + 1] == '\n'))
                cBuffer[i] = ' ';

            continue;
        }

        if (insideString)
        {
            if (c == STRING_CHAR || c == '\n' || c == '\r' && i + 1 < m_buffer_size && cBuffer[i + 1] == '\n')
                insideString = false;
            continue;
        }

        if (lineCommentEnabled && c == lineCommentChar && m_line_comment_start.compare(0u, lineCommentLen, &cBuffer[i], lineCommentLen) == 0)
        {
            insideLineComment = true;
            for (auto j = 0u; j < lineCommentLen; j++)
                cBuffer[i + j] = ' ';
        }
        else if (blockCommentEnabled && c == blockCommentStartChar && m_block_comment_start.compare(0u, blockCommentStartLen, &cBuffer[i], blockCommentStartLen) == 0)
        {
            insideBlockComment = true;
            for (auto j = 0u; j < blockCommentStartLen; j++)
                cBuffer[i + j] = ' ';
        }
        else if (m_consider_strings && c == STRING_CHAR)
        {
            insideString = true;
        }
    }
}
