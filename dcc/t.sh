make all

dst/dcc src/temp/test1.c  1>src/temp/error.txt 2>&1

../dnasm/dst/dnasm src/temp/test.asm  1>src/temp/error.txt 2>&1

../dnasm/dst/dnasm src/temp/start.asm  1>src/temp/error1.txt 2>&1

cd dst
ar -x dcc.a

cd ..
#../dld_s/dst/dld -Ttext 0x8048000 -g src/temp/test.o src/temp/start.o dst/printf.o dst/write.o dst/lib.o dst/liba.o 1>src/temp/error.txt 2>&1
../dld_s/dst/dld -Ttext 0x8048000 -g src/temp/start.o src/temp/test.o dst/printf.o dst/write.o dst/lib.o dst/liba.o 1>src/temp/error.txt 2>&1

