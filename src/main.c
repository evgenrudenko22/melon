#include "editor.h"
#include <ncurses.h>

#define CTRL_KEY(k) ((k) & 0x1f)

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Usage: %s <filename>\n", argv[0]);
	}

	// Init ncurses
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();

	// Load a file
	load_file(argv[1]);

	int x = 0, y = 0;
	
	while  (1) {
		clear();
		// Text output
		for(int i = 0; i < num_lines; i++) {
			mvprintw(i, 0, "%s", text[i]);
		};
		move(y, x);
		refresh();
		
		int ch = getch();
		if (ch == CTRL_KEY('q')) {
			break;
		} else if (ch == CTRL_KEY('s')) {
			save_file(argv[1]);
		} else {
			handle_input(ch, &x, &y);
		}
	}
	
	// Stoping ncurses
	endwin();
	return 0;
}
