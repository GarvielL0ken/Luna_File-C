//main.c
#include <stdio.h>
#include <stdlib.h>
#include "./Luna_File.h"

int main()
{
	struct Luna_File *file = Luna_File.new((t_uchar)1, NULL);

	file->read(file, "test_files/00001_00010.txt");
	file->print_lines(file);
	file->destruct(file);
	free(file);
}