#pragma once
#include <string>

struct Config 
{
	std::string client_dll_name;
	std::string engine_dll_name;
	std::string  windowname;
	int delay_between_shots = 0;
	bool ignore_same_team = true;
	//DWORD trigger_button = 0;
};
