//Luna_File.c

#include "./Luna_File.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

static int	L_open(struct Luna_File *this, t_str file_path)
{
	if (!file_path)
	{
		if (this->file_path)
			file_path = this->file_path;
		else
			return (-1);
	}
	if (this->verbose)
		printf("          : %p : Opening File : %s\n", this, file_path);
	this->fd = open(file_path, O_RDONLY);
}

static int	L_read(struct Luna_File *this, t_str file_path)
{
	t_str	string;

	if (this->verbose)
		printf("Luna_File : %p : Reading File : %s\n", this, file_path);

	if (this->fd < 0)
	{
		if (this->verbose)
			printf("          : %p : File Not Open\n", this);
		if (this->open(this, file_path) < 0)
			return (-1);
	}
	fd = open(file_path, O_RDONLY);
	string = (t_str)malloc(10);
	read(fd, string, 9);
	string[10] = '\0';
	printf("%s\n", string);
	free(string);
	close(fd);
	return (1);
}

static int	destruct(struct Luna_File *this)
{
	if (this->verbose)
		printf("Luna_File : %p : Destructed\n", (this));
	free(this);
	return (0);
}

static struct Luna_File	*new(t_uchar verbose, t_str file_path)
{
	struct Luna_File	*this;

	//Allocate Memory
	this = (struct Luna_File*)malloc(sizeof(struct Luna_File));
	if (!this)
	{
		if (verbose)
			printf("Luna_File : Construction Failed : Malloc Failed\n");
		return (NULL);
	}
	else if (verbose)
		printf("Luna_File : %p : Construction Started\n", this);

	//Initialize Properties
	this->verbose = verbose;
	this->file_path = file_path;
	if (verbose)
		printf("          : %p : file_path : %s\n", this, this->file_path);

	//Initialize Methods
	this->destruct = &destruct;
	this->read = &L_read;

	if (this->verbose)
		printf("Luna_File : %p : Constructed\n", this);
	return (this);
}

const struct Luna_File_Class Luna_File = {.new = &new};
