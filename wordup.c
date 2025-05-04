// Andrew Kranz
//Project 10 Word up
// May the 4th be with u

#include <stdio.h>
#include <stdbool.h>
#define FILENAME "word.txt"

#define MAX_WORD_LENGTH 6 
#define MAX_ATTEMPTS 6

// Function prototypes
void loadMysteryWord(char *mysteryWord);
void displayPreviousGuesses(char guesses[][MAX_WORD_LENGTH], char feedback[][MAX_WORD_LENGTH], int currentAttempt);
bool validateGuess(const char *guess);
void processGuess(const char *guess, const char *mysteryWord, char *feedback);
void toLowerCase(char *str);
void displayResult(bool won, const char *mysteryWord, int attempts);
int myStrlen(const char *str);
int myStrcmp(const char *s1, const char *s2);
void myStrcpy(char *dest, const char *src);
bool isAlpha(char c);
char toUpper(char c);
char toLower(char c);

int main() {
    char mysteryWord[MAX_WORD_LENGTH];
    char guesses[MAX_ATTEMPTS][MAX_WORD_LENGTH];
    char feedback[MAX_ATTEMPTS][MAX_WORD_LENGTH];
    char guess[MAX_WORD_LENGTH];
    int attempts = 0;
    bool gameWon = false;

    loadMysteryWord(mysteryWord);
    
    printf("Welcome to Wordle!\n");
    printf("Try to guess the 5-letter word. You have 6 attempts.\n");
    
    while (attempts < MAX_ATTEMPTS && !gameWon) {

        displayPreviousGuesses(guesses, feedback, attempts);
        

        printf("\nAttempt %d/%d\n", attempts + 1, MAX_ATTEMPTS);
        printf("Enter your guess: ");
        scanf("%5s", guess);
        
        toLowerCase(guess);
        
        if (!validateGuess(guess)) {
            printf("Invalid guess! Please enter a 5-letter word with only letters.\n");
            continue;
        }
        
        myStrcpy(guesses[attempts], guess);
        
        processGuess(guess, mysteryWord, feedback[attempts]);
        
        if (myStrcmp(guess, mysteryWord) == 0) {
            gameWon = true;
        }
        
        attempts++;
    }
    
    displayResult(gameWon, mysteryWord, attempts);
    
    return 0;
}

int myStrlen(const char *str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

int myStrcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

void myStrcpy(char *dest, const char *src) {
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0';
}

bool isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

char toUpper(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 32;
    }
    return c;
}

char toLower(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + 32;
    }
    return c;
}

void loadMysteryWord(char *mysteryWord) {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", FILENAME);
        mysteryWord[0] = 'h';
        mysteryWord[1] = 'e';
        mysteryWord[2] = 'l';
        mysteryWord[3] = 'l';
        mysteryWord[4] = 'o';
        mysteryWord[5] = '\0';
        return;
    }
    
    fscanf(file, "%5s", mysteryWord);
    fclose(file);
    
    toLowerCase(mysteryWord);
}

void toLowerCase(char *str) {
    int i = 0;
    while (str[i]) {
        str[i] = toLower(str[i]);
        i++;
    }
}

void displayPreviousGuesses(char guesses[][MAX_WORD_LENGTH], char feedback[][MAX_WORD_LENGTH], int currentAttempt) {
    if (currentAttempt == 0) {
        return; 
    }
    
    printf("\nYour previous guesses:\n");
    for (int i = 0; i < currentAttempt; i++) {
        printf("%d. ", i + 1);
        
        for (int j = 0; j < 5; j++) {
            if (feedback[i][j] == '*') {
                printf("[%c]", toUpper(guesses[i][j]));
            } else if (feedback[i][j] == '^') {
                printf("^%c", guesses[i][j]);
            } else {
                printf(" %c ", guesses[i][j]);
            }
        }
        printf("\n");
    }
}

bool validateGuess(const char *guess) {
    if (myStrlen(guess) != 5) {
        return false;
    }
    
    for (int i = 0; i < 5; i++) {
        if (!isAlpha(guess[i])) {
            return false;
        }
    }
    
    return true;
}


void processGuess(const char *guess, const char *mysteryWord, char *feedback) {
    bool letterUsed[5] = {false, false, false, false, false};
    
    for (int i = 0; i < 5; i++) {
        feedback[i] = ' ';
    }
    feedback[5] = '\0';
    
    for (int i = 0; i < 5; i++) {
        if (guess[i] == mysteryWord[i]) {
            feedback[i] = '*';
            letterUsed[i] = true;
        }
    }
    
   
    for (int i = 0; i < 5; i++) {
        if (feedback[i] == ' ') { 
            for (int j = 0; j < 5; j++) {
                if (!letterUsed[j] && i != j && guess[i] == mysteryWord[j]) {
                    feedback[i] = '^';
                    letterUsed[j] = true;
                    break;
                }
            }
        }
    }
}


void displayResult(bool won, const char *mysteryWord, int attempts) {
    printf("\n");
    if (won) {
        printf("Congratulations! You guessed the word in %d attempts!\n", attempts);
    } else {
        printf("Game over! You've used all your attempts.\n");
        printf("The mystery word was: %s\n", mysteryWord);
    }
}

