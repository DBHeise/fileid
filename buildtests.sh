cd ./test

g++ -std=c++14 -O3 common_test.cpp -o ../bin/common_test
g++ -std=c++14 -O3 oless/olecommon_test.cpp -o ../bin/olecommon_test
g++ -std=c++14 -O3 oless/structures/LongRGB_test.cpp -o ../bin/LongRGB_test

cd ..
