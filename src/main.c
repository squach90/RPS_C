// 🪨 📄 ✂️  Rock, Paper, Scissors
#include "../includes/choiceMaker.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>

#define MIN 0
#define MAX 3
char *Rock = "🪨 \033[1;38;2;102;102;102mRock\033[0m";
char *Paper = "📄 \033[1;38;2;191;191;191mPaper\033[0m";
char *Scissors = "✂️ \033[1;38;2;153;0;0mScissors\033[0m";

void press_any_key() {
    struct termios oldt, newt;

    // get actual terminal settings
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    printf("Press any key to continue...\n");
    getchar(); // wait for keys

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

int main() {
    srand(time(NULL)); // seed
    char *options[] = {Rock, Paper, Scissors};

    while (1) { // boucle du jeu
        char *choice = choice_from_array("🪨  📄 ✂️  Rock, Paper, Scissors", options, 3);

        char robotChoice[50];
        int randNum = MIN + rand() % (MAX - MIN);

        switch(randNum) {
            case 0: strcpy(robotChoice, Rock); break;
            case 1: strcpy(robotChoice, Paper); break;
            case 2: strcpy(robotChoice, Scissors); break;
        }

        printf("\033[1;38;2;0;0;255mYou\033[0m haved choose : %s\n", choice);
        printf("\033[1;38;2;153;153;0mThe robot\033[0m choose : %s\n", robotChoice);

        // ===== Logical Operation =====
        if (strcmp(robotChoice, choice) == 0) { 
            printf("\n\033[1;38;2;191;191;191mEquality\033[0m\n");
        } 
        else if ((strcmp(robotChoice, Rock) == 0 && strcmp(choice, Scissors) == 0) ||
                 (strcmp(robotChoice, Paper) == 0 && strcmp(choice, Rock) == 0) ||
                 (strcmp(robotChoice, Scissors) == 0 && strcmp(choice, Paper) == 0)) {
            printf("\n\033[1;38;2;153;0;0mYou have lost.\033[0m Bot: %s Human: %s\n", robotChoice, choice);
        }
        else {
            printf("\n\033[1;38;2;0;166;0mYou have won.\033[0m Bot: %s Human: %s\n", robotChoice, choice);
        }
        // =====       End        =====

        press_any_key();

        char *restartOptions[] = {"✅ Yes", "❌ No"};
        char *restartChoice = choice_from_array("🔄 Did you want to restart ?", restartOptions, 2);
        if (strcmp(restartChoice, "❌ No") == 0) {
            break; // exit
        }
    }

    return 0;
}
