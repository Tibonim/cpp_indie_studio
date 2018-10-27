#pragma once

#include <algorithm>
#include <utility>
#include <vector>
#include "entityCollection.hh"
#include "CollectionException.hh"
#include "potionComponent.hh"
#include "renforceComponent.hh"
#include "speedUpComponent.hh"

namespace	ecs {
  template<typename ComponentType>
  class	componentCollection {
  public:
    typedef std::vector<ComponentType>	componentList;
    template<typename... Args>
    ComponentType	addComponent(entity id, Args&&... args);
    void		eraseComponent(entity id);
    ComponentType	&getComponent(entity id);
    template<typename Predicate>
    componentList	getComponentsOf(Predicate p) const;
    bool		empty() const;
  private:
    componentList	_component;
  };

  template<typename ComponentType> template<typename... Args>
  ComponentType	componentCollection<ComponentType>::addComponent(entity id,
								  Args&&... args) {
    auto result = ComponentType{ id, std::forward<Args>(args)... };
    _component.push_back(result);
    return result;
  }

  template<typename ComponentType>
  bool	componentCollection<ComponentType>::empty() const {
    return _component.empty();
  }

  template<typename ComponentType>
  void		componentCollection<ComponentType>::eraseComponent(entity id) {
    _component.erase(std::remove_if(_component.begin(), _component.end(),
				    [=](ComponentType e){ return e.id == id; }),
		     _component.end());
  }

  template<typename ComponentType>
  ComponentType	&componentCollection<ComponentType>::getComponent(entity id) {
    auto component = std::find_if(_component.begin(), _component.end(),
				  [=](ComponentType const &c){ return c.id == id; });
    if (component == _component.end())
      throw indie::CollectionException{ "Error, component not found" };
    return *component;
  }

  template<typename ComponentType> template<typename Predicate>
  typename componentCollection<ComponentType>::componentList
  componentCollection<ComponentType>::getComponentsOf(Predicate p) const {
    typename componentCollection<ComponentType>::componentList	result{};
    std::for_each(_component.begin(), _component.end(),
		  [&](ComponentType c) { if (p(c)) result.push_back(c); });
    return result;
  }
}
