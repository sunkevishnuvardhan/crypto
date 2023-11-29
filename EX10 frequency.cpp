#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Function to calculate letter frequency in the given text
void calculateFrequency(char *text, int frequency[ALPHABET_SIZE]) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            frequency[tolower(text[i]) - 'a']++;
        }
    }
}

// Function to perform additive decryption using a key
void decrypt(char *ciphertext, int key, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = (ciphertext[i] - base - key + ALPHABET_SIZE) % ALPHABET_SIZE + base;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

// Function to print the top N possible plaintexts based on letter frequency
void printTopPlaintexts(char *ciphertext, int topN) {
    int frequency[ALPHABET_SIZE] = {0};
    calculateFrequency(ciphertext, frequency);

    // Guess keys based on the frequency of letters in English
    for (int key = 0; key < ALPHABET_SIZE; key++) {
        char plaintext[strlen(ciphertext) + 1];
        decrypt(ciphertext, key, plaintext);

        printf("Key: %d, Plaintext: %s\n", key, plaintext);
    }
}

int main() {
    char ciphertext[1000];
    int topN;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; // Remove newline character

    printf("Enter the top N possible plaintexts to display: ");
    scanf("%d", &topN);

    printf("\nTop %d possible plaintexts:\n", topN);
    printTopPlaintexts(ciphertext, topN);

    return 0;
}

