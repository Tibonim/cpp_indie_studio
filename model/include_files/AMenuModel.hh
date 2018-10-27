#pragma once

#include	<memory>
#include	"MenuLoader.hh"
#include	"GraphicMenu.hh"
#include	"AModel.hh"

namespace	indie {
  class		AMenuModel : public AModel {
  protected:
    typedef std::shared_ptr<GraphicMenu>	graphicMenu_t;
    typedef std::vector<std::string>		buttons_t;
  public:
    AMenuModel(graphicMenu_t& graphic);
  protected:
    void		pushInCollection();
    void		removeAll();
    void		removeElement(std::string const& name);
  protected:
    graphicMenu_t	_graphic;
    buttons_t		_buttons;
    MenuLoader		_loader;
  };
}
