ASM		= nasm
DASM		= ../../dst/dnasm
DASM		= objdump
#CC		= ../../dst/dcc
LD		= ld
#ASMFLAGS	= -f elf
ASMFLAGS	= -f elf -g -F stabs
CFLAGS		= 
#CFLAGS		= -I ../../include/ -c -fno-builtin -fno-stack-protector -w
#CFLAGS		= -I ../../include/ -c -fno-builtin -fno-stack-protector -Wall
#LDFLAGS		= -Ttext 0x8048000
LDFLAGS		= -Ttext 0x8048000 -g
DASMFLAGS	= -D

LIB		=  ../../dst/dnasm.a

#A_OBJS		=  test.asm

B_OBJS		=  test

O_OBJS		=  start.o

E_OBJS		=  test_mcode.o			

# All Phony Targets
.PHONY : everything final clean realclean disasm all install

# Default starting position
everything : $(E_OBJS) $(O_OBJS) $(B_OBJS)


install : all clean
	
all : realclean everything

final : all clean

clean :
	rm -f $(O_OBJS) 

realclean :
	rm -f $(O_OBJS) $(B_OBJS)

test : test.o start.o $(LIB) 
	$(LD) $(LDFLAGS) -Map test.map -o $@ $?

start.o : start.asm
	$(ASM) $(ASMFLAGS) -o $@ $<

#test.asm: test1.c
#	$(CC) $(CFLAGS) -o $@ $<

test.o : test.asm
	$(ASM) $(ASMFLAGS) -o $@ $<



