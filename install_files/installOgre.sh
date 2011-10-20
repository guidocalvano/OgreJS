
if [ ! -d ./OgreSDK1.7.3 ]
then
	if [ $(uname) == 'Darwin' ] 
	then
	 	wget wget http://downloads.sourceforge.net/project/ogre/ogre/1.7/OgreSDK_v1-7-3.dmg?r=&ts=1310482623&use_mirror=ignum 
	 	wait
	  	hdiutil attach OgreSDK_v1-7-3.dmg
		wait
		cp -R /Volumes/OgreSDK/OgreSDK/ ./OgreSDK1.7.3
		wait
		hdiutil detach /Volumes/OgreSDK 
		wait
		rm OgreSDK_v1-7-3.dmg
#	else
		# Insert Linux install here
		# sudo apt-get install libogre-dev # is this the correct line?
	fi
else
	echo OGRE ALREADY INSTALLED
fi


