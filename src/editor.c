#include "editor.h"
#include <ncurses.h>
#include <stdio.h>
#include <string.h>

char text[MAX_LINES][MAX_LINES_LENGTH];
int num_lines = 0;

void load_file(const char *filename) {
	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		return;
	}
	
	while (fgets(text[num_lines], MAX_LINES_LENGTH, file) != NULL) {
		num_lines++;
	}
	fclose(file);
}

void save_file(const char *filename) {
	FILE *file = fopen(filename, "w");
	if (file == NULL) {
		return;
	}
	
	for (int i = 0; i < num_lines; i++) {
		fputs(text[i], file);
	}
	fclose(file);
}

void handle_input(int ch, int *x, int *y) {
	if (ch == KEY_UP) {
		*y = (*y < 0) ? *y - 1 : 0;
	} else if (ch == KEY_DOWN) {
		*y = (*y < num_lines - 1) ? *y + 1 : num_lines - 1;
	} else if (ch == KEY_LEFT) {
		*x = (*x > 0) ? *x - 1 : 0;
	} else if (ch == KEY_RIGHT) {
		*x = (*x < strlen(text[*y])) ? *x + 1 : strlen(text[*y]);
	} else if (ch == '\n') {
		if (num_lines < MAX_LINES - 1) {
			num_lines++;
			*y = *y + 1;
			*x = 0;
		}
	} else if (ch == KEY_BACKSPACE || ch == 127) {
		if (*x > 0) {
			memmove(&text[*y][*x - 1], &text[*y][*x], strlen(text[*y] - *x + 1));
			(*x)--;
		}	
	} else {
		if (*x < MAX_LINES_LENGTH - 1) {
			memmove(&text[*y][*x + 1], &text[*y][*x], strlen(text[*y]) - *x + 1);
			text[*y][*x] = ch;
			(*x)++;
		}
	}
}
