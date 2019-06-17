#!bin/bash

basedir='ROMs/testing'

cd $basedir
roms=(*)
cd ../../

for rom in "${roms[@]}"
do
    echo "Launching test $rom"
    ./GBEmu "$basedir/$rom"
done

echo "All tests passed!"


