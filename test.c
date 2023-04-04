#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char* input;

    while ((input = readline("> ")) != NULL) {
        // Do something with input...

        rl_replace_line("", 0);  // Clear the input line
        rl_redisplay();  // Redraw the input line

        add_history(input);  // Add input to the command history
        free(input);
    }
    return 0;
}