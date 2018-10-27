#include "EventManager.hh"

namespace event
{
  void EventManager::createFrameListener(void)
  {
    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;

    Window->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

    _InputManager = OIS::InputManager::createInputSystem(pl);

    _Keyboard = static_cast<OIS::Keyboard*>(_InputManager->createInputObject(OIS::OISKeyboard, true));
    _Mouse = static_cast<OIS::Mouse*>(_InputManager->createInputObject(OIS::OISMouse, true));
    if (_Mouse){
      _Mouse->setEventCallback(this);
    }
    _Keyboard->setEventCallback(this);

    windowResized(Window);

    Ogre::WindowEventUtilities::addWindowEventListener(Window, this);

    _InputContext.mKeyboard = _Keyboard;
    _InputContext.mMouse = _Mouse;
    _TrayMgr = new OgreBites::SdkTrayManager("InterfaceName", Window, _InputContext, this);
    _TrayMgr->hideCursor();
    Root->addFrameListener(this);
  }

  bool EventManager::frameRenderingQueued(const Ogre::FrameEvent& evt)
  {
    if (Window->isClosed())
      {
	return false;
      }
    if (ShutDown)
      return false;
    _Keyboard->capture();
    _Mouse->capture();
    if (evt.timeSinceLastFrame != 0)
      CEGUI::System::getSingleton().injectTimePulse(evt.timeSinceLastFrame);
    keyEvent();
    return true;
  }
}
