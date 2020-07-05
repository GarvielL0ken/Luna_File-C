//Luna_File.c

#include "./Luna_File.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

static int	append_buffer(struct Luna_File *this, t_str buffer)
{
	int	index_buffer;

	//Create a new line if no line exists and set the last line to point to the new line
	if (this->verbose)
		printf("Luna_File : %p : APPEND_BUFFER\n", this);
	if (!(this->line))
	{
		this->line = L_Line.new((t_uchar)1, L_Line.string_size);
		this->last_line = this->line;
	}
	index_buffer = 0;
	while (1)
	{
		index_buffer = this->last_line->append_buffer(this->last_line, buffer, index_buffer);
		printf("index_buffer : %d\n", index_buffer);
		if (index_buffer)
		{
			this->last_line->next = L_Line.new((t_uchar)1, L_Line.string_size);
			this->last_line = this->last_line->next;
		}
		else
			return (1);
	}
}

static int	L_open(struct Luna_File *this, t_str file_path)
{
	if (!file_path)
	{
		if (this->file_path)
			file_path = this->file_path;
		else
		{
			if (this->verbose)
				printf("          : %p : Error : Failed to open file : No file_path was set\n", this);
			return (-1);
		}
	}
	if (this->verbose)
		printf("          : %p : Opening File : %s\n", this, file_path);
	this->fd = open(file_path, O_RDONLY);
	return (1);
}

static int	L_read(struct Luna_File *this, t_str file_path)
{
	int	read_size;

	if (this->verbose)
		printf("Luna_File : %p : Reading File : %s\n", this, file_path);

	if (this->fd < 0)
	{
		if (this->verbose)
			printf("          : %p : File Not Open\n", this);
		if (this->open(this, file_path) < 0)
			return (-1);
	}

	if (!(this->buffer))
		this->buffer = (t_str)malloc(this->buffer_size + 1);
	this->buffer[this->buffer_size] = '\0';
	while (read_size = read(this->fd, this->buffer, this->buffer_size))
	{
		if (read_size < this->buffer_size)
			this->buffer[read_size] = '\0';
		printf("Luna_File : %p : BUFFER : %s\n", this, this->buffer);
		this->append_buffer(this, this->buffer);
	}
	free(this->buffer);
	close(this->fd);
	return (1);
}

int		print_lines(struct Luna_File *this)
{
	struct L_Line	*current_line;
	struct L_String *current_string;
	t_uint			index;

	current_line = this->line;
	index = 0;
	while (current_line)
	{
		if (this->verbose)
			printf("L_line : %d\n", index);
		printf("%s\n", current_line->string);
		current_string = current_line->string_next;
		while (current_string)
		{
			printf("%s\n", current_string->string);
			current_string = current_string->next;
		}
		printf("NEWLINE\n");
		current_line = current_line->next;
		index++;
	}
	return (1);
}

static int	destruct(struct Luna_File *this)
{
	struct L_Line	*next;

	if (this->file_path)
	{
		free(this->file_path);
		this->file_path = NULL;
	}
	if (this->buffer)
	{
		free(this->buffer);
		this->buffer = NULL;
	}
	while (this->line)
	{
		next = this->line->next;
		this->line->destruct(this->line);
		this->line = next;
	}
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
	this->buffer = NULL;
	this->fd = -1;
	this->buffer_size = BUFFER_SIZE;
	this->last_line = 0;
	if (verbose)
	{
		printf("          : %p : file_path : %s\n", this, this->file_path);
		printf("          : %p : fd : %d\n", this, this->fd);
	}
	//Initialize Structs
	this->line = NULL;

	//Initialize Methods
	this->destruct = &destruct;
	this->open = &L_open;
	this->read = &L_read;
	this->append_buffer = &append_buffer;
	this->print_lines = &print_lines;

	if (this->verbose)
		printf("Luna_File : %p : Constructed\n\n", this);
	return (this);
}

const struct Luna_File_Class Luna_File = {.new = &new};
