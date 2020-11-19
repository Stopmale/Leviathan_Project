#pragma once

#include <mutex>

namespace Leviathan
{

template <typename T>
class cSingleton
{
private:
	static std::once_flag flag;
	static std::unique_ptr<T> inst;

public:
	static T& Instance()
	{
		std::call_once(flag, []()
			{
				inst.reset(new T);
			});

		return *(inst.get());
	}
};

template <typename T>
std::unique_ptr<T> cSingleton<T>::inst = nullptr;

template <typename T>
std::once_flag cSingleton<T>::flag;

}