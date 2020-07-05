#include "L_String.h"

static int	append_buffer(struct L_String *this, t_str buffer, t_uint index_buffer)
{
	t_uint	index_string;
	struct L_Line	**parent;

	index_string = 0;
	printf("Parent : %p\n", &(this->parent));
	while (this->string[index_string] != '\0')
		index_string++;
	while (index_string < this->string_size)
	{
		printf("%d : index_buffer : %d : %c\n", index_string, index_buffer, buffer[index_buffer]);
		if (buffer[index_buffer] == '\n')
			return (index_buffer + 1);
		if (buffer[index_buffer] == '\0')
			return (0);
		this->string[index_string] = buffer[index_buffer];
		index_string++;
		index_buffer++;
	}
	if (index_string == this->string_size)
	{
		this->next = L_String.new(this->parent, (t_uchar)1, L_String.string_size);
		
		this->parent->string_last = this->next;
	}
	if (buffer[index_buffer] != '\0')
		return (this->next->append_buffer(this->next, buffer, index_buffer));
	else
		return (0);
}

static int	destruct(struct L_String *this)
{
	if (this->string)
	{
		free(this->string);
		this->string = NULL;
	}
	if (this->verbose)
		printf("L_String : %p : Destructed\n", (this));
	free(this);
	return (0);
}

static struct L_String	*new(struct L_Line *parent, t_uchar verbose, t_uint string_size)
{
	struct L_String	*this;

	//Allocate Memory
	this = (struct L_String*)malloc(sizeof(struct L_String));
	if (!this)
	{
		if (verbose)
			printf("L_String : Construction Failed : Malloc Failed\n");
		return (NULL);
	}
	else if (verbose)
		printf("L_String : %p : Construction Started\n", this);

	//Initialize Properties
	this->verbose = verbose;
	this->string = (t_str)malloc(string_size + 1);
	this->string_size = string_size;
	this->string[0] = '\0';
	this->string[string_size] = '\0';

	//Intialize Structs
	this->parent = parent;
	this->next = NULL;

	//Initialize Methods
	this->destruct = &destruct;
	this->append_buffer = &append_buffer;

	if (this->verbose)
		printf("L_String : %p : Constructed\n\n", this);
	return (this);
}

const struct L_String_Class L_String = {.new = &new, .string_size = STRING_SIZE};