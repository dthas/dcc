#===========================================================================
# dcc.sh
#   Copyright (C) 2013 Free Software Foundation, Inc.
#   Originally by ZhaoFeng Liang <zhf.liang@outlook.com>
#
#This file is part of DTAHS_DCC.
#
#DTHAS is free software; you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation; either version 2 of the License, or 
#(at your option) any later version.
#
#DTHAS is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.
#
#You should have received a copy of the GNU General Public License
#along with DTHAS; If not, see <http://www.gnu.org/licenses/>.  
#===========================================================================

#-------------------------------------------------------------------------
# (1) compile programs of dld(static link)
#-------------------------------------------------------------------------
cd dld_s
make all

#-------------------------------------------------------------------------
# (2) compile programs of dnasm
#-------------------------------------------------------------------------
cd ../dnasm
make all

#-------------------------------------------------------------------------
# (3) compile programs of dcc
#-------------------------------------------------------------------------
cd ../dcc
make all

#-------------------------------------------------------------------------
# (4) dcc:: test1.c ==> test.asm
#-------------------------------------------------------------------------
dst/dcc src/temp/test1.c  1>src/temp/error.txt 2>&1

#-------------------------------------------------------------------------
# (5) dnasm:: test.asm ==> test.o, start.asm ==> start.o
#-------------------------------------------------------------------------
../dnasm/dst/dnasm src/temp/test.asm  1>src/temp/error.txt 2>&1

../dnasm/dst/dnasm src/temp/start.asm  1>src/temp/error1.txt 2>&1

#-------------------------------------------------------------------------
# (6) dld:: *.o ==> test 
#-------------------------------------------------------------------------
cd dst
ar -x dcc.a

cd ..
../dld_s/dst/dld -Ttext 0x8048000 -g src/temp/start.o src/temp/test.o dst/printf.o dst/write.o dst/lib.o dst/liba.o 1>src/temp/error.txt 2>&1

