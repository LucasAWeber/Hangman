#include "header.h"

int main() {
    int game = 1;
    int rand = 0;
    int error = 0;
    char word[MAX_CHARS];
    char guessed[MAX_CHARS];
    char letterBank[27] = "                          \0";
    char guess;

    printf("\n*********************************************\n");
    printf("        Welcome to the game of Hangman!\n");
    printf("*********************************************\n");
    printf("A game in which the object is for one player\n");
    printf("to guess the letters of an unknown word \n");
    printf("before the player who knows the word creates\n");
    printf("a stick figure of a hanged man by drawing one\n");
    printf("line for each incorrect guess.\n");
    printf("*********************************************\n\n");
    /*printf("Would you like to play against a friend or\n");
    printf("bot? Type 0 for friend and 1 for bot: ");
    fflush(stdin);
    scanf("%d", &rand);
    while (rand != 0 && rand != 1) {
        printf("Invalid input!\n");
        printf("Type 0 for friend and 1 for bot: ");
        fflush(stdin);
        scanf("%d", &rand);
    }*/
    if (!rand) {
        fflush(stdin);
        strcpy(word,getpass("Type the secret word: "));
        upper(word);
    }
    for (int i=0;i<=strlen(word);i++) {
        guessed[i] = '_';
        if (i==strlen(word)) guessed[i] = '\0';
    }

    while (game) {
        print(error, guessed);
        printf("Guess: ");
        fflush(stdin);
        scanf("%c", &guess);
        guess = toupper(guess);
        while (check(letterBank, guess)) {
            printf("Already guessed!\n");
            printf("Guess: ");
            fflush(stdin);
            scanf("%c", &guess);
            guess = toupper(guess);
        }

        error += logic(word, guessed, letterBank, guess);

        if (error >= 6) {
            print(error, guessed);
            printf("You lost! The word was %s\n", word);
            printf("*********************************************\n\n");
            break;
        }
    }

    return 0;
}

void upper(char word[MAX_CHARS]) {
    for (int i=0;i<strlen(word);i++) {
        word[i] = toupper(word[i]);
    }
}

void print(int error, char guessed[MAX_CHARS]) {
    printf("  ____\n");
    printf(" |    |\n");
    printf(" |    ");
    if (error >= 1) printf("o");
    printf("\n |   ");
    if (error >= 5) printf("/|");
    if (error >= 2 && error <= 4) printf(" |");
    if (error >= 6) printf("\\");
    printf("\n |   ");
    if (error >= 3) printf("/");
    if (error >= 4) printf(" \\");
    printf("\n---\n\n");
        for (int i=0;i<strlen(guessed);i++) {
            printf("%c ", guessed[i]);
        }
        printf("\n\n");
}

int logic(char word[MAX_CHARS], char guessed[MAX_CHARS], char letterBank[MAX_CHARS], char guess) {
    letterBank[guess-'A'] = guess;
    if (check(word, guess)) {
        guessed[check(word, guess)-1] = guess;
        return 0;
    }
    return 1;
}

int check(char word[MAX_CHARS], char guess) {
    for (int i=0;i<strlen(word);i++) {
        if (guess == word[i]) {
            return i+1;
        }
    }
    return 0;
}
