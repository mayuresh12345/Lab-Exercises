echo "Begin Program"
echo "Enter a, b, c for ax^2+bx+c"
read a b c
#echo $a $b $c
d=`expr $b \* $b \- 4 \* $a \* $c`
echo d = $d
if [ $d -gt  0 ]
then
f=0
d_sqrt=$(echo "sqrt ( $d )" | bc -l)
sqr=$d_sqrt
elif [ $d -eq 0 ]
then
f=1
else
f=2
fi
echo f=$f

case $f in
  "1")
	echo "roots are 0"
	root="(-$b)/(2*$a)"
	echo $root
	 ;;
  "2")
	echo "roots are imaginary"
	 ;;
  "0")
	root1="(-$b+$sqr)/(2*$a)"
	 echo $root1 | bc -l
	root2="(-$b-$sqr)/(2*$a)"
	echo $root2 | bc -l
	 ;;
   *)
	echo "illegal choice"
         ;;	
 esac

