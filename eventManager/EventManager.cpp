#include "EventManager.hh"
#include "EventHandler.hh"
#include "KeyCollection.hh"

namespace event {

  EventManager::EventManager(Ogre::RenderWindow *window, Ogre::Root *root,
			     Ogre::Camera *camera)
  {
    Root = root;
    Window = window;
    Camera = camera;
    ShutDown = false;
  }

  void EventManager::keyEvent()
  {
  }

  OIS::InputManager	*EventManager::getInputManager() const {
    return _InputManager;
  }

  void	EventManager::setInputManager(OIS::InputManager *im) {
    _InputManager = im;
  }

  OIS::Mouse	*EventManager::getMouse() const {
    return _Mouse;
  }

  OIS::Keyboard	*EventManager::getKeyboard() const {
    return _Keyboard;
  }

  void	EventManager::setEntityCollection(std::vector<ov::VEntity *> newEntityCollection)
  {
    entityCollection = newEntityCollection;
  }

  int	EventManager::remove_key(OIS::KeyCode const &key)
  {
    int	ret;

    std::vector<std::pair<OIS::KeyCode, unsigned int>> newKeys;
    ret = -1;
    for (auto const &it : this->keys)
      {
	if (it.first != key){
	  newKeys.push_back(it);
	}
	else
	  {
	    ret = static_cast<int>(it.second);
	  }
      }
    CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp((CEGUI::Key::Scan)key);
    keys = newKeys;
    return (ret);
  }

  bool	EventManager::push_key(OIS::KeyCode const &key, unsigned int text)
  {
    for (auto const &it : this->keys)
      {
	if (it.first == key)
	  return (false);
      }
    keys.push_back(std::make_pair(key, text));
    return (true);
  }

  bool EventManager::keyPressed( const OIS::KeyEvent &arg )
  {
    event::key value;

    if (push_key(arg.key, arg.text) == true)
      {
	CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown((CEGUI::Key::Scan)arg.key);
	CEGUI::System::getSingleton().getDefaultGUIContext().injectChar((CEGUI::Key::Scan)arg.text);
      }
    try {
      value = KeyCollection::getKey(arg.text);
      for (auto const &it : this->entityCollection)
	{
	  if (value.type == it->getPlayer())
	    {
	      EventHandler::push(eventProtocol{static_cast<int>(arg.text), it->getId(), true});
	      return (true);
	    }
	}
    }
    catch (indie::CustomException const& c){
    }
    return true;
  }

  bool EventManager::keyReleased(const OIS::KeyEvent &arg)
  {
    event::key value;
    int		text;

    text = remove_key(arg.key);
    try {
      value = KeyCollection::getKey(text);
      for (auto const &it : this->entityCollection)
	{
	  if (value.type == it->getPlayer())
	    {
	      EventHandler::push(eventProtocol{static_cast<int>(text), it->getId(), false});
	      return (true);
	    }
	}
    }
    catch (indie::CustomException const& c){
    }
    return true;
  }

  bool EventManager::mouseMoved(const OIS::MouseEvent &arg)
  {
    CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove((float)arg.state.X.rel, (float)arg.state.Y.rel);
    _TrayMgr->injectMouseMove(arg);
    return true;
  }

  CEGUI::MouseButton EventManager::convertButton(OIS::MouseButtonID const &buttonID){
    if (buttonID == OIS::MB_Left)
      return (CEGUI::LeftButton);
    else if (buttonID == OIS::MB_Right)
      return (CEGUI::RightButton);
    else
      return (CEGUI::LeftButton);
  }

  bool EventManager::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
  {
    CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(convertButton(id));
    if (_TrayMgr->injectMouseDown(arg, id)) return true;
    return true;
  }

  bool EventManager::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
  {
    CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(convertButton(id));
    if (_TrayMgr->injectMouseUp(arg, id)) return true;
    return true;
  }

  void	EventManager::windowResized(Ogre::RenderWindow* rw)
  {
    unsigned int width, height, depth;
    int left, top;

    rw->getMetrics(width, height, depth, left, top);
    if (_Mouse){
      const OIS::MouseState &ms = _Mouse->getMouseState();
      ms.width = width;
      ms.height = height;
    }
  }

  void EventManager::windowClosed(Ogre::RenderWindow* rw)
  {
    if(rw == Window)
      {
	if(_InputManager)
	  {
	    _InputManager->destroyInputObject(_Mouse);
	    _InputManager->destroyInputObject(_Keyboard);

	    OIS::InputManager::destroyInputSystem(_InputManager);
	    _InputManager = 0;
	  }
      }
  }
}
