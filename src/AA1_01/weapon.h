#pragma once
#include <string>

class Weapon {
public:
	std::string id;
	std::string type;
	float range;


	Weapon();
	Weapon(std::string _type, std::string _id, float _range);
};