#pragma once
#include "Utility/Utility.h"
#include "GameInformationHandler.h"

class Triggerbot 
{
public:
	void update(GameInformationhandler* handler);
	void set_shoot_at_teammates(bool shoot_at_teammates);
	void set_time_between_shots(int milliseconds);

private:
	long long m_delay_time = 0;
	bool m_shoot_at_teammates = false;
	int m_time_between_shots = 500;
};