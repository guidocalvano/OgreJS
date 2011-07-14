git clone https://github.com/joyent/node.git node0.4.8
cd node
git checkout v0.4.8
# if architecture is i386, compile as i386
# if [ $(uname -p) == i386 ]
# then
./configure --dest-cpu=ia32
# else
# ./configure
# fi
make staticlib
cd ..

# DOWNLOAD OGRE

wget wget http://downloads.sourceforge.net/project/ogre/ogre/1.7/OgreSDK_v1-7-3.dmg?r=&ts=1310482623&use_mirror=ignum
hdiutil attach OgreSDK_v1-7-3.dmg

cp -R /Volumes/OgreSDK/OgreSDK/ ./OgreSDK

hdiutil detach /Volumes/OgreSDK\ Installer/;
rm OgreSDK_v1-7-3.dmg

# DOWNLOAD OGRE DEPENDENCIES

wget http://downloads.sourceforge.net/project/ogre/ogre-dependencies-mac/1.7/OgreDependencies_OSX_20110208.zip?r=http%3A%2F%2Fsourceforge.net%2Fprojects%2Fogre%2Ffiles%2Fogre-dependencies-mac%2F1.7%2F&ts=1310483790&use_mirror=garr
mv Dependencies/ OgreSDK

# DOWNLOAD JUICE

wget http://v8-juice.googlecode.com/files/libv8-juice-20101126.tar.bz2
bunzip2 libv8-juice-20101126.tar.bz2
tar -xvf libv8-juice-20101126.tar 
rm libv8-juice-20101126.tar

 
cd lib
# if [ $(uname -p) == i386 ]
# then
cp ./SConstruct ../OgreJS/install_files/juice/SConstruct.backup
cp ../OgreJS/install_files/juice/SConstruct.patch ./SConstruct
# fi

scons

cd ..

# MOVE BOOST DEPENDENCIES INTO PROJECT DIR

mv OgreSDK/boost_1_46_1/ ./boost_1_46_1