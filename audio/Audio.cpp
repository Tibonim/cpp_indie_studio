#include "Audio.hh"


namespace	indie {
  std::vector<sf::Sound *> *Audio::_sounds = new std::vector<sf::Sound *>;
  std::vector<sf::Music *> *Audio::_musics = new std::vector<sf::Music *>;
  float Audio::_volume = 50;

  bool Audio::playSound(std::string const &file) {
    sf::SoundBuffer *buff = new sf::SoundBuffer;
    if (!buff->loadFromFile(file))
      return false;
    sf::Sound *n = new sf::Sound;
    n->setBuffer(*buff);
    n->setVolume(_volume);
    n->play();
    _sounds->push_back(n);
  }

  bool Audio::playMusic(std::string const &file) {
    sf::Music *music = new sf::Music;
    if (!music->openFromFile(file))
      return false;
    music->play();
    music->setLoop(true);
    music->setVolume(_volume);
    _musics->push_back(music);
  }

  void Audio::setPitch(float p) {
    for (auto it = _musics->begin(); it != _musics->end(); ++it)
      (*it)->setPitch(p);
    for (auto it = _sounds->begin(); it != _sounds->end(); ++it)
      (*it)->setPitch(p);
  }

  void Audio::stop() {
    for (auto it = _musics->begin(); it != _musics->end(); ++it) {
      (*it)->stop();
      delete (*it);
    }
    for (unsigned i = 0; i < _musics->size(); ++i) {
      _musics->pop_back();
    }
  }

  float Audio::getVolume() {
    return _volume;
  }

  void Audio::setVolume(float v) {
    if (v < 0)
      _volume = 0;
    if (v > 100)
      _volume = 100;
    for (auto it = _musics->begin(); it != _musics->end(); ++it) {
      (*it)->setVolume(v);
    }
    for (auto it = _sounds->begin(); it != _sounds->end(); ++it) {
      (*it)->setVolume(v);
    }
    _volume = v;
  }
}
