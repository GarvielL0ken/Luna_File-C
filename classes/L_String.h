#ifndef L_STRING_H
# define L_STRING_H
# include "../includes/typedefs.h"
# include "L_Line.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

struct L_String
{
	//Properties
	t_uchar			verbose;
	t_str			string;
	t_uint			string_size;

	//Objects
	struct L_Line	*parent;
	struct L_String	*next;

	//Methods
	int				(*destruct)(struct L_String *this);
	int				(*append_buffer)(struct L_String *this, t_str buffer, t_uint index_buffer);
};

extern const struct L_String_Class {
	//Properties
	t_uint	string_size;

	//Methods
	struct L_String	*(*new)(struct L_Line *parent, t_uchar verbose, t_uint string_size);
} L_String;

#endif