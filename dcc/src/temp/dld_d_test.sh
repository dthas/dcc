#gcc -shared dst/printf.o dst/write.o dst/lib.o dst/liba.o -o dst/lib_d.so
#gcc -I src/include/ -shared src/lib/ex/printf.c src/lib/ex/write.asm src/lib/lib.c src/lib/liba.asm -o dst/lib_d.so
ld -shared ../../dst/printf.o ../../dst/write.o ../../dst/lib.o ../../dst/liba.o -o lib_d.so

gcc test1.c ./lib_d.so -o test_d


