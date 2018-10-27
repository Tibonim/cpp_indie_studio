#include <stdexcept>
#include <iostream>
#include "AModel.hh"

namespace	indie {
  AModel::AModel() : _currentModel{ 0 }, _ret{ true } {
    _components.direction = &_direction;
    _components.velocity = &_velocity;
    _components.strength = &_strength;
    _components.graphic = &_graphic;
    _components.position = &_position;
    _components.script = &_script;
    _components.health = &_health;
    _components.faction = &_faction;
    _components.range = &_range;
    _components.damage = &_damage;
    _components.player = &_player;
    _components.stuff = &_stuff;
    _components.potion = &_potion;
    _components.renforce = &_renforce;
    _components.defense = &_defense;
    _components.attack = &_attack;
  }

  bool		AModel::update() {
    bool	result{};

    if (_currentModel.get() && _currentModel.get() != this)
      result = _currentModel->update();
    else
      result = _update();
    if (!result && !_currentModel.get()) {
      return false;
    }
    else if (!result && _currentModel.get() && _currentModel.get() != this) {
      _currentModel.reset();
      return true;
    }
    return true;
  }
}
