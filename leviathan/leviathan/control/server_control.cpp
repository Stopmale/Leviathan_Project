#include "leviathan.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

Leviathan::cServerControl::cServerControl()
{
}

Leviathan::cServerControl::~cServerControl()
{
}

bool Leviathan::cServerControl::LoadConfig(const std::string name)
{		
	std::ifstream ifs(name.c_str());
	if (!ifs.is_open())
	{
		std::cerr << "LoadConfig Error" << std::endl;
		return false;
	}

	std::stringstream buf;
	buf << ifs.rdbuf();

	std::string data = buf.str();
	ifs.close();

	rapidjson::Document config;
	config.Parse(data.c_str());

	return true;
}
