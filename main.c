#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void caesarCipher(char* plainText, int shift, char* cipherText);
void caesarDecipher(char* cipherText, int shift, char* plainText);
void vernamCipher(char* plainText, char* key, char* cipherText);
void vernamDecipher(char* cipherText, char* key, char* plainText);

int main() {
    char plainText[1000];
    char cipherText[1000];
    int shift = 3;
    FILE *inputFile, *outputFile;
    char inputPath[1000];
    int choice;
    char key[] = "SOMEKEY";  // klucz dla szyfru Vernama
    bool isDecipher = false; // jezeli chcemy uzyc odszyfrowania ustawić na true

    printf("Podaj ścieżkę do pliku do zaszyfrowania: ");
    scanf("%s", inputPath);

    printf("Wybierz szyfr:\n1. Szyfr Cezara\n2. Szyfr Vernama\nWybór: ");
    scanf("%d", &choice);

    inputFile = fopen(inputPath, "r");
    if (inputFile == NULL) {
        printf("Nie mogę otworzyć pliku.\n");
        return 1;
    }

    fgets(plainText, 1000, inputFile);

    switch(choice) {
        case 1:
            caesarCipher(plainText, shift, cipherText);
            break;
        case 2:
            vernamCipher(plainText, key, cipherText);
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
    printf("\nSzyfrowanie powiodlo sie oraz tekst znajduje się w pliku cipherContent.txt\n");

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

