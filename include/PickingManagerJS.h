#ifndef PICKING_MANAGER_JS_H
#define PICKING_MANAGER_JS_H

#include <PickingManager.h>
#include <hash_map.h>
#include <OGRE/Ogre.h>
#include <EntityJS.h>
using namespace std ;

class PickingManagerJS
	{
	public:
	 hash_map<long, long > pEntityToPEntityJS ;


	 EntityJS* pick( Ogre::Ray ray,
					 Ogre::Vector3 &result 		) ;



	 void add( Ogre::Entity* entity,  EntityJS* entityJS ) ;

	 void remove( Ogre::Entity* entity ) ;
	} ;



#endif