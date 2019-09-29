echo "Begin Program"
echo "Enter the number n"
read n
f=1
i=1
while test $i -le $n
do
f=$((i*f))
i=$((i+1))
done
echo "Factorial = $f"
