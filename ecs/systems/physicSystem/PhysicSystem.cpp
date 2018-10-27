#include <algorithm>
#include "PhysicSystem.hh"

#include <iostream>

namespace	ecs {
  bool		PhysicSystem::getGoodEntities(entity id, collectionDir& direction,
					      collectionVelocity& velocity,
					      collectionPos& pos,
					      collectionGraphic& graph,
					      collectionFaction& faction) const {
    try {
      direction.getComponent(id);
      faction.getComponent(id);
      auto vel = velocity.getComponent(id);
      auto graphic = graph.getComponent(id);
      if (vel.velocity == 0.f) {
	graphic.animationName = "";
	return false;
      }
      pos.getComponent(id);
      return true;
    }
    catch (indie::CollectionException const&) {
      return false;
    }
  }

  bool		PhysicSystem::getFactionFromCollision(entity collision, entity id,
						      collectionFaction& f) const {
    try {
      auto factionCollision = f.getComponent(collision);
      auto factionEntity = f.getComponent(id);
      return static_cast<int>(factionCollision.type) == static_cast<int>(factionEntity.type);
    }
    catch (indie::CollectionException const&) {
      return false;
    }
  }

  bool		PhysicSystem::updateComponents(ov::View *viewSystem,
					       entity id, collectionDir& direction,
					       collectionVelocity& velocity,
					       collectionPos& pos,
					       collectionGraphic& graph,
					       collectionFaction& faction) const {
    try {
      auto &directionComponent = direction.getComponent(id);
      auto &velocityComponent = velocity.getComponent(id);
      auto &posComponent = pos.getComponent(id);
      auto &graphComponent = graph.getComponent(id);
      float x, y, z;
      entity	collision;

      x = posComponent.x + velocityComponent.velocity * directionComponent.x;
      y = posComponent.y + velocityComponent.velocity * directionComponent.y;
      z = posComponent.z + velocityComponent.velocity * directionComponent.z;

      if ((collision = viewSystem->willCollide(id, x, y, z)) != -1) {
      	auto result = getFactionFromCollision(collision, id, faction);
      	if (!result)
      	  return false;
      }
      posComponent.x = x;
      posComponent.y = y;
      posComponent.z = z;
      if (velocityComponent.velocity > 0 && graphComponent.animationName != "Attack")
	graphComponent.animationName = "Walk";
      return true;
    }
    catch (indie::CollectionException const&) {
      return false;
    }
  }

  bool		PhysicSystem::update(ov::View *viewSystem,
				     entityCollection const &collection,
				     collectionDir &direction,
				     collectionVelocity &velocity,
				     collectionPos &pos,
				     collectionGraphic& graphic,
				     collectionFaction& faction) const {
    auto entities = collection.getEntitiesOf([&, this](entity id) {
	return this->getGoodEntities(id, direction, velocity, pos, graphic,
				     faction);
      });
    std::for_each(entities.begin(), entities.end(),
		  [&, this](entity id){
		    return this->updateComponents(viewSystem, id, direction, velocity,
						  pos, graphic, faction);
		  });
    return true;
  }
}
