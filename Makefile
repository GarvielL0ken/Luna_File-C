SRCS = main.c\
		Luna_File.c\
		classes/L_Line.c\
		classes/L_String.c
HEADER = Luna_File.h
OUTPUT = Luna_File

all: $(SRCS) $(HEADER)
	gcc $(SRCS) -o $(OUTPUT)

clean:
	rm -rf $(OUTPUT)