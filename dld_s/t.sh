make all

cd dst
ar -x dld.a 

cd ..
dst/dld -Ttext 0x8048000 -g src/temp/test_mcode.o src/temp/start.o dst/printf.o dst/write.o dst/lib.o dst/liba.o 1>src/temp/error.txt 2>&1
#dst/dld -Ttext 0x8048000 -g src/temp/test.o src/temp/start.o dst/printf.o dst/write.o dst/lib.o dst/liba.o 1>src/temp/error.txt 2>&1
