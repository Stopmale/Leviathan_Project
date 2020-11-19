#include "leviathan.h"

Leviathan::cLeviathan::cLeviathan()
{
}

Leviathan::cLeviathan::~cLeviathan()
{
}

bool Leviathan::cLeviathan::Booting(std::string config)
{
	if (!LoadConfig(config))
	{
		return false;
	}

	return true;
}