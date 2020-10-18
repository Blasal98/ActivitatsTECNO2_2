#include "enemy.h"

Enemy::Enemy() {

}
Enemy::Enemy(std::string _name, float _health, float _defense, float _attack, float _atkSpeed, float _exp, std::vector<Weapon> _weapons) {
	health = _health;
	defense = _defense;
	attack = _attack;
	atkSpeed = _atkSpeed;
	exp = _exp;
	weapons = _weapons;
}