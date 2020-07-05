//L_Line/c

#include "./L_Line.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

static int	append_buffer(struct L_Line *this, t_str buffer, t_uint index_buffer)
{
	t_uint	index_string;

	/*If the current end if the string is less than the string length:       */
	/*Append the buffer to this->string until either the end of this->string */
	/*is reached, a newline is found in the buffer or the end of the buffer  */
	/*is reached.*/
	if (!this->string_last)
	{
		index_string = 0;
		while (this->string[index_string] != '\0')
			index_string++;
		while (index_string < this->string_size)
		{
			if (buffer[index_buffer] == '\n')
				return (index_buffer + 1);
			if (buffer[index_buffer] == '\0')
				return (0);
			this->string[index_string] = buffer[index_buffer];
			index_string++;
			index_buffer++;
		}
	}
	if (index_string == this->string_size)
	{
		this->string_next = L_String.new(this, (t_uchar)1, L_String.string_size);
		this->string_last = this->string_next;
	}
	printf("%d : %c\n", index_buffer, buffer[index_buffer]);
	if (buffer[index_buffer] != '\0')
	{
		printf("Append_buffer\n");
		printf("This : %p\n", &this);
		printf("String_next : %p : %s\n", this->string_next, this->string_next->string);
		return (this->string_last->append_buffer(this->string_last, buffer, index_buffer));
	}
	else
		return (0);
}

static int	destruct(struct L_Line *this)
{
	if (this->string)
	{
		free(this->string);
		this->string = NULL;
	}
	if (this->verbose)
		printf("L_Line : %p : Destructed\n", (this));
	free(this);
	return (0);
}

static struct L_Line	*new(t_uchar verbose, t_uint string_size)
{
	struct L_Line	*this;

	//Allocate Memory
	this = (struct L_Line*)malloc(sizeof(struct L_Line));
	if (!this)
	{
		if (verbose)
			printf("L_Line : Construction Failed : Malloc Failed\n");
		return (NULL);
	}
	else if (verbose)
		printf("L_Line : %p : Construction Started\n", this);

	//Initialize Properties
	this->verbose = verbose;
	this->string = (t_str)malloc(string_size + 1);
	this->string_size = string_size;
	this->string[0] = '\0';
	this->string[string_size] = '\0';

	//Intialize Structs
	this->string_next = NULL;
	this->string_last = NULL;
	this->next = NULL;

	//Initialize Methods
	this->destruct = &destruct;
	this->append_buffer = &append_buffer;

	if (this->verbose)
		printf("L_Line : %p : Constructed\n\n", this);
	return (this);
}

const struct L_Line_Class L_Line = {.new = &new, .string_size = STRING_SIZE};