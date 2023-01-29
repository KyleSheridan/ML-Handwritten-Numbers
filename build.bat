mkdir Build
cd Build
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build . -j --config Debug
pause