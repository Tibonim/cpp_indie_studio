#include <algorithm>
#include <stdexcept>
#include "CollectionException.hh"
#include "entityCollection.hh"

namespace	ecs {
  entity	entityCollection::createEntity() {
    auto id = _entities.empty() ? 0 : _entities.back() + 1;
    _entities.push_back(id);
    return id;
  }

  void		entityCollection::addEntity(entity const id) {
    auto	it = std::find_if(_entities.begin(), _entities.end(),
				  [=](entity const cmp) { return cmp == id; });
    if (it != _entities.end())
      throw indie::CollectionException{ "Error, entity already exist" };
    _entities.push_back(id);
  }

  void		entityCollection::removeEntity(entity id) {
    _entities.erase(std::remove(_entities.begin(), _entities.end(), id),
		    _entities.end());
  }

  entityCollection::entityList	entityCollection::getEntities() const {
    return _entities;
  }

}
