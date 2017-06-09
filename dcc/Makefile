#===========================================================================
# Makefile
#   Copyright (C) 2013 Free Software Foundation, Inc.
#   Originally by ZhaoFeng Liang <zhf.liang@outlook.com>
#
#This file is part of DTAHS_DCC.
#
#DTAHS_DCC is free software; you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation; either version 2 of the License, or 
#(at your option) any later version.
#
#DTAHS_DCC is distributed in the hope that it will be useful,
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
LDFLAGS		= -Map dcc.map $(LOBJS_UBUNTU)
ARFLAGS		= rcs

# This Program
DCC		= dst/dcc
LIB		= dst/dcc.a

OBJS		= $(OBJS_MAIN) $(OBJS_SYMTBL) $(OBJS_PRE)\
			$(OBJS_LEX) $(OBJS_PARSE) $(OBJS_SEMANTICS)\
			$(OBJS_IR) $(OBJS_FRAME) $(OBJS_LABEL)\
			$(OBJS_PASM) $(OBJS_BLOCK) $(OBJS_LIVE)\
			$(OBJS_GRAPH) $(OBJS_ALLOC)\
			$(OBJS_INS) $(OBJS_ASM)


OBJS_MAIN	= src/main/main.o
OBJS_SYMTBL	= src/front_end/symbol/symbol_main.o
OBJS_PRE	= src/pre/pre_main.o src/pre/lex/pre_lex_char_state_tab.o\
			src/pre/lex/pre_lex_word_state_tab.o
OBJS_LEX	= src/front_end/lex/lex_main.o src/front_end/lex/lex_char_state_tab.o src/front_end/lex/lex_lib.o
OBJS_PARSE	= src/front_end/parse/parse_main.o src/front_end/parse/parse_production_tab.o\
			src/front_end/parse/parse_lib.o src/front_end/parse/parse_func.o

OBJS_SEMANTICS	= src/front_end/semantics/seman_lib.o src/front_end/semantics/seman_main.o\
			src/front_end/semantics/seman_type.o

OBJS_IR		= src/mid_end/ir/ir_list.o src/mid_end/ir/ir_list_lib.o

OBJS_PASM	= src/back_end/pasm/pasm_main.o src/back_end/pasm/pasm_lib.o src/back_end/pasm/pasm_lib_t.o

OBJS_FRAME	= src/mid_end/frame/frame_main.o src/mid_end/frame/var.o

OBJS_LABEL	= src/front_end/label/label_main.o	

OBJS_BLOCK	= src/back_end/block/block_main.o src/back_end/block/block_lib.o src/back_end/block/block_lib_t.o

OBJS_LIVE	= src/back_end/live/live_main.o src/back_end/live/live_lib.o src/back_end/live/live_lib_t.o

OBJS_GRAPH	= src/back_end/graph/graph_main.o src/back_end/graph/graph_lib.o src/back_end/graph/graph_lib_t.o

OBJS_ALLOC	= src/back_end/alloc/alloc_main.o src/back_end/alloc/alloc_lib.o src/back_end/alloc/alloc_lib_t.o

OBJS_INS	= src/back_end/ins/i386/ins_main.o src/back_end/ins/i386/ins_lib.o src/back_end/ins/i386/ins_lib_t.o

OBJS_ASM	= src/back_end/asm/asm_main.o src/back_end/asm/asm_file.o

LOBJS_UBUNTU	= /usr/lib/i386-linux-gnu/crt1.o\
			/usr/lib/i386-linux-gnu/crti.o\
			/usr/lib/gcc/i686-linux-gnu/4.6.3/crtbegin.o\
			-lc /usr/lib/gcc/i686-linux-gnu/4.6.3/crtend.o\
			/usr/lib/i386-linux-gnu/crtn.o\
			-dynamic-linker /lib/ld-linux.so.2 
	
LOBJS		= src/lib/lib.o src/lib/liba.o
			
EX_LOBJS	= src/lib/ex/printf.o src/lib/ex/write.o src/lib/ex/print.o

all : realclean everything clean

realclean :
	rm -f  $(OBJS) $(LOBJS) $(LIB) $(EX_LOBJS)

clean :
	rm -f $(OBJS) $(LOBJS) $(EX_LOBJS)

everything : $(DCC) $(OBJS) $(LOBJS) $(EX_LOBJS)



$(DCC) : $(OBJS) $(LIB) 
	$(LD) $(LDFLAGS) -o $(DCC) $^

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

src/pre/lex/pre_lex_word_state_tab.o: src/pre/lex/pre_lex_word_state_tab.c
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

src/back_end/block/block_main.o: src/back_end/block/block_main.c
	$(CC) $(CFLAGS) -o $@ $<

src/back_end/block/block_lib.o: src/back_end/block/block_lib.c
	$(CC) $(CFLAGS) -o $@ $<

src/back_end/block/block_lib_t.o: src/back_end/block/block_lib_t.c
	$(CC) $(CFLAGS) -o $@ $<

src/back_end/live/live_main.o: src/back_end/live/live_main.c
	$(CC) $(CFLAGS) -o $@ $<

src/back_end/live/live_lib.o: src/back_end/live/live_lib.c
	$(CC) $(CFLAGS) -o $@ $<

src/back_end/live/live_lib_t.o: src/back_end/live/live_lib_t.c
	$(CC) $(CFLAGS) -o $@ $<

src/back_end/graph/graph_main.o: src/back_end/graph/graph_main.c
	$(CC) $(CFLAGS) -o $@ $<

src/back_end/graph/graph_lib.o: src/back_end/graph/graph_lib.c
	$(CC) $(CFLAGS) -o $@ $<

src/back_end/graph/graph_lib_t.o: src/back_end/graph/graph_lib_t.c
	$(CC) $(CFLAGS) -o $@ $<

src/back_end/alloc/alloc_main.o: src/back_end/alloc/alloc_main.c
	$(CC) $(CFLAGS) -o $@ $<

src/back_end/alloc/alloc_lib.o: src/back_end/alloc/alloc_lib.c
	$(CC) $(CFLAGS) -o $@ $<

src/back_end/alloc/alloc_lib_t.o: src/back_end/alloc/alloc_lib_t.c
	$(CC) $(CFLAGS) -o $@ $<

src/back_end/ins/i386/ins_main.o: src/back_end/ins/i386/ins_main.c
	$(CC) $(CFLAGS) -o $@ $<

src/back_end/ins/i386/ins_lib.o: src/back_end/ins/i386/ins_lib.c
	$(CC) $(CFLAGS) -o $@ $<

src/back_end/ins/i386/ins_lib_t.o: src/back_end/ins/i386/ins_lib_t.c
	$(CC) $(CFLAGS) -o $@ $<

src/back_end/asm/asm_main.o: src/back_end/asm/asm_main.c
	$(CC) $(CFLAGS) -o $@ $<

src/back_end/asm/asm_file.o: src/back_end/asm/asm_file.c
	$(CC) $(CFLAGS) -o $@ $<

src/lib/ex/printf.o: src/lib/ex/printf.c
	$(CC) $(CFLAGS) -o $@ $<

src/lib/ex/print.o : src/lib/ex/print.asm
	$(ASM) $(ASMLIBFLAGS) -o $@ $<

src/lib/ex/write.o : src/lib/ex/write.asm
	$(ASM) $(ASMLIBFLAGS) -o $@ $<
