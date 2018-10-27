#include <algorithm>
#include "CollectionException.hh"
#include "AnimationSystem.hh"

namespace	ecs {
  bool	AnimationSystem::getAnimatedEntity(entity const id,
					   collectionGraphic& graphic,
					   collectionVelocity& velocity) const {
    try {
      graphic.getComponent(id);
      velocity.getComponent(id);
    }
    catch (indie::CollectionException const&) {
      return false;
    }
  }

  bool	AnimationSystem::getAttackEntity(entity const id,
					 collectionGraphic& graphic,
					 collectionAttack& attack) const {
    try {
      graphic.getComponent(id);
      attack.getComponent(id);
      return true;
    }
    catch (indie::CollectionException const&) {
      return false;
    }
  }

  void	AnimationSystem::updateGraphicEntity(entity const id,
					     collectionGraphic& graphic,
					     collectionVelocity& velocity) const {
    auto &graphicComponent = graphic.getComponent(id);
    auto &velocityComponent = velocity.getComponent(id);
    if (velocityComponent.velocity <= 0)
      graphicComponent.animationName = "";
    else
      graphicComponent.animationName = "Walk";
  }

  void	AnimationSystem::updateAttackAnimation(entity const id,
					       collectionGraphic& graphic,
					       collectionAttack& attack) const {
    auto &attackComponent = attack.getComponent(id);
    auto &graphicComponent = graphic.getComponent(id);
    if (!attackComponent.isAttack && graphicComponent.animationName == "Attack")
      graphicComponent.animationName = "";
    else if (attackComponent.isAttack)
      graphicComponent.animationName = "Attack";
  }

  bool	AnimationSystem::update(entityCollection const& entities,
				collectionGraphic& graphic,
				collectionVelocity& velocity,
				collectionAttack& attack) const {
    auto eAnimated = entities.getEntitiesOf([&, this](entity const id) {
	return this->getAnimatedEntity(id, graphic, velocity);
      });
    auto eAttack = entities.getEntitiesOf([&, this](entity const id) {
	return this->getAttackEntity(id, graphic, attack);
      });
    std::for_each(eAnimated.begin(), eAnimated.end(), [&, this](entity const id) {
	this->updateGraphicEntity(id, graphic, velocity);
      });
    std::for_each(eAttack.begin(), eAttack.end(), [&, this](entity const id) {
	this->updateAttackAnimation(id, graphic, attack);
      });
  }
}
