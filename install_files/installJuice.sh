
if[ ! -f ./libv8-juice-20101126 ]
then
# DOWNLOAD JUICE

	wget http://v8-juice.googlecode.com/files/libv8-juice-20101126.tar.bz2
	bunzip2 libv8-juice-20101126.tar.bz2
	tar -xvf libv8-juice-20101126.tar 
	rm libv8-juice-20101126.tar

 
	cd lib
# if [ &(uname) == 'Darwin' ] && [ $(uname -p) == i386 ]
# then
	cp ./SConstruct ../OgreJS/install_files/juice/SConstruct.backup
	cp ../OgreJS/install_files/juice/SConstruct.patch ./SConstruct
# fi

	scons

	cd ..
fi