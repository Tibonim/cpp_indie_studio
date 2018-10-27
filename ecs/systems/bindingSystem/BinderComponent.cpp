#include "IaSystemException.hh"
#include "BinderComponent.hh"

namespace	ecs {
  BinderComponent::BinderComponent(entity const id) :
    _direction{ 0 }, _velocity{ 0 }, _position{ 0 }, _health{ 0 }, _strength{ 0 },
    _faction{ 0 }, _range{ 0 }, _damages{ 0 }, _entities{ 0 }, _id{ id } {
  }

  /*
  ** The following functions are available to set the new components
  ** in the binding.
  */

  BinderComponent	&BinderComponent::setNewComponent(collectionDir& collection) {
    _direction = &collection;
    return *this;
  }

  BinderComponent	&BinderComponent::setNewComponent(collectionDamage& collection) {
    _damages = &collection;
    return *this;
  }

  BinderComponent	&BinderComponent::setNewComponent(collectionVelocity& collection) {
    _velocity = &collection;
    return *this;
  }

  BinderComponent	&BinderComponent::setNewComponent(collectionPos& collection) {
    _position = &collection;
    return *this;
  }

  BinderComponent	&BinderComponent::setNewComponent(collectionHealth& collection) {
    _health = &collection;
    return *this;
  }

  BinderComponent	&BinderComponent::setNewComponent(collectionAttack& collection) {
    _attack = &collection;
    return *this;
  }

  BinderComponent	&BinderComponent::setNewComponent(collectionStrength& collection) {
    _strength = &collection;
    return *this;
  }

  BinderComponent	&BinderComponent::setNewComponent(collectionFaction& collection) {
    _faction = &collection;
    return *this;
  }

  BinderComponent	&BinderComponent::setNewComponent(collectionRange& collection) {
    _range = &collection;
  }

  /*
  ** Getter for the direction component
  */

  double	BinderComponent::getDirX(entity const id) {
    if (!_direction)
      throw indie::IaSystemException{ "Error, no directions found" };
    auto &direction = _direction->getComponent(id);
    return static_cast<double>(direction.x);
  }

  double	BinderComponent::getDirY(entity const id) {
    if (!_direction)
      throw indie::IaSystemException{ "Error, no directions found" };
    auto &direction = _direction->getComponent(id);
    return static_cast<double>(direction.y);
  }

  double	BinderComponent::getDirZ(entity const id) {
    if (!_direction)
      throw indie::IaSystemException{ "Error, no directions found" };
    auto &direction = _direction->getComponent(id);
    return static_cast<double>(direction.z);
  }

  /*
  ** Setter for the direction component
  */

  void		BinderComponent::setDirection(entity const id, double x, double y,
					      double z) {
    if (!_direction)
      throw indie::IaSystemException{ "Error, directionCollection is null" };
    auto &direction = _direction->getComponent(id);
    direction.x = static_cast<float>(x);
    direction.y = static_cast<float>(y);
    direction.z = static_cast<float>(z);
  }

  /*
  ** Getter for the velocity component
  */

  double	BinderComponent::getVelocity(entity const id) {
    if (!_velocity)
      throw indie::IaSystemException{ "Error, no velocity found" };
    auto &velocity = _velocity->getComponent(id);
    return static_cast<double>(velocity.velocity);
  }

  /*
  ** Setter for the velocity component
  */

  void		BinderComponent::setVelocity(entity const id, double velocity) {
    if (!_velocity)
      throw indie::IaSystemException{ "Error, no velocity component !" };
    auto &velocityComponent = _velocity->getComponent(id);
    velocityComponent.velocity = static_cast<float>(velocity);
  }

  void		BinderComponent::setAttack(entity const id, bool attack) {
    if (!_attack)
      throw indie::IaSystemException{ "Error, no attack component !" };
    auto &attackComponent = _attack->getComponent(id);
    attackComponent.isAttack = static_cast<bool>(attack);
  }

  /*
  ** Getter for the position component
  */

  double	BinderComponent::getPosX(entity const id) {
    if (!_position)
      throw indie::IaSystemException{ "Error, no position found" };
    auto &position = _position->getComponent(id);
    return static_cast<double>(position.x);
  }

  double	BinderComponent::getPosY(entity const id) {
    if (!_position)
      throw indie::IaSystemException{ "Error, no position found" };
    auto &position = _position->getComponent(id);
    return static_cast<double>(position.y);
  }

  double	BinderComponent::getPosZ(entity const id) {
    if (!_position)
      throw indie::IaSystemException{ "Error, no position found" };
    auto &position = _position->getComponent(id);
    return static_cast<double>(position.z);
  }

  /*
  ** Setter for the position component
  */

  void		BinderComponent::setPosition(entity const id, double x, double y,
					     double z) {
    if (!_position)
      throw indie::IaSystemException{ "Error, no position component found !" };
    auto &position = _position->getComponent(id);
    position.x = static_cast<float>(x);
    position.y = static_cast<float>(y);
    position.z = static_cast<float>(z);
  }

  /*
  ** Getter for the health component
  */

  double	BinderComponent::getLive(entity const id) {
    if (!_health)
      throw indie::IaSystemException{ "Error, no health found" };
    auto &live = _health->getComponent(id);
    return static_cast<double>(live.live);
  }

  /*
  ** Setter for the health component
  */

  void		BinderComponent::setLive(entity const id, double live) {
    if (!_health)
      throw indie::IaSystemException{ "Error, no health found" };
    auto &liveC = _health->getComponent(id);
    liveC.live = static_cast<float>(live);
  }

  /*
  ** Getter for the strength component
  */

  double	BinderComponent::getStrength(entity const id) {
    if (!_strength)
      throw indie::IaSystemException{ "Error, no strength found" };
    auto &strength = _strength->getComponent(id);
    return static_cast<double>(strength.strength);
  }

  /*
  ** Setter for the strength component
  */

  void		BinderComponent::setStrength(entity const id,
					     double strength) {
    if (!_strength)
      throw indie::IaSystemException{ "Error, no strength found" };
    auto &strengthComponent = _strength->getComponent(id);
    strengthComponent.strength = static_cast<float>(strength);
  }

  /*
  ** Getter for the faction component
  */

  int		BinderComponent::getFaction(entity const id) {
    if (!_faction)
      throw indie::IaSystemException{ "Error, no faction found" };
    auto &faction = _faction->getComponent(id);
    auto &iaFaction = _faction->getComponent(_id);
    return static_cast<int>(iaFaction.type) != static_cast<int>(faction.type);
  }

  /*
  ** Getter for the range component
  */

  double	BinderComponent::getRangeX(entity const id) {
    if (!_range)
      throw indie::IaSystemException{ "Error, no range found" };
    auto &range = _range->getComponent(id);
    return static_cast<double>(range.x);
  }

  double	BinderComponent::getRangeY(entity const id) {
    if (!_range)
      throw indie::IaSystemException{ "Error, no range found" };
    auto &range = _range->getComponent(id);
    return static_cast<double>(range.y);
  }

  entity        BinderComponent::getCurrentIa() {
    return _id;
  }

  /*
  ** Getter for the damage component
  */

  double	BinderComponent::getDamage(entity const id) {
    if (!_damages)
      throw indie::IaSystemException{ "Error, this entity doesn't have damage" };
    auto &damage = _damages->getComponent(id);
    return static_cast<double>(damage.damageValue);
  }

  /*
  ** Setter for the damage component
  */

  void		BinderComponent::setDamage(entity const id, double damage) {
    if (!_damages)
      throw indie::IaSystemException{ "Error, this entity doesn't have damage" };
    auto &damages = _damages->getComponent(id);
    damages.damageValue = static_cast<float>(damage);
  }

  /*
  ** Set new collection of entities
  */

  BinderComponent	&BinderComponent::setNewCollection(std::vector<entity> const& collection) {
    _entities = &collection;
  }

  int		BinderComponent::getNbrOfEntities() {
    if (!_entities)
      throw indie::IaSystemException{ "Error, no entityCollection is specified" };
    return _entities->size();
  }

  entity	BinderComponent::getEntityFromCollection(int const idx) {
    if (!_entities)
      throw indie::IaSystemException{ "Error, no entityCollection is specified" };
    if (idx >= _entities->size())
      throw indie::IaSystemException{ "Error, index out of bound" };
    return (*_entities)[idx];
  }

}
