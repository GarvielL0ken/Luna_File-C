//main.c
#include <stdio.h>
#include <stdlib.h>
#include "./Luna_File.h"

int main()
{
	struct Luna_File *file = Luna_File.new((t_uchar)1);

	printf("%d\n", file->verbose);
	printf("%p\n", file);
	file->destruct(file);
	free(file);
}