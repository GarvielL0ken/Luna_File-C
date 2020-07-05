#ifndef L_LINE_H
# define L_LINE_H
# define STRING_SIZE 6
# include "../includes/typedefs.h"
# include "L_String.h"

struct L_Line
{
	//Properties
	t_uchar			verbose;
	t_str			string;
	t_uint			string_size;

	//Structs
	struct L_String	*string_next;
	struct L_String	*string_last;
	struct L_Line	*next;

	//Methods
	int				(*destruct)(struct L_Line *this);
	int				(*append_buffer)(struct L_Line *this, t_str buffer, t_uint index_buffer);
};

extern const struct L_Line_Class 
{
	//Properties
	t_uint			string_size;

	//Methods
	struct L_Line	*(*new)(t_uchar verbose, t_uint string_size);
} L_Line;

#endif