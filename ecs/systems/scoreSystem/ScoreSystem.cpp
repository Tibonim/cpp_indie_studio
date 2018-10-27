#include <algorithm>
#include "loader.hh"
#include "CollectionException.hh"
#include "ScoreSystem.hh"

namespace	ecs {
  ScoreSystem::ScoreSystem(ScoreSystem::graphicMenu_t& graphic)
    : _waveNbr{ 1 }, _scoreRegistered{ 1 }, _graphic{ graphic } {
      _loader.loadButtonFromFile(indie::ConfigurationLoader::getFile("score.json"),
				 "ScorePage");
      _button = "";
      displayScore();
    }

  void	ScoreSystem::loadButton() {
    auto bScore = _loader["score"];
    std::string	name{ bScore.text + std::to_string(_scoreRegistered) };
    _graphic->loadButton(bScore.name, "TaharezLook/Button", name,
			 indie::GraphicMenu::Pos{ bScore.ax, bScore.ay,
			     bScore.bx, bScore.by },
			 indie::GraphicMenu::Size{ bScore.sax, bScore.say, bScore.sbx,
			     bScore.sby });
    _button = bScore.name;
  }

  void	ScoreSystem::displayScore() {
    if (_button == "") {
      loadButton();
      return ;
    }
    auto bScore = _loader["score"];
    std::string	name{ bScore.text + std::to_string(_scoreRegistered) };
    CEGUI::Window	*win = _graphic->getWindow(_button);
    win->setText(name);
  }

  void	ScoreSystem::deleteScore() {
    _graphic->removeChildWindow(_button);
    _button = "";
  }

  bool	ScoreSystem::update(scoreComponent& score) {
    score.value += 10 * _waveNbr;
    _scoreRegistered = score.value;
    ++_waveNbr;
    displayScore();
  }
}
