#include "LRCompiler.h"

int main(const int argc, const char** argv)
{
    const LRCompiler compiler;
    return compiler.Start(argc, argv) ? 1 : 0;
}
