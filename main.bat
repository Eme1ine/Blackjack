rem a changer par le path local du compilateur
cmake -S . -B build -G "MinGW Makefiles" ^
  -DCMAKE_PREFIX_PATH="C:\Qt\6.9.3\mingw_64"
cmake --build build --verbose -j1 --target MyQtApp
.\build\MyQtApp.exe