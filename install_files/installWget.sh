
if [ ! -f /usr/local/bin/wget ]
then
	ftp ftp://ftp.gnu.org/gnu/wget/wget-1.9.tar.gz
	wait
	tar -xvzf wget-1.9.tar.gz
	wait
	cd wget-1.9
	wait
	./configure
	wait
	make
	wait
	sudo make install
	wait
	cd ..
	rm wget-1.9.tar.gz
	
else
	echo WGET ALREADY INSTALLED
fi