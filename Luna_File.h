#ifndef LUNA_FILE_H
# define LUNA_FILE_H

typedef char			*t_str;
typedef unsigned char	*t_uchar;

struct Luna_File
{
	//Properties
	t_uchar	verbose;
	t_str	file_path;
	int		fd;

	//Methods
	int		(*destruct)(struct Luna_File *this);
	int		(*open)(struct Luna_File *this, const t_str file_path);
	int		(*read)(struct Luna_File *this, const t_str file_path);
};

extern const struct Luna_File_Class 
{
	struct Luna_File*(*new)(t_uchar verbose, t_str file_path);
} Luna_File;

#endif