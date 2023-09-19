#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 30

// Function to check if a character is a consonant (excluding case)
int isConsonant(char c) {
    c = tolower(c); // Convert the character to lowercase
    return (c >= 'b' && c <= 'z' && c != 'e' && c != 'i' && c != 'o' && c != 'u');
}

int main() {

    printf("Executed by Zhelezniak Serhii, MI-31\nWelcome to the Double Consonant Finder!\n");
    printf("Lab Task: Find only those words that have double consonant letters.\n");
    printf("The result:\n\n");

    FILE *file;
    char word[MAX_WORDS][MAX_WORD_LENGTH]; // Array to store unique words
    char resultWords[MAX_WORDS][MAX_WORD_LENGTH]; // Array to store words with double consonants
    int wordCount = 0; // Number of unique words encountered
    int resultCount = 0; // Number of words with double consonants
    char line[1000]; // Assuming each line of text can have a maximum of 1000 characters

    // Open the file for reading
    file = fopen("C:\\Users\\ks\\Desktop\\sysprog_lab1\\data.txt", "r");

    if (file == NULL) {
        printf("File could not be opened.\n");
        return 1;
    }

    while (fgets(line, sizeof(line), file)) { // Read each line from the file
        int len = strlen(line);
        int i = 0;

        while (i < len) {
            int j = 0;

            // Extract a word from the current line
            while (i < len && isalpha(line[i])) {
                if (j < MAX_WORD_LENGTH) {
                    word[wordCount][j] = tolower(line[i]); // Convert the word to lowercase
                    j++;
                }
                i++;
            }

            if (j < MAX_WORD_LENGTH) {
                word[wordCount][j] = '\0';

                // Check if the word contains double consonants
                int hasDoubleConsonants = 0;
                int wordLength = strlen(word[wordCount]);
                for (int k = 0; k < wordLength - 1; k++) {
                    if (isConsonant(word[wordCount][k]) && word[wordCount][k] == word[wordCount][k + 1]) {
                        hasDoubleConsonants = 1;
                        break; // No need to continue checking
                    }
                }

                // If the word has double consonants, add it to resultWords
                if (hasDoubleConsonants) {
                    int isNewWord = 1;
                    for (int w = 0; w < resultCount; w++) {
                        if (strcmp(word[wordCount], resultWords[w]) == 0) {
                            isNewWord = 0;
                            break;
                        }
                    }

                    if (isNewWord) {
                        strcpy(resultWords[resultCount], word[wordCount]);
                        resultCount++;
                    }
                }
            }

            // Move to the next word or non-alphabetic character
            while (i < len && !isalpha(line[i])) {
                i++;
            }
        }
    }

    // Print the result words
    printf("Words with double consonants:\n");
    for (int i = 0; i < resultCount; i++) {
        printf("%s\n", resultWords[i]);
    }

    fclose(file);
    return 0;
}
