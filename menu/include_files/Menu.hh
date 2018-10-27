#pragma once

#include <iostream>
#include "CEGUI.h"
#include <unistd.h>
#include <OgreWindowEventUtilities.h>
#include <RendererModules/Ogre/Renderer.h>
#include "saveCollection.hh"
#include "InputSystem.hh"
#include "GameModel.hh"

namespace	indie {
  class		GraphicMenu
  {
  public:
    GraphicMenu();
    ~GraphicMenu() {};
    GraphicMenu	&loadLayout(std::string const&);
    GraphicMenu	&bindEventToWidget(std::string const&, function);
    GraphicMenu	&loadScheme(std::string const&);
    GraphicMenu &render();
  private:
    CEGUI::WindowManager	&_wmgr;
    CEGUI::GUIContext		*_context;
    CEGUI::Window		*_root;
    CEGUI::OgreRenderer		*_renderer;
    ov::View			_view;
  };
};
