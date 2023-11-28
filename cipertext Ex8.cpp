#include <stdio.h>

#define ALPHABET_SIZE 26

int isValidCharacter(char c) {
    return (c >= 'A' && c <= 'Z');
}


void countFrequency(char ciphertext[], int frequency[]) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isValidCharacter(ciphertext[i])) {
            frequency[ciphertext[i] - 'A']++;
        }
    }
}


void findMostFrequentCharacters(char ciphertext[], char* mostFrequent, char* secondMostFrequent) {
    int frequency[ALPHABET_SIZE] = {0};
    countFrequency(ciphertext, frequency);

    int maxFrequency = 0;
    int maxFrequencyIndex = -1;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (frequency[i] > maxFrequency) {
            maxFrequency = frequency[i];
            maxFrequencyIndex = i;
        }
    }

    *mostFrequent = maxFrequencyIndex + 'A';
    frequency[maxFrequencyIndex] = 0;

    int secondMaxFrequency = 0;
    int secondMaxFrequencyIndex = -1;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (frequency[i] > secondMaxFrequency) {
            secondMaxFrequency = frequency[i];
            secondMaxFrequencyIndex = i;
        }
    }

    *secondMostFrequent = secondMaxFrequencyIndex + 'A';
}


void decryptAffineCipher(char ciphertext[], char plaintext[], int a, int b) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isValidCharacter(ciphertext[i])) {
            int plainTextIndex = (a * (ciphertext[i] - 'A') + b) % ALPHABET_SIZE;
            plaintext[i] = plainTextIndex + 'A';
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
}

int main() {
    char ciphertext[100];
    printf("Enter the ciphertext: ");
    scanf("%s", ciphertext);

    char mostFrequent, secondMostFrequent;
    findMostFrequentCharacters(ciphertext, &mostFrequent, &secondMostFrequent);

 
    int a = (secondMostFrequent - mostFrequent) % ALPHABET_SIZE;
    int b = (mostFrequent + ALPHABET_SIZE - 'E') % ALPHABET_SIZE;

    char plaintext[100];
    decryptAffineCipher(ciphertext, plaintext, a, b);

    printf("Decrypted plaintext: %s\n", plaintext);

    return 0;
}
