
if [ ! -d ./node ]
then
	echo INSTALLING NODE
	wait
	git clone https://github.com/guidocalvano/node.git node
	wait
	cd node
	wait
	git checkout lib
	wait
## if architecture is i386, compile as i386
# if [ [ &(uname) == 'Darwin' ] && [$(uname -p) == i386 ]
# then
# ./configure --dest-cpu=ia32
# else
	./configure
	wait
# fi
	make staticlib
	wait
	cd ..
else 
	echo NODE ALREADY INSTALLED
	
fi