# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>

int main() {
    char *name;

    name = readline("Enter your name: ");
    printf("%s", name);

    return 0;
}