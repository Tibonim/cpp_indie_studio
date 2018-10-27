#include <algorithm>
#include "AMenuModel.hh"

namespace	indie {
  AMenuModel::AMenuModel(AMenuModel::graphicMenu_t& graphic)
    : _graphic{ graphic } {}

  void		AMenuModel::pushInCollection() {
    auto collection = _loader.getButtons();
    std::for_each(collection.begin(), collection.end(),
		  [this](MenuLoader::Button const& b) {
		    this->_graphic->loadButton(b.text, "TaharezLook/Button",
					       b.text,
					       GraphicMenu::Pos{ b.ax, b.ay, b.bx,
						   b.by },
					       GraphicMenu::Size{ b.sax, b.say,
						   b.sbx, b.sby});
		    this->_buttons.push_back(b.text);
		    return ;
		  });
  }

  void		AMenuModel::removeAll() {
    std::for_each(_buttons.begin(), _buttons.end(),
		  [this](std::string const& name) {
		    try {
		      this->_graphic->removeChildWindow(name);
		    }
		    catch (CEGUI::Exception const& ca) {
		    }
		  });
    _buttons.clear();
  }

  void		AMenuModel::removeElement(std::string const& name) {
    _graphic->removeChildWindow(name);
    _buttons.erase(std::remove_if(_buttons.begin(), _buttons.end(),
				  [&](std::string const& win) {
				    return win == name;
				  }),
		   _buttons.end());
  }
}
