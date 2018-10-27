#include "KeyCollection.hh"
#include "EngineException.hh"
#include "Engine.hh"

namespace indie {
  Engine::Engine(std::string const &keyConf) {
    try {
      event::KeyCollection::load(keyConf);
    }
    catch(indie::KeyCollectionException const &e) {
      throw EngineException{e.what()};
    }
  }

  bool Engine::run(IModel *model) const {
    while (model && model->update());
    return true;
  }
}
