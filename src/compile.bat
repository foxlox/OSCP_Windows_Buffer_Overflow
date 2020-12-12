#by foxlox

set path=%path%;c:\mingw\bin
gcc -c funcs_access.c
gcc.exe -shared -o funcs_access.dll  -Wl,--out-implib=libext.a -Wl,--image-base=0x62500000 funcs_access.o
gcc access.c -o access.exe -lws2_32 ./libext.a
