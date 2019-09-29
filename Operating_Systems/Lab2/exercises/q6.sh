echo "The Program $0 is runnning"
echo "The first parameter is $1"
echo "The second parameter is $2"
fmat=*.$1
echo $fmat
cp $fmat $2 && echo "Copying complete"
