#include "weapon.h"

Weapon::Weapon() {

}
Weapon::Weapon(std::string _type, std::string _id, float _range) {
	type = _type;
	id = _id;
	range = _range;
}