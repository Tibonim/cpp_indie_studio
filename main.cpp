#include <iostream>
#include "Spawner.hh"
#include "loader.hh"
#include "MenuModel.hh"
#include "IModel.hpp"
#include "Engine.hh"
#include "EngineException.hh"
#include "EventHandler.hh"
#include "Audio.hh"

int	main()
{
  indie::Audio::playMusic("media/ambiance.wav");
  indie::Audio::setPitch(1.5);
  try {
    indie::ConfigurationLoader::loadCfgConfiguration("./config/configuration.cfg");
    indie::Engine engine(indie::ConfigurationLoader::getFile("keys.json"));
    engine.run(new indie::MenuModel{});
    indie::Audio::stop();
  }
  catch(indie::CustomException const &e) {
    std::cerr << e.what() << std::endl;
    return (-1);
  }
}
