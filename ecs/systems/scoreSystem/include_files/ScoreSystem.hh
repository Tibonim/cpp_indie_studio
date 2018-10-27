#pragma once

#include <memory>
#include <string>
#include "MenuLoader.hh"
#include "GraphicMenu.hh"
#include "NonCopyable.hh"
#include "componentType.hh"

namespace	ecs {
  class		ScoreSystem : private NonCopyable {
    typedef std::shared_ptr<indie::GraphicMenu>	graphicMenu_t;
  public:
    ScoreSystem(graphicMenu_t& graphic);
    bool	update(scoreComponent& score);
    void	deleteScore();
  private:
    void	displayScore();
    void	loadButton();
  private:
    std::size_t		_waveNbr;
    std::size_t		_scoreRegistered;
    graphicMenu_t	_graphic;
    indie::MenuLoader	_loader;
    std::string		_button;
  };
}
