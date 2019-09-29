echo "Program starts"
echo "Enter the number"
read num
x=1
echo "The odd numbers till $num are: "
while test $x -le $num
do
ans=$((x % 2 ))
if test $ans -eq 1
then
echo $x
fi
x=$((x+1))
done
