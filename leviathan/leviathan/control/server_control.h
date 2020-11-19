#pragma once

namespace Leviathan
{

class cServerControl
{
public:
	cServerControl();
	virtual ~cServerControl();

private:
	
public:
	bool LoadConfig(const std::string name);
};

}