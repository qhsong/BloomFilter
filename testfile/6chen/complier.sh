gcc *.c -o strfind
rm computer.time
echo "First run"
./strfind /home/bupt/strpool.dat /home/bupt/checkedemail.dat result.dat >>computer.time
echo "Second run"
./strfind /home/bupt/strpool.dat /home/bupt/checkedemail.dat result.dat >>computer.time
echo "Third run"
./strfind /home/bupt/strpool.dat /home/bupt/checkedemail.dat result.dat >>computer.time
sum=`awk '{sum+=$1}END{print sum}' computer.time`
echo `echo "scale=4;$sum/3"|bc` >>computer.time
