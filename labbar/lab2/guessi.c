#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

int main() {
    
    int num_of_tries = 1;
    char buf[255];          /* skapar 255 lådor att lägga karakärer. Går också att skriva buf[buf_siz]*/
    int buf_siz = 255;      /* en statement som säger hur stor/många lådor som finns */
    int current_guess;      /* vad vi precis skrev in som gissning*/
    srand(time(NULL));
    int correct_answer = random() % 100;           /* det korrekta svaret för rundan. mellan 0 til 100*/
    
    printf("%d\n",correct_answer);

    char *name = ask_question_string("Skriv in dit namn:", buf, buf_siz);       //frågar namn, tar in ditt namn när du skriver det, returnerar ditt namn (inte printar!! bara returnar)//

    printf("Du %s, ", name);

    current_guess = ask_question_int("jag tänker på ett tal... kan du gissa vilket?");  // current guess = funktionen tar in en fråga, läser och returnerar ett tal från tangentbord som vi fångar och sparar i current guess//
    
    while(num_of_tries < 2) {
        
        if(current_guess > correct_answer) {
            current_guess = ask_question_int("För stort!");
        }
        else if(current_guess < correct_answer) {
            current_guess = ask_question_int("För litet!");
        }
        else {
            printf("Bingo!\n");
            break; // break out of loop when correct_answer is given
        }
        
        num_of_tries++;
    }
    
    if(num_of_tries == 2) {
        printf("Nu har du slut på gissningar! Jag tänkte på %d!\n", correct_answer);
    }
    else {
        printf("Det tog %s %d gissningar att komma fram till %d!\n", name, num_of_tries, correct_answer);
    }
    return 0;
}