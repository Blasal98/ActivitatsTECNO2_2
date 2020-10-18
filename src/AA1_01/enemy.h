#pragma once
#include <string>
#include <vector>
#include "weapon.h"

class Enemy {
public:
	std::string name;
	float health;
	float defense;
	float attack;
	float atkSpeed;
	float exp;

	std::vector<Weapon> weapons;

	Enemy();
	Enemy(std::string _name, float _health, float _defense, float _attack, float _atkSpeed, float _exp, std::vector<Weapon> _weapons);
};