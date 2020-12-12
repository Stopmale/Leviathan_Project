#pragma once

#include "define.h"

namespace Leviathan
{

#pragma pack(push, 1)
class cServerControl
{
public:
	cServerControl();
	virtual ~cServerControl();

private:
	bool shutdown;

	ServerID serverID;
	Channel channel;
	ServerType serverType;

	__int32 logLevel;

	Host host;
	Port port;
	
public:
	bool ShuttingDown() { return shutdown; }

	bool LoadConfig(const std::string name);

	ServerID GetServerID() { return serverID; }
	Channel GetChannel() { return channel; }
	ServerType GetServerType() { return serverType; }

	__int32 GetLogLevel() { return logLevel; }

	Host GetHost() { return host; }
	Port GetPort() { return port; }
};
#pragma pack(pop)

}