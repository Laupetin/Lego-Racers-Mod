#pragma once

class LRCompiler
{
    class Impl;
    Impl* m_impl;

public:
    LRCompiler();
    ~LRCompiler();

    LRCompiler(const LRCompiler& other) = delete;
    LRCompiler(LRCompiler&& other) noexcept = delete;
    LRCompiler& operator=(const LRCompiler& other) = delete;
    LRCompiler& operator=(LRCompiler&& other) noexcept = delete;

    bool Start(int argc, const char** argv) const;
};
