#include "leviathan.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

Leviathan::cServerControl::cServerControl() : shutdown(false), serverID(0), channel(0), serverType(""), logLevel(1), host(""), port(0)
{
}

Leviathan::cServerControl::~cServerControl()
{
}

bool Leviathan::cServerControl::LoadConfig(const std::string name)
{
	std::string name_added_json = name + ".json";
	std::ifstream ifs(name_added_json.c_str());
	if (!ifs.is_open())
	{
		std::cerr << "[SYSTEM] LoadConfig Error" << std::endl;
		return false;
	}

	std::stringstream buf;
	buf << ifs.rdbuf();

	std::string data = buf.str();
	ifs.close();

	rapidjson::Document config;
	config.Parse(data.c_str());

	serverID = config["serverID"].GetInt();
	channel = config["channel"].GetInt();
	serverType = config["serverType"].GetString();

	logLevel = config["logLevel"].GetInt();

	host = config["environment"]["host"].GetString();
	port = config["environment"]["port"].GetInt();
	return true;
}
