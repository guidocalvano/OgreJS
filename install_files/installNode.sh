git clone https://github.com/guidocalvano/node.git node
cd node
git checkout lib
## if architecture is i386, compile as i386
# if [ [ &(uname) == 'Darwin' ] && [$(uname -p) == i386 ]
# then
# ./configure --dest-cpu=ia32
# else
./configure
# fi
make staticlib
cd ..