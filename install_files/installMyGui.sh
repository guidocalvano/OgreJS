
if [ ! -d ./my-gui ]
then
	svn co https://my-gui.svn.sourceforge.net/svnroot/my-gui/trunk my-gui
	
	svn up -r 4305
	
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