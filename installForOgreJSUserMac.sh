

echo "This will install all dependencies in the PARENT folder, next to where you probably have your other project dependencies. Is this what you want?"
while true
do
echo -n "Please confirm (y or n) :"
read CONFIRM
case $CONFIRM in
y|Y|YES|yes|Yes) break ;;
n|N|no|NO|No)
echo Aborting - you entered $CONFIRM
exit
;;
*) echo Please enter only y or n
esac
done
echo You entered $CONFIRM. Continuing ...


cd ..
. ./OgreJS/install_files/installDependencies.sh

cd OgreJS
scons
cd ..