#include "random.h"
#include <time.h>

void Leviathan::InitializeRandomSeed()
{
	gRandomSeed = new std::mt19937((unsigned int)time(NULL));
}

__int32 Leviathan::GetRandomValueInt32(__int32 _begin, __int32 _end)
{
	if (_end < _begin)
		return _begin;

	std::uniform_int_distribution<__int32> distribution(_begin, _end);
	return distribution(*gRandomSeed);
}

__int64 Leviathan::GetRandomValueInt64(__int64 _begin, __int64 _end)
{
	if (_end < _begin)
		return _begin;

	std::uniform_int_distribution<__int64> distribution(_begin, _end);
	return distribution(*gRandomSeed);
}
