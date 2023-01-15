
pushd .\out\build\x64-debug 
start SnakeNet.exe 7000 2 local 127.0.0.1:7001 
start SnakeNet.exe 7001 2 127.0.0.1:7000 local
popd