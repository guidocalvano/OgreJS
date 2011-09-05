
#ifndef OGRE_FRAMEWORK_H
#define OGRE_FRAMEWORK_H

//|||||||||||||||||||||||||||||||||||||||||||||||

#include <OGRE/OgreCamera.h>
#include <OGRE/OgreEntity.h>
#include <OGRE/OgreLogManager.h>
#include <OGRE/OgreOverlay.h>
#include <OGRE/OgreOverlayElement.h>
#include <OGRE/OgreOverlayManager.h>
#include <OGRE/OgreRoot.h>
#include <OGRE/OgreViewport.h>
#include <OGRE/OgreSceneManager.h>
#include <OGRE/OgreRenderWindow.h>
#include <OGRE/OgreConfigFile.h>

#include <OIS/OISEvents.h>
#include <OIS/OISInputManager.h>
#include <OIS/OISKeyboard.h>
#include <OIS/OISMouse.h>

#include <PickingManager.h>


class OgreManager : public Ogre::Singleton<OgreManager>, OIS::KeyListener, OIS::MouseListener
	{
	public:

	 OgreManager() ;
	 ~OgreManager() ;

	 bool initDefault() ;
	 
	 void setupDemoScene() ;

	 bool keyPressed(const OIS::KeyEvent &keyEventRef);
	 bool keyReleased(const OIS::KeyEvent &keyEventRef);

	 bool mouseMoved(const OIS::MouseEvent &evt);
	 bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id); 
	 bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);


	 Ogre::Root*				m_pRoot		;
	 Ogre::SceneManager*			m_pSceneMgr	;
	 Ogre::RenderWindow*			m_pRenderWnd	;
	 Ogre::Camera*				m_pCamera	;
	 Ogre::Viewport*			m_pViewport	;

	 OIS::InputManager*			m_pInputMgr	;
	 OIS::Keyboard*				m_pKeyboard	;
	 OIS::Mouse*				m_pMouse	;


	 Ogre::Log*				m_pLog		;
	 Ogre::Timer*				m_pTimer	;

	 Ogre:: SceneNode*			m_pDemoNode	;
	 Ogre:: Entity*				m_pDemoEntity 	;

  	 Ogre::String                 m_ResourcePath	;

	 PickingManager* 		m_pPickingManager ;

	 void initPlatform() ; // compile and link the platform specific cpp file to init the right platform

	 void pumpGUIEventQueue() ;
	} ;

#endif // OGRE_FRAMEWORK_H