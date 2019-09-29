echo "Program starts"
x=10
while test $x -ge 0
do
echo $x
x=`expr $x - 1`
x=$((x-1))
done
