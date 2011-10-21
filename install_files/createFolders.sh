
ln -s ./OgreSDK1.7.3/lib ./Plugins

mkdir Contents

cd Contents
ln -s ../Plugins Plugins
ln -s ../Resources Resources
cd ..

cd build
ln -s ../Contents ./Contents
cd..

mkdir build/objects