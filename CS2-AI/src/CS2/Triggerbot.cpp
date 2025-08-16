#include "CS2/Triggerbot.h"

void Triggerbot::update(GameInformationhandler* handler)
{
	if (!handler)
		return;

	const GameInformation game_info = handler->get_game_information();

	if ((game_info.controlled_player.shots_fired > 0) || (game_info.controlled_player.health <= 0))
		handler->set_player_shooting(false);

	if (!game_info.player_in_crosshair)
		return;

	if (!m_shoot_at_teammates && (game_info.player_in_crosshair->team == game_info.controlled_player.team))
		return;

	if ((game_info.player_in_crosshair->health <= 0) || (game_info.player_in_crosshair->health >=200))
		return;

	const auto current_time_ms = get_current_time_in_ms();
	
	if (current_time_ms >= m_delay_time)
	{
		m_delay_time = current_time_ms + m_time_between_shots;
		handler->set_player_shooting(true);
	}
}

void Triggerbot::set_shoot_at_teammates(bool shoot_at_teammates)
{
	m_shoot_at_teammates = shoot_at_teammates;
}

void Triggerbot::set_time_between_shots(int milliseconds)
{
	m_time_between_shots = milliseconds;
}
