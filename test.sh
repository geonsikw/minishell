echo hello
echo $USER
echo "HELLO" > new1
cat new1
echo "WORLD" >> new1
cat new1
ls > new2
cat new2
rm new1 new2
env
cd ..
pwd
cd mini
pwd
echo | cd .. | pwd
who
echo === who ===
who | grep t
echo "=== who | grep t ==="
who | grep t |  grep 008
echo "=== who | grep t | grep 008 ==="
