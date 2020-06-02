
cd ./test

for file in $(find -name "*.cpp"); do
        echo "$file"
        filename=$(basename "$file")
        filename="${filename%.*}"
        g++ -std=c++17 -O3 "$file" -o ../bin/$filename
done

cd ..
