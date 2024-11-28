#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define MAX_TEXT_LENGTH 128
#define KEY_LENGTH 16

void keygen(int key[], int size) {
    srand(time(NULL));
    for (int z = 0; z < size; z++) {
        key[z] = rand() % 2;
    }
}

void extendtxt(char *text, size_t max_length){
    size_t len = strlen(text);
    if (len < max_length){
        for (size_t i = len; i < max_length; i++) {
            text[i] = '\0';
        }
        text[max_length] = '\0';
    }
}

void xor(char *text, int key[], int key_size){
    size_t len = strlen(text);
    for (size_t i = 0; i < len; i++) {
        int key_bit = key[i % key_size];
        text[i] ^= key_bit ? 0xFF : 0x00;
    }
}

void print_bits(char *text) {
    size_t len = strlen(text);
    for (size_t i = 0; i < len; i++) {
        unsigned char byte = text[i];
        for (int j = 7; j >= 0; j--) {
            printf("%d", (byte >> j) & 1);
        }
        printf(" ");
    }
    printf("\n");
}

int main() {
    char toencrypt[MAX_TEXT_LENGTH + 1] = "";
    char buffer[256];
    FILE *file = fopen("PFAD HINZUFÜGEN", "r");
    if (file == NULL) {
        printf("Fehler beim lesen der Client-Datei.\n");
        return 1;
    } else {
        while (fgets(buffer, sizeof(buffer), file) != NULL){
            strcat(toencrypt, buffer);
        }
        fclose(file);
    }


    for (size_t i = 0; i < strlen(toencrypt); i++) {
        if (toencrypt[i] < 0 || toencrypt[i] > 127) {
            printf("Zeichen sind nicht Teil der ASCII-Tabelle, bitte versuchen Sie es erneut.\n");
            return 1;
        }
    }

    int key[16];
    keygen(key, 16);

    extendtxt(toencrypt, MAX_TEXT_LENGTH);

    xor(toencrypt, key, KEY_LENGTH);

    print_bits(toencrypt);

    return 0;
}
