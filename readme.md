**Do you want to Help out?** go here-> https://github.com/guidocalvano/OgreJS/wiki/Help-out

## Important!

This is still a work in progress:

 - Documentation on the wiki is totally outdated, will work on that in the near future.

 - Vectors are almost implemented, but not entirely. The api is unlikely to change though.

 - A lot of functions have not been added yet.



## setting up environment on a Mac

This has only been tested hastily!

To set up your own environment automatically do:

git clone git@github.com:guidocalvano/OgreJS.git

cd OgreJS

. ./install.sh

This will download all required dependencies into the OgreJS root directory (with the exception of wget and Cg.framework which will be installed on using their installers):

1. wget
2. node (but a special adapted version)
3. OgreSDK version 1.7.3
4. Ogre Dependencies
    - this included Cg.framework
5. boost (because it is included in the OgreSDK)
6. my-gui

## building

to build everything: 

make -f makeOgreJS


to build OgreJS without my-gui

make -f makeOgreJSWithoutMyGui

## Run

OgreJS

./build/ogrenode ./example.js


OgreJSWithoutMyGui

./build/ogrenode_no_mygui ./example.js




