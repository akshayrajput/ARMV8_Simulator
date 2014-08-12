echo 'Building elfio'
g++ -g -o elfio  elfio_bin.cpp
echo 'Elfio successfully built'

echo 'Building simulo'
make
echo 'Done building simulo'

