
ln -s ./OgreSDK1.7.3/lib /Plugins

mkdir Resources

cd Contents
ln -s ../Plugins Plugins
ln -s ../Resources Resources
cd ..

cp -r ./OgreSDK1.7.3