#include "LRCompiler.h"

int main(const int argc, const char** argv)
{
    return LRCompiler::Start(argc, argv) ? 1 : 0;
}
