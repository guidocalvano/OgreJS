

if [ ! -d ./boost_1_46_1 ] 
then
	if [ -d OgreSDK1.7.3/boost_1_46_1/ ]
	then
		cp -r OgreSDK1.7.3/boost_1_46_1/ ./boost_1_46_1
	else
		wget http://downloads.sourceforge.net/project/boost/boost/1.46.1/boost_1_46_1.tar.bz2?r=http%3A%2F%2Fsourceforge.net%2Fprojects%2Fboost%2Ffiles%2Fboost%2F1.46.1%2F&ts=1310656609&use_mirror=dfn
		wait
		bunzip2 boost_1_46_1.tar.bz2
		wait
		tar -xvf boost_1_46_1.tar 
		wait
		rm boost_1_46_1.tar
	fi
else
	echo BOOST ALREADY INSTALLED
	
fi