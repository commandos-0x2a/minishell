#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>

int main() {
    char *termtype = getenv("TERM");  // Get the terminal type from the environment
    if (termtype == NULL) {
        fprintf(stderr, "Error: TERM environment variable not set.\n");
        return EXIT_FAILURE;
    }

    // Initialize the terminal
    int success = tgetent(NULL, termtype);
    if (success < 0) {
        fprintf(stderr, "Error: Could not access the termcap database.\n");
        return EXIT_FAILURE;
    } else if (success == 0) {
        fprintf(stderr, "Error: Terminal type '%s' is not defined in the termcap database.\n", termtype);
        return EXIT_FAILURE;
    }

    // Retrieve termcap strings
    char *_clear_screen = tgetstr("cl", NULL);
    char *move_cursor = tgetstr("cm", NULL);

    if (_clear_screen == NULL || move_cursor == NULL) {
        fprintf(stderr, "Error: Required terminal capabilities not found.\n");
        return EXIT_FAILURE;
    }

    // Clear the screen
    printf("%s", _clear_screen);
	int i = 0;
	while (_clear_screen[i])
	{
		printf("%c ", _clear_screen[i]);
		i++;
	}
	
	printf("\ncm: %s\n", move_cursor);
    // Move the cursor to row 10, column 20
    char *cursor_command = tgoto(move_cursor, 20, 10);
    if (cursor_command) {
        printf("%s", cursor_command);
        printf("Hello, Termcap!");  // Print message at the cursor position
    } else {
        fprintf(stderr, "Error: Could not generate cursor command.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
