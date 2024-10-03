#ifndef EDITOR_H
#define EDITOR_H

#define MAX_LINES 1000
#define MAX_LINES_LENGTH 256

// Global variables announcement
extern char text[MAX_LINES][MAX_LINES_LENGTH];
extern int num_lines;

// Function declaration
void load_file(const char *filename);
void save_file(const char *filename);
void handle_input(int ch, int *x, int *y);

#endif
