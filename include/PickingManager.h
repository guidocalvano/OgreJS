#ifndef PICKING_MANAGER_H
#define PICKING_MANAGER_H

#include <Ogre.h>



class PickingManager
	{
	public:
	
	
	 Ogre:: RaySceneQuery*	m_pray_scene_query ;
	 PickingManager() ;
		
	 Ogre::Entity* RaycastFromPoint( Ogre::Ray ray,
	                                 Ogre::Vector3 &result 		) ;
	
	
	 void GetMeshInformation(	Ogre::Entity *entity,
								size_t &vertex_count,
								Ogre::Vector3* &vertices,
								size_t &index_count,
								Ogre::uint32* &indices,
								const Ogre::Vector3 position,
								const Ogre::Quaternion orient,
								const Ogre::Vector3 scale) ;
	} ;
	
#endif