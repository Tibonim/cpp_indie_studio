#pragma once

#include "CEGUI.h"
#include "protocol.hh"
#include "Includes.hh"
#include "Entity.hpp"
#include <utility>

namespace event{
  class	EventManager : public Ogre::FrameListener, public Ogre::WindowEventListener, public OIS::KeyListener, public OIS::MouseListener, OgreBites::SdkTrayListener {
  public:
    EventManager(Ogre::RenderWindow *window, Ogre::Root	*root, Ogre::Camera *camera);
    ~EventManager() = default;
    void keyEvent(void);
    bool keyPressed(const OIS::KeyEvent &arg);
    bool keyReleased(const OIS::KeyEvent &arg);
    bool mouseMoved(const OIS::MouseEvent &arg);
    bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    void windowResized(Ogre::RenderWindow* rw);
    void windowClosed(Ogre::RenderWindow* rw);
    void createFrameListener();
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
    void setEntityCollection(std::vector<ov::VEntity *> newEntityCollection);

    OIS::InputManager		*getInputManager() const;
    void			setInputManager(OIS::InputManager *im);
    OIS::Mouse			*getMouse() const;
    OIS::Keyboard		*getKeyboard() const;

  private:
    OIS::InputManager*		_InputManager;
    OIS::Mouse*                 _Mouse;
    OIS::Keyboard*              _Keyboard;
    OgreBites::SdkTrayManager*  _TrayMgr;
    OgreBites::InputContext     _InputContext;
    OgreBites::ParamsPanel*     _DetailsPanel;
    bool			ShutDown;
    Ogre::RenderWindow		*Window;
    Ogre::Root			*Root;
    Ogre::Camera		*Camera;
    std::vector<ov::VEntity *> entityCollection;
    std::vector<std::pair<OIS::KeyCode, unsigned int>> keys;

    int				remove_key(OIS::KeyCode const&);
    CEGUI::MouseButton		convertButton(OIS::MouseButtonID const &buttonID);
    bool			push_key(OIS::KeyCode const&, unsigned int);
  };
}
