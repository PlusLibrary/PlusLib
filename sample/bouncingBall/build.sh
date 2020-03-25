libPath="../../"
libName="pluslib"
libBuildUtil="${libPath}${libName}/util/*.cpp"
libBuildOpengl="${libPath}${libName}/opengl/*.cpp"

g++ ./*.cpp $libBuildUtil $libBuildOpengl -I $libPath -o bin -lglfw -lGL -lm