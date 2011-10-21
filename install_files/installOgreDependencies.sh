

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
	
	wait
	curl -O -L http://developer.download.nvidia.com/cg/Cg_3.0/Cg-3.0_February2011.dmg && hdiutil attach Cg-3.0_February2011.dmg
	wait
	open /Volumes/Cg-3.0.0016/Cg-3.0.0016.app/
	wait
	echo AFTER INSTALLER COMPLETES PRESS ENTER
	read ignoreThis
	hdiutil detach /Volumes/Cg-3.0.0016
	wait
	rm Cg-3.0_February2011.dmg
	wait
	echo COPYING
	cp -r /Library/Frameworks/Cg.framework ./OgreSDK1.7.3/Dependencies
else
	echo OGRE DEPENDENCIES ALREADY INSTALLED
fi