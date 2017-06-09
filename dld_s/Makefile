#===========================================================================
# Makefile
#   Copyright (C) 2013 Free Software Foundation, Inc.
#   Originally by ZhaoFeng Liang <zhf.liang@outlook.com>
#
#This file is part of DTHAS_DLD.
#
#DTHAS_DLD is free software; you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation; either version 2 of the License, or 
#(at your option) any later version.
#
#DTHAS_DLD is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.
#
#You should have received a copy of the GNU General Public License
#along with DTHAS; If not, see <http://www.gnu.org/licenses/>.  
#===========================================================================

# Programs, flags, etc.
ASM		= nasm
CC		= gcc
LD		= ld

ASMLIBFLAGS	= -I src/include/ -I src/lib/ -f elf

CFLAGS		= -I src/include/ -c -fno-builtin -w -fno-stack-protector
LDFLAGS		= -Map dld.map $(LOBJS_UBUNTU)
ARFLAGS		= rcs

# This Program
DLD		= dst/dld
LIB		= dst/dld.a

OBJS		= $(OBJS_MAIN) 


OBJS_MAIN	= src/main/main.o src/main/dld_lib.o src/main/main_lib.o\
			src/main/rel_process.o src/main/main_lib_1.o


LOBJS_UBUNTU	= /usr/lib/i386-linux-gnu/crt1.o\
			/usr/lib/i386-linux-gnu/crti.o\
			/usr/lib/gcc/i686-linux-gnu/4.6.3/crtbegin.o\
			-lc /usr/lib/gcc/i686-linux-gnu/4.6.3/crtend.o\
			/usr/lib/i386-linux-gnu/crtn.o\
			-dynamic-linker /lib/ld-linux.so.2 
	
LOBJS		= src/lib/lib.o src/lib/liba.o
			
EX_LOBJS	= src/lib/ex/printf.o src/lib/ex/write.o src/lib/ex/print.o

ELF_LOBJS	= src/lib/elf/elf.o src/lib/elf/elf_lib.o

all : realclean everything clean

realclean :
	rm -f  $(OBJS) $(LOBJS) $(LIB) $(EX_LOBJS) $(ELF_LOBJS)

clean :
	rm -f $(OBJS) $(LOBJS) $(EX_LOBJS) $(ELF_LOBJS)

everything : $(DLD) $(OBJS) $(LOBJS) $(EX_LOBJS) $(ELF_LOBJS)

$(DLD) : $(OBJS) $(LIB) 
	$(LD) $(LDFLAGS) -o $(DLD) $^

$(LIB) : $(LOBJS)  $(EX_LOBJS) $(ELF_LOBJS)
	$(AR) $(ARFLAGS) $@ $^


src/lib/lib.o: src/lib/lib.c
	$(CC) $(CFLAGS) -o $@ $<

src/lib/liba.o : src/lib/liba.asm
	$(ASM) $(ASMLIBFLAGS) -o $@ $<

src/main/main.o: src/main/main.c
	$(CC) $(CFLAGS) -o $@ $<

src/main/dld_lib.o: src/main/dld_lib.c
	$(CC) $(CFLAGS) -o $@ $<

src/main/main_lib.o: src/main/main_lib.c
	$(CC) $(CFLAGS) -o $@ $<

src/main/rel_process.o: src/main/rel_process.c
	$(CC) $(CFLAGS) -o $@ $<

src/main/main_lib_1.o: src/main/main_lib_1.c
	$(CC) $(CFLAGS) -o $@ $<

src/lib/ex/printf.o: src/lib/ex/printf.c
	$(CC) $(CFLAGS) -o $@ $<

src/lib/ex/print.o : src/lib/ex/print.asm
	$(ASM) $(ASMLIBFLAGS) -o $@ $<

src/lib/ex/write.o : src/lib/ex/write.asm
	$(ASM) $(ASMLIBFLAGS) -o $@ $<

src/lib/elf/elf.o: src/lib/elf/elf.c
	$(CC) $(CFLAGS) -o $@ $<

src/lib/elf/elf_lib.o: src/lib/elf/elf_lib.c
	$(CC) $(CFLAGS) -o $@ $<

