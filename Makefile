SRCS = main.c\
		Luna_File.c
HEADER = Luna_File.h
OUTPUT = Luna_File

all: $(SRCS) $(HEADER)
	gcc $(SRCS) -o $(OUTPUT)

clean:
	rm -rf $(OUTPUT)