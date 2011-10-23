
if [ ! -d ./my-gui ]
then
	svn co https://my-gui.svn.sourceforge.net/svnroot/my-gui/trunk my-gui
		
	cd my-gui
	
	svn up -r 4305
	
	cp ../forOtherDependencies/mac/my-gui/Platforms/Ogre/OgrePlatform/CMakeLists.txt Platforms/Ogre/OgrePlatform/CMakeLists.txt
	
	cmake -D MYGUI_STATIC=ON -D MYGUI_BUILD_DEMOS=OFF -D MYGUI_BUILD_PLUGINS=OFF -D MYGUI_BUILD_DOCS=OFF  -D FREETYPE_INCLUDE_DIR=../forOtherDependencies/mac/my-gui/usr/local/include/freetype2 -D FREETYPE_FT2BUILD_INCLUDE_DIR=../forOtherDependencies/mac/my-gui/usr/local/include -D FREETYPE_LIBRARY_REL=../forOtherDependencies/mac/my-gui/opt/local/lib/libfreetype.dylib -D OIS_INCLUDE_DIR=../OgreSDK1.7.3/OIS -D OIS_LIBRARY_REL=./OgreSDK1.7.3/lib/release/libOIS.a -D OGRE_LIBRARY=../OgreSDK1.7.3/lib/release/OGRE.framework -G Xcode .
	
	
	xcodebuild -project MYGUI.xcodeproj/ -target MyGUIEngine
	xcodebuild -project MYGUI.xcodeproj/ -target MyGUI.OgrePlatform
 
	cd ..
	
	# insert correct cmake vars:
	
	# set correct Ogre.framework for UNGROUPED ENTRIES: OGRE_LIBRARY = /Volumes/Macintosh2/messingAboutWithInstallScript/OgreJS/OgreSDK1.7.3/lib/release/Ogre.framework
	
	# set correct libois.a = /Volumes/Macintosh2/messingAboutWithInstallScript/OgreJS/OgreSDK1.7.3/lib/release/libOIS.a
	
	# use correct freetype include FREETYPE_INCLUDE_DIR = /Volumes/Macintosh2/messingAboutWithInstallScript/OgreJS/OgreSDK1.7.3/Dependencies/include/freetype
	
	# use correct ft2build.h dir for FREETYPE_FT2BUILD_INCLUDE_DIR = /Volumes/Macintosh2/messingAboutWithInstallScript/OgreJS/OgreSDK1.7.3/Dependencies/include/

	# use correct libfreetype.a dir for FREETYPE_LIBRARY_REL = /Volumes/Macintosh2/messingAboutWithInstallScript/OgreJS/OgreSDK1.7.3/Dependencies/lib/Release/libfreetype.a

	# MYGUI: MYGUI_DEMOS no MYGUI_DOCS no
	
	
	# generate xcode file
	
	# make xcode compile
	# xcodebuild -project myProject.xcodeproj -alltargets
fi