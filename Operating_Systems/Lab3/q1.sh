echo "Program starts"
echo "Enter a number"
read num
ans=$((num % 2 ))
#ans=`expr $num \% 2`
echo $ans
if [ $ans -eq 0 ]
then
echo "Even"
else
echo "Odd"
fi
