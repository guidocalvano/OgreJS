
#include <PickingManagerJS.h>

EntityJS* PickingManagerJS:: pick( Ogre::Ray ray,
	      Ogre::Vector3 &result 		) 
		{
		 Ogre::Entity* entity = OgreManager:: getSingletonPtr()-> m_pPickingManager-> RaycastFromPoint( ray, result ) ;

		 if( entity == NULL ) return NULL ;

		 return (EntityJS*) pEntityToPEntityJS[ (long) entity ] ;
		}
		
		
void PickingManagerJS:: add(  Ogre::Entity* entity, EntityJS* entityJS ) { pEntityToPEntityJS[ (long) entity ] = (long) entityJS ;}

void PickingManagerJS:: remove(  Ogre::Entity* entity )   { /* pEntityToPEntityJS.erase( entity ) ; */ }