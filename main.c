// Paweł Reliński
// Krystian Rożnawski
// Projekt 18. Szyfrowanie (2 osoby)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

void caesarCipher(char* plainText, int shift, char* cipherText);
void caesarDecipher(char* cipherText, int shift, char* plainText);

void vernamCipher(char* plainText, char* key, char* cipherText);
void vernamDecipher(char* cipherText, char* key, char* plainText);

void vigenereCipher(char* key, char* text, int encrypt);
void encryptVigenereCipher(char* text);
void decryptVigenereCipher(char* text);

void beaufortCipher(char* key, char* text);
void encryptBeaufortCipher(char* text);
void decryptBeaufortCipher(char* text);

int main() {
    char plainText[1000];
    char cipherText[1000];
    int shift = 3;
    FILE *inputFile, *outputFile;
    char inputPath[1000];
    int choice;
    char key[] = "SOMEKEY";  // klucz dla szyfru Vernama
    bool isDecipher = true; // jezeli chcemy uzyc odszyfrowania ustawić na true
    int decipherChoice;

    printf("Podaj ścieżkę do pliku do zaszyfrowania: ");
    scanf("%s", inputPath);
    printf("\n");

    inputFile = fopen(inputPath, "r");
    if (inputFile == NULL) {
        printf("Nie mogę otworzyć pliku.\n");
        return 1;
    }

    printf("Wybierz szyfr:\n1. Szyfr Cezara\n2. Szyfr Vernama\n3. Szyfr Vigenère'a\n4. Szyfr Beauforta\nWybór: ");
    scanf("%d", &choice);

    fgets(plainText, 1000, inputFile);

    // szyfrowanie
    switch(choice) {
        case 1:
            caesarCipher(plainText, shift, cipherText);
            break;
        case 2:
            vernamCipher(plainText, key, cipherText);
            break;
        case 3:
            encryptVigenereCipher(plainText);
            strcpy(cipherText, plainText);
            break;
        case 4:
            encryptBeaufortCipher(plainText);
            strcpy(cipherText, plainText);
            break;
        default:
            printf("Niepoprawny wybór.\n");
            return 1;
    }

    outputFile = fopen("cipherContent.txt", "w");
    if (outputFile == NULL) {
        printf("Nie mogę otworzyć pliku.\n");
        return 1;
    }

    fputs(cipherText, outputFile);
    fclose(outputFile);
    printf("\nSzyfrowanie powiodlo sie oraz tekst znajduje się w pliku cipherContent.txt\n \n");

    printf("Czy chcesz odszyfrować plik i go zapisać w nowym pliku:\n1. Tak\n2. Nie\nWybór: ");
    scanf("%d", &decipherChoice);

    if (decipherChoice == 1) {
        isDecipher = true;
    } else if (decipherChoice == 2) {
        isDecipher = false;
    } else {
        printf("Niepoprawny wybór.\n");
        return 1;
    }

    // odszyfrowanie
    if (isDecipher == true) {
        if (choice == 1) {
            char decipherText[1000];
            caesarDecipher(cipherText, shift, decipherText);

            outputFile = fopen("decipherContent.txt", "w");
            if (outputFile == NULL) {
                printf("Nie mogę otworzyć pliku.\n");
                return 1;
            }

            fputs(decipherText, outputFile);

            fclose(inputFile);
            fclose(outputFile);
            printf("\nOdszyfrowanie powiodlo sie oraz tekst znajduje się w pliku decipherContent.txt\n");
        } else if (choice == 2) {
            char decipherText[1000];
            vernamDecipher(cipherText, key, decipherText);

            outputFile = fopen("decipherContent.txt", "w");
            if (outputFile == NULL) {
                printf("Nie mogę otworzyć pliku.\n");
                return 1;
            }

            fputs(decipherText, outputFile);

            fclose(inputFile);
            fclose(outputFile);
            printf("\nOdszyfrowanie powiodlo sie oraz tekst znajduje się w pliku decipherContent.txt\n");
        } else if (choice == 3) {
            char decipherText[1000];
            decryptVigenereCipher(cipherText);
            strcpy(decipherText, cipherText);

            outputFile = fopen("decipherContent.txt", "w");
            if (outputFile == NULL) {
                printf("Nie mogę otworzyć pliku.\n");
                return 1;
            }

            fputs(decipherText, outputFile);

            fclose(inputFile);
            fclose(outputFile);
            printf("\nOdszyfrowanie powiodlo sie oraz tekst znajduje się w pliku decipherContent.txt\n");
        } else if (choice == 4) {
            char decipherText[1000];
            decryptBeaufortCipher(cipherText);
            strcpy(decipherText, cipherText);

            outputFile = fopen("decipherContent.txt", "w");
            if (outputFile == NULL) {
                printf("Nie mogę otworzyć pliku.\n");
                return 1;
            }

            fputs(decipherText, outputFile);

            fclose(inputFile);
            fclose(outputFile);
            printf("\nOdszyfrowanie powiodlo sie oraz tekst znajduje się w pliku decipherContent.txt\n");
        }
    }

    return 0;
}

void caesarCipher(char* plainText, int shift, char* cipherText) {
    int i = 0;
    while(plainText[i] != '\0') {
        char letter = plainText[i];
        if(letter == ' '){
            cipherText[i] = ' ';
        } else if(letter >= 'a' && letter <= 'z'){
            letter = letter + shift;
            if(letter > 'z') {
                letter = letter - 'z' + 'a' - 1;
            }
            cipherText[i] = letter;
        } else if(letter >= 'A' && letter <= 'Z') {
            letter = letter + shift;
            if(letter > 'Z') {
                letter = letter - 'Z' + 'A' - 1;
            }
            cipherText[i] = letter;
        }
        i++;
    }
    cipherText[i] = '\0';  // end of string
}

void caesarDecipher(char* cipherText, int shift, char* plainText) {
    int i = 0;
    while(cipherText[i] != '\0') {
        char letter = cipherText[i];
        if(letter == ' '){
            plainText[i] = ' ';
        } else if(letter >= 'a' && letter <= 'z'){
            letter = letter - shift;
            if(letter < 'a') {
                letter = letter + 'z' - 'a' + 1;
            }
            plainText[i] = letter;
        } else if(letter >= 'A' && letter <= 'Z') {
            letter = letter - shift;
            if(letter < 'A') {
                letter = letter + 'Z' - 'A' + 1;
            }
            plainText[i] = letter;
        }
        i++;
    }
    plainText[i] = '\0';  // end of string
}

void vernamCipher(char* plainText, char* key, char* cipherText) {
    int i;
    for(i = 0; i < strlen(plainText); i++) {
        cipherText[i] = plainText[i] ^ key[i % strlen(key)];
    }
    cipherText[i] = '\0';
}

void vernamDecipher(char* cipherText, char* key, char* plainText) {
    // operacja XOR jest odwracalna, więc używamy tej samej funkcji
    vernamCipher(cipherText, key, plainText);
}

void vigenereCipher(char* key, char* text, int encrypt) {
    int key_len = strlen(key);
    int text_len = strlen(text);
    
    for(int i = 0; i < text_len; ++i) {
        char c = text[i];
        if(isalpha(c)) {
            char offset = islower(c) ? 'a' : 'A';
            int key_shift = tolower(key[i % key_len]) - 'a';
            int text_shift = c - offset;
            int new_shift = (text_shift + (encrypt ? key_shift : 26 - key_shift)) % 26;
            text[i] = new_shift + offset;
        }
    }
}

void encryptVigenereCipher(char* text) {
    char key[] = "aghiie";
    vigenereCipher(key, text, 1);
}

void decryptVigenereCipher(char* text) {
    char key[] = "aghiie";
    vigenereCipher(key, text, 0);
}

void beaufortCipher(char* key, char* text) {
    int key_len = strlen(key);
    int text_len = strlen(text);
    
    for(int i = 0; i < text_len; ++i) {
        char c = text[i];
        if(isalpha(c)) {
            char offset = islower(c) ? 'a' : 'A';
            int key_shift = tolower(key[i % key_len]) - 'a';
            int text_shift = c - offset;
            int new_shift = (key_shift - text_shift + 26) % 26;
            text[i] = new_shift + offset;
        }
    }
}

void encryptBeaufortCipher(char* text) {
    char key[] = "aghiie";
    beaufortCipher(key, text);
}

void decryptBeaufortCipher(char* text) {
    char key[] = "aghiie";
    beaufortCipher(key, text);
}