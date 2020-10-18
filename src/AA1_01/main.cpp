#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include "enemy.h"
#include "weapon.h"

#include "../../dep/inc/XML/rapidxml.hpp"
#include "../../dep/inc/XML/rapidxml_iterators.hpp"
#include "../../dep/inc/XML/rapidxml_print.hpp"
#include "../../dep/inc/XML/rapidxml_utils.hpp"



int main() {

	std::vector<Enemy> enemies;

	rapidxml::xml_document<> doc;

	//std::ifstream file("C:/Users/****/OneDrive/Documentos_main/AAAVICTOR/1----ENTI----1/2. SEGON/REPETISIONES/TECNO2_2/ActivitatsAvaluables/Activitats/res/files/config.xml");
	std::ifstream file("../../res/files/config.xml");
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);

	//std::cout << doc.first_node()->first_node()->first_attribute()->value();

	rapidxml::xml_node<> *pRoot = doc.first_node();
	int i = 0;

	for (rapidxml::xml_node<> *pNode = pRoot->first_node("enemy"); pNode; pNode = pNode->next_sibling()) {

		std::string name(pNode->first_attribute("name")->value());
		float health = std::stoi(pNode->first_node("health")->value());
		float defense = std::stoi(pNode->first_node("defense")->value());
		float attack = std::stoi(pNode->first_node("attack")->value());
		float atkSpeed = std::stof(pNode->first_node("atkSpeed")->value());
		float exp = atof(pNode->first_node("exp")->value());
		//atof
		std::vector<Weapon> weapons;

		for (rapidxml::xml_node<> *pNode1 = pNode->first_node("weapon"); pNode1; pNode1 = pNode1->next_sibling()) {
			std::string type = std::string(pNode1->first_attribute("type")->value());
			std::string id = std::string(pNode1->first_node("id")->value());
			float range = std::stoi(pNode1->first_node("range")->value());
			Weapon auxWeapon = Weapon(type, id, range);
			weapons.push_back(auxWeapon);
		}

		Enemy auxEnemy = Enemy(name, health, defense, attack, atkSpeed, exp, weapons);
		enemies.push_back(auxEnemy);
		std::cout << enemies[i].name << " / " << enemies[i].health << " / " << enemies[i].defense << " / " << enemies[i].attack << " / " << enemies[i].atkSpeed << " / " << enemies[i].exp << std::endl;
		std::cout << enemies[i].weapons[0].id << " / " << enemies[i].weapons[0].range << " / " << enemies[i].weapons[0].type << std::endl;
		std::cout << "--------------------------------" << std::endl;
		i++;
	}


	return 0;
}
