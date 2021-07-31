#pragma once
#include <iostream>
#include <vector>
#include "Offsets.h"
#include "Vec3D.h"
#include "Vec2D.h"
#include "MemoryManager.h"
#include "ConfigReader.h"

struct ControlledPlayer 
{
	Vec2D<float> view_vec;
	Vec3D<float> head_position;
	int team;
	int health;
};

struct PlayerInformation 
{
	Vec3D<float> head_position;
	int team;
	int health;
};

struct GameInformation 
{
	ControlledPlayer controlled_player;
	std::shared_ptr<PlayerInformation> player_in_crosshair = nullptr;
	std::vector<PlayerInformation> other_players;
	std::shared_ptr<PlayerInformation> closest_enemy_player = nullptr;
};

class GameInformationhandler
{
public:
	GameInformationhandler();
	bool init(const ConfigData& config);
	void update_game_information();

	GameInformation get_game_information() const;
	void set_view_vec(const Vec2D<float>& view_vec);

private:
	ControlledPlayer read_controlled_player_information(DWORD player_address, DWORD engine_client_state_address);
	std::vector<PlayerInformation> read_other_players(DWORD player_address, DWORD engine_client_state_address);
	Vec3D<float> get_head_bone_position(DWORD entity);
	std::shared_ptr<PlayerInformation> read_player_in_crosshair(DWORD player_address);
	std::shared_ptr<PlayerInformation> get_closest_enemy(const GameInformation& game_info);

	GameInformation game_information;
	ConfigData config_data;
	MemoryManager mem_manager;
	DWORD client_dll_address;
	DWORD engine_address;
};