//Luna_File.c

#include "./Luna_File.h"
#include <stdio.h>

static int	destruct(struct Luna_File *this)
{
	if (this->verbose)
		printf("destruct\n");
	return (0);
}

static struct Luna_File	*new(t_uchar verbose)
{
	struct Luna_File	*this;

	//Allocate Memory
	this = (struct Luna_File*)malloc(sizeof(struct Luna_File));

	//Initialize Properties
	this->verbose = verbose;

	//Initialize Methods
	this->destruct = &destruct;

	if (this->verbose)
		printf("Luna_File : %p : Created\n", this);
	return (this);
}

const struct Luna_File_Class Luna_File = {.new = &new};
