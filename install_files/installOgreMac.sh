
if[ ! -f ./OgreSDK ]
then
	if[ $(uname) == 'Darwin' ]
	then
	 	wget wget http://downloads.sourceforge.net/project/ogre/ogre/1.7/OgreSDK_v1-7-3.dmg?r=&ts=1310482623&use_mirror=ignum
		hdiutil attach OgreSDK_v1-7-3.dmg

		cp -R /Volumes/OgreSDK/OgreSDK/ ./OgreSDK

		hdiutil detach /Volumes/OgreSDK\ Installer/;
		rm OgreSDK_v1-7-3.dmg
	else
		# Insert Linux install here
	fi
fi


