#pragma once

#include <algorithm>
#include <vector>
#include "entityType.hh"

namespace	ecs {
  class		entityCollection {
  public:
    typedef std::vector<entity>	entityList;
    entity	createEntity();
    void	addEntity(entity const id);
    void	removeEntity(entity id);
    entityList	getEntities() const;
    template<typename UnaryPredicate>
    entityList	getEntitiesOf(UnaryPredicate p) const;
  private:
    entityList	_entities;
  };

  template<typename Predicate>
  entityCollection::entityList	entityCollection::getEntitiesOf(Predicate p) const {
    entityCollection::entityList	result{};
    std::for_each(_entities.begin(), _entities.end(),
		  [&](entity e){
		    if (p(e)) result.push_back(e);
		  });
    return result;
  }
}
