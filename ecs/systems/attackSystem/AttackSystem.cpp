#include <cmath>
#include <iostream>
#include <algorithm>
#include "CollectionException.hh"
#include "AttackSystem.hh"

namespace	ecs {

  void		AttackSystem::changeDamageOfEntity(entity id,
						   entityCollection const& collection,
						   collectionAttack const& attack,
						   collectionDamage & damage,
						   collectionPosition& position,
						   collectionRange & range,
						   collectionStrength & strength,
						   collectionDirection& direction,
						   collectionFaction& faction) const {
    auto entities = collection.getEntitiesOf([&, this](entity id) {
    	return true;
      });
    std::for_each(entities.begin(), entities.end(), [&, this](entity idd) {
	if (idd == id)
	  return ;

	try {
	  auto factionMe = faction.getComponent(id);
	  auto factionOther = faction.getComponent(idd);
	  if (factionOther.type == factionMe.type)
	    return ;
	  auto posMe = position.getComponent(id);
	  auto posOther = position.getComponent(idd);
	  auto dir = direction.getComponent(id);
	  auto rangeComponent = range.getComponent(id);
	  auto distRange = std::sqrt(rangeComponent.x * rangeComponent.x
	  			     + rangeComponent.y * rangeComponent.y);
	  auto basicDist = std::sqrt((posMe.x-posOther.x) * (posMe.x-posOther.x)
				     + (posMe.y-posOther.y) * (posMe.y-posOther.y)
				     + (posMe.z-posOther.z) * (posMe.z-posOther.z));
	  auto dirDist = std::sqrt((posMe.x+dir.x-posOther.x) * (posMe.x+dir.x-posOther.x)
				     + (posMe.y+dir.y-posOther.y) * (posMe.y+dir.y-posOther.y)
				     + (posMe.z+dir.z-posOther.z) * (posMe.z+dir.z-posOther.z));
	  if (basicDist > distRange || dirDist > basicDist)
	    return ;
	  auto strengthComponent = strength.getComponent(id);
	  auto &damageComponent = damage.getComponent(idd);
	  damageComponent.damageValue += strengthComponent.strength * ((strengthComponent.boost) ? strengthComponent.boost : 1);
	}
	catch (indie::CollectionException const &e) {
	}
      });
  }

  bool		AttackSystem::update(entityCollection const& collection,
				     collectionAttack& attack,
				     collectionDamage& damage,
				     collectionPosition& position,
				     collectionRange& range,
				     collectionStrength& strength,
				     collectionDirection& direction,
				     collectionFaction& faction) const {
    auto entities = collection.getEntitiesOf([&, this](entity const id) {
	try {
	  auto attackComponent = attack.getComponent(id);
	  return attackComponent.isAttack;
	}
	catch(indie::CollectionException const &) {
	  return false;
	}
      });
    std::for_each(entities.begin(), entities.end(), [&, this](entity id) {
    	this->changeDamageOfEntity(id,
				   collection,
				   attack,
				   damage,
				   position,
				   range,
				   strength,
				   direction,
				   faction);
      });
    return true;
  }
}
