echo The program $0 is now running
echo Enter file1
read f1
echo Enter file2
read f2
sort $f1 $f2 |uniq > final.txt
cat final.txt
