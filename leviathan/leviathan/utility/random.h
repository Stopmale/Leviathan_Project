#pragma once
#include <random>

namespace Leviathan
{
static std::mt19937* gRandomSeed;

void InitializeRandomSeed();
__int32 GetRandomValueInt32(__int32 _begin, __int32 _end);
__int64 GetRandomValueInt64(__int64 _begin, __int64 _end);
}