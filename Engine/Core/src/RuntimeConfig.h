#pragma once

#include <string>
#include <cstdint>

namespace GE2D 
{

//========================================
struct RuntimeConfig
{
	std::string t_AppName;
	std::uint32_t t_Width{ 0 };
	std::uint32_t t_Height{ 0 };
};

} // GE2D namespace