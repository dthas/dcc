//===========================================================================
// dnasm_graph.h
//   Copyright (C) 2013 Free Software Foundation, Inc.
//   Originally by ZhaoFeng Liang <zhf.liang@outlook.com>
//
//This file is part of DTHAS_DNASM.
//
//DTHAS_DNASM is free software; you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation; either version 2 of the License, or 
//(at your option) any later version.
//
//DTHAS_DNASM is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with DTHAS; If not, see <http://www.gnu.org/licenses/>.  
//===========================================================================

#ifndef	_DNASM_GRAPH_H_
#define	_DNASM_GRAPH_H_

//-------------------------------------------------------------------------
// vertex
//-------------------------------------------------------------------------
struct vertex
{
	s32	v_id;
	s32	r_id;
};


struct vertex_list
{
	struct vertex *v;
	
	struct vertex_list *head;
	struct vertex_list *tail;
};

//-------------------------------------------------------------------------
// edge
//-------------------------------------------------------------------------
struct edge
{
	struct vertex *v_s;
	struct vertex *v_e;
};

struct edge_list
{
	struct edge *e;
	struct edge_list *head;
	struct edge_list *tail;
};

//-------------------------------------------------------------------------
// conflict graph
//-------------------------------------------------------------------------
struct graph
{
	struct vertex_list *vlist;
	struct edge_list *elist;
};

struct graph_list
{
	struct graph *g;
	struct graph_list *head;
	struct graph_list *tail;
};

struct graph_file
{
	struct graph_list *glist;
	struct graph_file *head;
	struct graph_file *tail;
};

struct graph_file	*gcurfile;

#endif
