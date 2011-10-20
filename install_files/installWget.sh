
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
	rm wget-1.9.tar.gz
	cd ..
	
else
	echo WGET ALREADY INSTALLED
fi