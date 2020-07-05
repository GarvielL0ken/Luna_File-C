#ifndef LUNA_FILE_H
# define LUNA_FILE_H
# define BUFFER_SIZE 6
# include "includes/typedefs.h"
# include "classes/L_Line.h"

struct Luna_File
{
	//Properties
	t_uchar	verbose;
	t_str	file_path;
	t_str	buffer;
	int		fd;
	t_uint	buffer_size;

	//Sub Structs
	struct L_Line	*line;
	struct L_Line	*last_line;

	//Methods
	int		(*destruct)(struct Luna_File *this);
	int		(*open)(struct Luna_File *this, const t_str file_path);
	int		(*read)(struct Luna_File *this, const t_str file_path);
	int		(*append_buffer)(struct Luna_File *this, t_str buffer);
	int		(*print_lines)(struct Luna_File *this);
};

extern const struct Luna_File_Class 
{
	struct Luna_File*(*new)(t_uchar verbose, t_str file_path);
} Luna_File;

#endif