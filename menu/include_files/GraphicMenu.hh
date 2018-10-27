#pragma once

#include <iostream>
#include "CEGUI.h"
#include <unistd.h>
#include <OgreWindowEventUtilities.h>
#include <RendererModules/Ogre/Renderer.h>
#include "saveCollection.hh"
#include "InputSystem.hh"
#include "View.hh"

namespace	indie {
  class		MenuModel;
  class		GraphicMenu
  {
  public:
    struct	Pos {
      float	ax;
      float	ay;
      float	bx;
      float	by;
    };
    struct	Size {
      float	ax;
      float	ay;
      float	bx;
      float	by;
    };
    GraphicMenu();
    ~GraphicMenu() = default;
    GraphicMenu	&loadLayout(const std::string&);
    template<typename T>
    GraphicMenu	&bindEventToWidget(const std::string& file,
				   bool (T::*function) (CEGUI::EventArgs const&),
				   T *model,
				   CEGUI::String const& e = CEGUI::PushButton::EventClicked) {
      CEGUI::Window *button = _root->getChild(file);
      button->subscribeEvent(e, CEGUI::Event::Subscriber(function, model));
      return *this;
    }
    GraphicMenu	&loadButton(const std::string&, const std::string&, const std::string&,
			    const Pos&, const Size&);
    GraphicMenu	&loadScheme(const std::string&);
    GraphicMenu	&render();
    GraphicMenu	&loadMouse(std::string const&);
    GraphicMenu	&createBackground(std::string const&, std::string const&);
    GraphicMenu	&setInvisibleButton(std::string const&);
    GraphicMenu	&setVisibleButton(std::string const&);
    GraphicMenu	&removeChildWindow(std::string const&);
    ov::View	*getView();
    CEGUI::Window	*getWindow(std::string const& win) const;
    void		saveBackground(std::string const& file,
				       std::string const& name);
    bool		isBackgroundSet() const;
    void		removeBackground();
  private:
    ov::View			_view;
    CEGUI::GUIContext		*_context;
    CEGUI::OgreRenderer		*_renderer;
    CEGUI::Window		*_root;
    Ogre::SceneManager		*_scMgr;
    Ogre::Root			*_rootMgr;
    Ogre::Rectangle2D		*_rect;
    Ogre::Rectangle2D		*_save;
    Ogre::MaterialPtr		_material;
    bool			_isBackgroundSet;
  };
}
