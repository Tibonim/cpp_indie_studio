#include <cassert>
#include <iostream>
#include "IaBinding.hh"

namespace	ecs {
  IaBinding::IaBinding() :
    _bindFile{ true },
    _binder{ 0 } {
  }

  void		IaBinding::setBinder(BinderComponent& component) {
    _binder = &component;
  }

  void		IaBinding::bindFile(std::string const& fileName) {
    _bindFile["Binder"].SetObj((*_binder),
			       "getDirX", &BinderComponent::getDirX,
			       "getDirY", &BinderComponent::getDirY,
			       "getDirZ", &BinderComponent::getDirZ,
			       "getVelocity", &BinderComponent::getVelocity,
			       "getPosX", &BinderComponent::getPosX,
			       "getPosY", &BinderComponent::getPosY,
			       "getPosZ", &BinderComponent::getPosZ,
			       "getLive", &BinderComponent::getLive,
			       "getStrength", &BinderComponent::getStrength,
			       "getFaction", &BinderComponent::getFaction,
			       "getRangeX", &BinderComponent::getRangeX,
			       "getRangeY", &BinderComponent::getRangeY,
			       "getEntityFromCollection",
			       &BinderComponent::getEntityFromCollection,
			       "getNbrOfEntities", &BinderComponent::getNbrOfEntities,
			       "getCurrentIa", &BinderComponent::getCurrentIa,
			       "setDirection", &BinderComponent::setDirection,
			       "setVelocity", &BinderComponent::setVelocity,
			       "setPosition", &BinderComponent::setPosition,
			       "setLive", &BinderComponent::setLive,
			       "setStrength", &BinderComponent::setStrength,
			       "setAttack", &BinderComponent::setAttack,
			       "setDamage", &BinderComponent::setDamage);
    _bindFile.Load(fileName);
  }
}
