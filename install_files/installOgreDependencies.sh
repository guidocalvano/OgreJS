

if [ ! -d ./OgreSDK1.7.3/Dependencies ]
then

	# DOWNLOAD OGRE DEPENDENCIES

	wget http://downloads.sourceforge.net/project/ogre/ogre-dependencies-mac/1.7/OgreDependencies_OSX_20110208.zip?r=http%3A%2F%2Fsourceforge.net%2Fprojects%2Fogre%2Ffiles%2Fogre-dependencies-mac%2F1.7%2F&ts=1310483790&use_mirror=garr
	wait
	unzip OgreDependencies_OSX_20110208.zip
	wait
	mv Dependencies/ OgreSDK1.7.3
	wait
	rm OgreDependencies_OSX_20110208.zip
else
	echo OGRE DEPENDENCIES ALREADY INSTALLED
fi