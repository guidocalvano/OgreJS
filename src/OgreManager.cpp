
#include <OgreManager.h>

#include <OGRE/OgreLight.h>
#include <OGRE/OgreWindowEventUtilities.h>

using namespace Ogre ;


template<> OgreManager* Ogre::Singleton<OgreManager>::ms_Singleton = 0 ;


OgreManager:: OgreManager()
	{
	 m_pRoot			= 0 ;
	 m_pSceneMgr			= 0 ;
	 m_pRenderWnd			= 0 ;
	 m_pCamera			= 0 ;
	 m_pViewport			= 0 ;

	 m_pInputMgr			= 0 ;
	 m_pKeyboard			= 0 ;
 	 m_pMouse			= 0 ;

	 m_pLog				= 0 ;
	 m_pTimer			= 0 ;
	}


OgreManager:: ~OgreManager()
	{
	 if(m_pInputMgr)
		{
		 OIS::InputManager::destroyInputSystem(m_pInputMgr);
		}

	 OGRE_DELETE m_pRoot;
	}



bool OgreManager:: initDefault()
	{
	 printf( "ogreman init -> \n" ) ;
 	 new Ogre::LogManager() ;
	 m_pLog = Ogre::LogManager::getSingleton().createLog("OgreLogfile.log", true, true, false);
	 m_pLog-> setDebugOutputEnabled(true);

	 printf( "root \n" ) ;

 	 m_pRoot = new Ogre:: Root() ;

	 m_pRoot-> loadPlugin( "RenderSystem_GL.dylib" ) ;
	 printf( "plugin \n" ) ;

 	 if( ! m_pRoot-> showConfigDialog() ) return false ;

	 m_pRenderWnd = m_pRoot->initialise( true ) ;


	 m_pSceneMgr = m_pRoot->createSceneManager(ST_GENERIC, "SceneManager");
	 m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.7, 0.7, 0.7));
	
	 m_pCamera = m_pSceneMgr->createCamera("Camera");
	 m_pCamera->setPosition(Vector3(0, 60, 60));
	 m_pCamera->lookAt(Vector3(0,0,0));
	 m_pCamera->setNearClipDistance(1);

	 m_pViewport = m_pRenderWnd->addViewport(m_pCamera);
	 m_pViewport->setBackgroundColour(ColourValue(0.8, 0.7, 0.6, 1.0));

	 m_pCamera->setAspectRatio(Real(m_pViewport->getActualWidth()) / Real(m_pViewport->getActualHeight()));
	
	 m_pViewport->setCamera(m_pCamera);

	 unsigned long hWnd = 0;
    	 OIS::ParamList paramList;
	 m_pRenderWnd->getCustomAttribute("WINDOW", &hWnd);

	 paramList.insert(OIS::ParamList::value_type("WINDOW", Ogre::StringConverter::toString(hWnd)));

	 m_pInputMgr = OIS::InputManager::createInputSystem(paramList);

    	 m_pKeyboard = static_cast<OIS::Keyboard*>(m_pInputMgr->createInputObject(OIS::OISKeyboard, true));
	 m_pMouse = static_cast<OIS::Mouse*>(m_pInputMgr->createInputObject(OIS::OISMouse, true));

	 m_pMouse->getMouseState().height = m_pRenderWnd->getHeight();
	 m_pMouse->getMouseState().width	 = m_pRenderWnd->getWidth();

	 // m_pKeyboard->	setEventCallback( this ) ;
	 // m_pMouse->	setEventCallback( this ) ;

	 #if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
	    	m_ResourcePath = "./Contents/Resources/";
	 #endif


	Ogre::String secName, typeName, archName;
	Ogre::ConfigFile cf;
    	cf.load(m_ResourcePath + "resources.cfg");

	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
    	while (seci.hasMoreElements())
    		{
        	 secName = seci.peekNextKey();
		 Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
	         Ogre::ConfigFile::SettingsMultiMap::iterator i;
	         for (i = settings->begin(); i != settings->end(); ++i)
	        	{
		         typeName = i->first;
    		         archName = i->second;
   	         	 #if OGRE_PLATFORM == OGRE_PLATFORM_APPLE || OGRE_PLATFORM == OGRE_PLATFORM_IPHONE
            		 // OS X does not set the working directory relative to the app,
            		 // In order to make things portable on OS X we need to provide
            		 // the loading with it's own bundle path location
            		 if (!Ogre::StringUtil::startsWith(archName, "/", false)) // only adjust relative dirs
               			 archName = Ogre::String("./" + archName);
		         #endif
	      	    	 Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
        		}
    		}

 	 Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	 Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	 m_pTimer = OGRE_NEW Ogre::Timer();
	 m_pTimer->reset();
	


	 initPlatform() ;

	 return true ;
	}


void OgreManager:: setupDemoScene()
	{

	 m_pSceneMgr->setSkyBox(true, "Examples/SpaceSkyBox");

 	 m_pSceneMgr->createLight("Light")->setPosition(75,75,75);

	// m_pDemoEntity = m_pSceneMgr->createEntity("Cube", "ogrehead.mesh");

	// m_pDemoNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("DemoNode");
	// m_pDemoNode->attachObject(m_pDemoEntity);
	}


bool OgreManager:: keyPressed( const OIS::KeyEvent &keyEventRef )
	{
	 return true ;
	}


bool OgreManager:: keyReleased(const OIS::KeyEvent &keyEventRef )
	{
 	 return true ;
	}




bool OgreManager:: mouseMoved(const OIS::MouseEvent &evt )
	{
	 return true ;
	}


bool OgreManager::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
	{
 	 return true ;
	}


bool OgreManager::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
	{
	 return true ;
	}

