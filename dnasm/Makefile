#===========================================================================
# Makefile
#   Copyright (C) 2013 Free Software Foundation, Inc.
#   Originally by ZhaoFeng Liang <zhf.liang@outlook.com>
#
#This file is part of DTAHS_DNASM.
#
#DTAHS_DNASM is free software; you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation; either version 2 of the License, or 
#(at your option) any later version.
#
#DTAHS_DNASM is distributed in the hope that it will be useful,
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
LDFLAGS		= -Map dnasm.map $(LOBJS_UBUNTU)
ARFLAGS		= rcs

# This Program
DNASM		= dst/dnasm
LIB		= dst/dnasm.a

OBJS		= $(OBJS_MAIN) $(OBJS_SYMTBL) $(OBJS_PRE)\
			$(OBJS_LEX) $(OBJS_PARSE) $(OBJS_SEMANTICS)\
			$(OBJS_FRAME) $(OBJS_IR)\
			$(OBJS_PASM) $(OBJS_INS)\
			$(OBJS_MCODE) $(ELF_LOBJS)


OBJS_MAIN	= src/main/main.o
OBJS_SYMTBL	= src/front_end/symbol/symbol_main.o
OBJS_PRE	= src/pre/pre_main.o src/pre/lex/pre_lex_char_state_tab.o
OBJS_LEX	= src/front_end/lex/lex_main.o src/front_end/lex/lex_char_state_tab.o src/front_end/lex/lex_lib.o
OBJS_PARSE	= src/front_end/parse/parse_main.o src/front_end/parse/parse_production_tab.o\
			src/front_end/parse/parse_lib.o src/front_end/parse/parse_func.o

OBJS_SEMANTICS	= src/front_end/semantics/seman_lib.o src/front_end/semantics/seman_main.o\
			src/front_end/semantics/seman_type.o

OBJS_IR		= src/mid_end/ir/ir_list.o src/mid_end/ir/ir_list_lib.o

OBJS_PASM	= src/back_end/pasm/pasm_main.o src/back_end/pasm/pasm_lib.o src/back_end/pasm/pasm_lib_t.o

OBJS_FRAME	= src/mid_end/frame/frame_main.o src/mid_end/frame/var.o

OBJS_LABEL	= src/front_end/label/label_main.o	


OBJS_INS	= src/back_end/ins/i386/ins_main.o src/back_end/ins/i386/ins_lib.o src/back_end/ins/i386/ins_lib_t.o\
			src/back_end/ins/i386/ins_lib_1.o src/back_end/ins/i386/ins_update.o

OBJS_MCODE	= src/back_end/mcode/mcode_main.o src/back_end/mcode/mcode_file.o src/back_end/mcode/mcode_lib.o

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

everything : $(DNASM) $(OBJS) $(LOBJS) $(EX_LOBJS) $(ELF_LOBJS)



$(DNASM) : $(OBJS) $(LIB) 
	$(LD) $(LDFLAGS) -o $(DNASM) $^

$(LIB) : $(LOBJS)  $(EX_LOBJS)
	$(AR) $(ARFLAGS) $@ $^

src/lib/lib.o: src/lib/lib.c
	$(CC) $(CFLAGS) -o $@ $<

src/lib/liba.o : src/lib/liba.asm
	$(ASM) $(ASMLIBFLAGS) -o $@ $<

src/main/main.o: src/main/main.c
	$(CC) $(CFLAGS) -o $@ $<

src/front_end/symbol/symbol_main.o: src/front_end/symbol/symbol_main.c
	$(CC) $(CFLAGS) -o $@ $<

src/pre/pre_main.o: src/pre/pre_main.c
	$(CC) $(CFLAGS) -o $@ $<

src/pre/lex/pre_lex_char_state_tab.o: src/pre/lex/pre_lex_char_state_tab.c
	$(CC) $(CFLAGS) -o $@ $<

src/front_end/lex/lex_main.o: src/front_end/lex/lex_main.c
	$(CC) $(CFLAGS) -o $@ $<

src/front_end/lex/lex_char_state_tab.o: src/front_end/lex/lex_char_state_tab.c
	$(CC) $(CFLAGS) -o $@ $<

src/front_end/lex/lex_lib.o: src/front_end/lex/lex_lib.c
	$(CC) $(CFLAGS) -o $@ $<

src/front_end/parse/parse_main.o: src/front_end/parse/parse_main.c
	$(CC) $(CFLAGS) -o $@ $<

src/front_end/parse/parse_production_tab.o: src/front_end/parse/parse_production_tab.c
	$(CC) $(CFLAGS) -o $@ $<

src/front_end/parse/parse_func.o: src/front_end/parse/parse_func.c
	$(CC) $(CFLAGS) -o $@ $<

src/front_end/parse/parse_lib.o: src/front_end/parse/parse_lib.c
	$(CC) $(CFLAGS) -o $@ $<

src/front_end/semantics/seman_lib.o: src/front_end/semantics/seman_lib.c
	$(CC) $(CFLAGS) -o $@ $<

src/front_end/semantics/seman_main.o: src/front_end/semantics/seman_main.c
	$(CC) $(CFLAGS) -o $@ $<

src/front_end/semantics/seman_type.o: src/front_end/semantics/seman_type.c
	$(CC) $(CFLAGS) -o $@ $<

src/mid_end/ir/ir_list.o: src/mid_end/ir/ir_list.c
	$(CC) $(CFLAGS) -o $@ $<

src/mid_end/ir/ir_list_lib.o: src/mid_end/ir/ir_list_lib.c
	$(CC) $(CFLAGS) -o $@ $<

src/mid_end/frame/frame_main.o: src/mid_end/frame/frame_main.c
	$(CC) $(CFLAGS) -o $@ $<

src/mid_end/frame/var.o: src/mid_end/frame/var.c
	$(CC) $(CFLAGS) -o $@ $<

src/front_end/label/label_main.o: src/front_end/label/label_main.c
	$(CC) $(CFLAGS) -o $@ $<

src/back_end/pasm/pasm_main.o: src/back_end/pasm/pasm_main.c
	$(CC) $(CFLAGS) -o $@ $<

src/back_end/pasm/pasm_lib.o: src/back_end/pasm/pasm_lib.c
	$(CC) $(CFLAGS) -o $@ $<

src/back_end/pasm/pasm_lib_t.o: src/back_end/pasm/pasm_lib_t.c
	$(CC) $(CFLAGS) -o $@ $<

src/back_end/ins/i386/ins_main.o: src/back_end/ins/i386/ins_main.c
	$(CC) $(CFLAGS) -o $@ $<

src/back_end/ins/i386/ins_update.o: src/back_end/ins/i386/ins_update.c
	$(CC) $(CFLAGS) -o $@ $<

src/back_end/ins/i386/ins_lib.o: src/back_end/ins/i386/ins_lib.c
	$(CC) $(CFLAGS) -o $@ $<

src/back_end/ins/i386/ins_lib_t.o: src/back_end/ins/i386/ins_lib_t.c
	$(CC) $(CFLAGS) -o $@ $<

src/back_end/ins/i386/ins_lib_1.o: src/back_end/ins/i386/ins_lib_1.c
	$(CC) $(CFLAGS) -o $@ $<

src/back_end/mcode/mcode_main.o: src/back_end/mcode/mcode_main.c
	$(CC) $(CFLAGS) -o $@ $<

src/back_end/mcode/mcode_file.o: src/back_end/mcode/mcode_file.c
	$(CC) $(CFLAGS) -o $@ $<

src/back_end/mcode/mcode_lib.o: src/back_end/mcode/mcode_lib.c
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

