#pragma once

#include <vector>
#include <SFML/Audio.hpp>
#include "SingletonPattern.hh"

namespace	indie {
  class Audio : private event::SingletonPattern {
  public:
    static bool playSound(std::string const &);
    static bool playMusic(std::string const &);
    static float getVolume();
    static void setVolume(float);
    static void setPitch(float);
    static void stop();
  private:
    static std::vector<sf::Sound *> *_sounds;
    static std::vector<sf::Music *> *_musics;
    static float _volume;
  };
}
