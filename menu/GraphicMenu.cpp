#include	"CustomException.hh"
#include	"GraphicMenu.hh"

namespace	indie {
  GraphicMenu::GraphicMenu() : _view{}, _isBackgroundSet{ false } {
    try {
      _renderer = &CEGUI::OgreRenderer::bootstrapSystem();
      CEGUI::ImageManager::setImagesetDefaultResourceGroup("General");
      CEGUI::Scheme::setDefaultResourceGroup("General");
      CEGUI::Font::setDefaultResourceGroup("General");
      CEGUI::WidgetLookManager::setDefaultResourceGroup("General");
      CEGUI::WindowManager::setDefaultResourceGroup("General");
      auto &wmgr = CEGUI::WindowManager::getSingleton();
      _root = wmgr.createWindow("DefaultWindow", "root");
      _context = &CEGUI::System::getSingleton().getDefaultGUIContext();
      _context->setRootWindow(_root);
      _scMgr = _view.getSceneManager();
      _rootMgr = _view.getRoot();
    }
    catch (Ogre::RenderingAPIException const&) {
      throw indie::CustomException{ "Error while trying to initialize ogre" };
    }
  }

  GraphicMenu&	GraphicMenu::loadMouse(std::string const& mouse) {
    CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage(mouse);
    _context->getMouseCursor().setImage(_context->getMouseCursor().getDefaultImage());
    return *this;
  }

  GraphicMenu&	GraphicMenu::loadLayout(std::string const& file) {
    auto &wmgr = CEGUI::WindowManager::getSingleton();
    _root = wmgr.loadLayoutFromFile(file);
    _context->setRootWindow(_root);
    return (*this);
  }

  GraphicMenu&	GraphicMenu::loadScheme(std::string const& file) {
    CEGUI::SchemeManager::getSingleton().createFromFile(file);
    return (*this);
  }

  void		GraphicMenu::saveBackground(std::string const& file,
					    std::string const& name) {
    _scMgr->destroySceneNode(name);
    _scMgr->getRootSceneNode()->detachAllObjects();
    _isBackgroundSet = false;
    delete _rect;
  }

  GraphicMenu&	GraphicMenu::createBackground(std::string const& file,
					      std::string const& name) {
    _material = Ogre::MaterialManager::getSingleton().create(name, "General");
    _material->getTechnique(0)->getPass(0)->createTextureUnitState(file);
    _material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
    _material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
    _material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
    _rect = new Ogre::Rectangle2D(true);
    _rect->setCorners(-1.0, 1.0, 1.0, -1.0);
    _rect->setMaterial(name);
    Ogre::SceneNode* node = _scMgr->getRootSceneNode()->createChildSceneNode(name);
    node->attachObject(_rect);
    _isBackgroundSet = true;
    return *this;
  }

  GraphicMenu&	GraphicMenu::loadButton(const std::string& name,
					const std::string& style,
					const std::string& text,
					const Pos& pos,
					const Size& size) {
    CEGUI::Window *button = CEGUI::WindowManager::getSingleton().createWindow(style,
									      name);
    button->setPosition(CEGUI::UVector2( CEGUI::UDim(pos.ax, pos.ay),
					 CEGUI::UDim(pos.bx, pos.by)));
    button->setSize(CEGUI::USize(CEGUI::UDim(size.ax, size.ay),
				 CEGUI::UDim(size.bx, size.by)));
    button->setText(text);
    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(button);
    return *this;
  }

  GraphicMenu&	GraphicMenu::setInvisibleButton(std::string const& butName) {
    CEGUI::Window	*button = _root->getChild(butName);
    button->setVisible(false);
    return *this;
  }

  GraphicMenu&	GraphicMenu::removeChildWindow(std::string const& win) {
    _root->destroyChild(win);
    return *this;
  }

  GraphicMenu&	GraphicMenu::setVisibleButton(std::string const& butName) {
    CEGUI::Window	*button = _root->getChild(butName);
    button->setVisible(true);
    return *this;
  }

  ov::View	*GraphicMenu::getView() {
    return &_view;
  }

  bool		GraphicMenu::isBackgroundSet() const {
    return _isBackgroundSet;
  }

  CEGUI::Window	*GraphicMenu::getWindow(std::string const& win) const {
    return _root->getChild(win);
  }

  GraphicMenu&	GraphicMenu::render() {
    _view.startRendering();
    return *this;
  }

}
