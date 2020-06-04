#ifndef LUNA_FILE_H
# define LUNA_FILE_H

typedef char			*t_str;
typedef unsigned char	*t_uchar;

struct Luna_File
{
	//Properties
	t_uchar	verbose;

	//Methods
	int		(*destruct)(struct Luna_File *this);
};

extern const struct Luna_File_Class 
{
	struct Luna_File*(*new)(t_uchar verbose);
} Luna_File;

#endif