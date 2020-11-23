#pragma once

#include "define.h"

namespace Leviathan
{

class cServerControl
{
public:
	cServerControl();
	virtual ~cServerControl();

private:
	ServerID serverID;
	Channel channel;
	ServerType serverType;
	Host host;
	Port port;
	
public:
	bool LoadConfig(const std::string name);
};

}