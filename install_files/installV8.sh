if [ ! -d ./v8 ]
then
	if [ -d ./node/deps/v8 ]
	then
		cp -r ./node/deps/v8 ./v8
	else
		echo CANNOT FIND V8 IN THE NODE DIR. PLEASE DOWN LOAD V8
	fi
fi