#pragma once

// gperftools
#ifdef __TC_MALLOC__
#pragma comment (lib, "libtcmalloc_minimal")
#pragma comment (linker, "/include:__tcmalloc")
#endif
//

// system header file include
#include <stdio.h>
#include <iostream>
#include <chrono>
#include <vector>
#include <numeric>
//

#include "singleton.h"

namespace Leviathan
{

class cLeviathan : public cSingleton<cLeviathan>
{
public:
	cLeviathan();
	virtual ~cLeviathan();

private:

public:
	void do_somting();
};

}