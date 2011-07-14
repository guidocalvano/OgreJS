git clone https://github.com/joyent/node.git node0.4.8
cd node
git checkout v0.4.8
# if architecture is i386, compile as i386
if [ [ &(uname) == 'Darwin' ] && [$(uname -p) == i386 ]
then
./configure --dest-cpu=ia32
else
./configure
fi
make staticlib
cd ..