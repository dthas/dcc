make all

dst/dnasm src/temp/test.asm  1>src/temp/error.txt 2>&1

#cd src/temp
#make all

#ld -Ttext 0x8048000 -g start.o test_mcode.o ../../dst/dnasm.a -o test
