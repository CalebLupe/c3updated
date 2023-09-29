#include<stdio.h>
#include<stdlib.h>
#include "utilities.h"
#include <time.h> 

/* Allocate space for num_elements and return by reference */
void allocate_memory(int **buffer, int len) {
	if(buffer == NULL || len <= 0) {
	// Test to make sure the number inputted is not negative
	fprintf(stderr, "Do not enter a negative number. \n");
	exit(1);
		return;
	}

	*buffer = (int *) malloc(len * sizeof(int));
	if (*buffer == NULL) {
		fprintf(stderr, "Memory allocation failed.\n");
		exit(1);
	}
}

/* Given the allocated space, initialize contents */
void initialize_memory(int *buffer, int len) {
	if(buffer == NULL || len <= 0) {
		return;
	}
	static int randomize = 0;
    if (!randomize) {
        srand(time(NULL));
        randomize = 1;
    }

	for (int i = 0; i < len; i++) {
		buffer[i] = rand();
		// Additional Test: Ensure random numbers are within the expected range.
		// Assuming the range is between 0 and RAND_MAX, this is just for demonstration.
		if (buffer[i] < 0 || buffer[i] > RAND_MAX) {
			fprintf(stderr, "Random number out of range.\n");
			exit(1);
		}
	}
}

/* Given initialized space, write contents to file, binary format */
void write_memory_to_file(int *buffer, int len, char *fname) {
	if(buffer == NULL || len <= 0) {
		return;
	}
	FILE *file = fopen(fname, "wb");
	if (file) {
		// Additional Test: Check if the file write was successful.
		size_t written = fwrite(buffer, sizeof(int), len, file);
		if (written != len) {
			fprintf(stderr, "Failed to write the expected number of elements to the file.\n");
			exit(1);
		}
		fclose(file);
	} else {
		fprintf(stderr, "Failed to open file for writing.\n");
		exit(1);
	}
}

/* Given the filename, determine size of file in units of number of integers */
int determine_file_size(char *fn) {
	int num_elements = 0;
	if(fn == NULL) {
		return 0;
	}
	FILE *file = fopen(fn, "rb");
	if (file) {
		fseek(file, 0, SEEK_END);
		long position = ftell(file); // Store the result of ftell

		// Additional Test: Check if ftell failed
		if (position == -1) {
			fprintf(stderr, "Error determining file size.\n");
			fclose(file);
			exit(1);
		}

		num_elements = position / sizeof(int);
		fclose(file);
	}
	return num_elements;
}

void initialize_memory_from_file(int **buffer, int *len, char *fn) {
	if(!buffer || !len || !fn) {
		return;
	}
	*len = determine_file_size(fn);
	allocate_memory(buffer, *len);
	FILE *file = fopen(fn, "rb");
	if (file) {
		size_t read = fread(*buffer, sizeof(int), *len, file);
		// Additional Test: Ensure that the entire file was read.
		if (read != *len) {
			fprintf(stderr, "Failed to read the expected number of elements from the file.\n");
			exit(1);
		}
		fclose(file);
	} else {
		fprintf(stderr, "Failed to open file for reading.\n");
		exit(1);
	}
}

/* Print the contents of memory to the screen */
void print_memory(int *buffer, int len) {
	if(!buffer || len <= 0) {
		return;
	}
	for (int i = 0; i < len; i++) {
		printf("%d ", buffer[i]);
	}
	printf("\n");
}
