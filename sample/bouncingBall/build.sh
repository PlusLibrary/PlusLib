libPath="../../"
libName="pluslib"

g++ ./*.cpp $(find ../../pluslib -type f -iregex ".*\.cpp") -I $libPath -I /usr/include/freetype2 -o bin -lglfw -lGL -lm -lfreetype