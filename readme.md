## setting up environment on a Mac

This has barely been tested, and only on my machine. 

To set up your own environment automatically do:

git clone git@github.com:guidocalvano/OgreJS.git

cd OgreJS

. ./install.sh

This will download all required dependencies into the OgreJS root directory (with the exception of wget and Cg.framework which will be installed using their installers):

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


## Run

OgreJS

cd example

../build/ogrenode ./example.js



