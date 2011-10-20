

if[ ! -f ./OgreSDK/Dependencies ] ;
then

	# DOWNLOAD OGRE DEPENDENCIES

	wget http://downloads.sourceforge.net/project/ogre/ogre-dependencies-mac/1.7/OgreDependencies_OSX_20110208.zip?r=http%3A%2F%2Fsourceforge.net%2Fprojects%2Fogre%2Ffiles%2Fogre-dependencies-mac%2F1.7%2F&ts=1310483790&use_mirror=garr
	unzip OgreDependencies_OSX_20110208.zip
	mv Dependencies/ OgreSDK
	rm OgreDependencies_OSX_20110208.zip

fi