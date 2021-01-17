#include <stdio.h>

// Aufgabe 2 a)
/*
int main(void) {
    char text[101] = { 0 };
    printf("Verschlüsselten Text eingeben\n");
    scanf(" %100s", text); // besser wäre "fgets(text, 100, stdin)", da scanf keine Leerzeichen erlaubt

    int key = 0;
    printf("Schlüssel eingeben\n");
    scanf(" %i", &key);

    for (int i = 0; text[i] != 0; i++) {
        char enc = text[i];
        if (0x41 <= enc && enc <= 0x5A) { // Großbuchstaben
            if (enc - key < 0x41) { // Underflow
                text[i] = enc - key + 26;
            } else if (enc - key > 0x5A) { // Overflow
                text[i] = enc - key - 26;
            }  else {
                text[i] = enc - key;
            }
        } else if (0x61 <= enc && enc <= 0x7A) { // Kleinbuchstaben
            if (enc - key < 0x61) { // Underflow
                text[i] = enc - key + 26;
            } else if (enc - key > 0x7A) { // Overflow
                text[i] = enc - key - 26;
            } else {
                text[i] = enc - key;
            }
        }
    }

    printf("Entschlüsselter Text: %s\n", text);
}
*/

// Aufgabe 2 b)
int main(void) {
    int mode = 0;
    while (!(mode == 1 || mode == 2)) {
        printf("Modus auswählen\n");
        printf("\t1: Entschlüsseln\n");
        printf("\t2: Verschlüsseln\n");
        scanf(" %i", &mode);
    }

    char text[101] = { 0 };
    if (mode == 1) {
        printf("Verschlüsselten Text eingeben\n");
    } else {
        printf("Zu verschlüsselnden Text eingeben\n");
    }
    scanf(" %100s", text);

    int key = 0;
    printf("Schlüssel eingeben\n");
    scanf(" %i", &key);

    if (mode == 2) {
        key = -key;
    }

    for (int i = 0; text[i] != 0; i++) {
        char enc = text[i];
        if (0x41 <= enc && enc <= 0x5A) {
            if (enc - key < 0x41) {
                text[i] = enc - key + 26;
            } else if (enc - key > 0x5A) {
                text[i] = enc - key - 26;
            }  else {
                text[i] = enc - key;
            }
        } else if (0x61 <= enc && enc <= 0x7A) {
            if (enc - key < 0x61) {
                text[i] = enc - key + 26;
            } else if (enc - key > 0x7A) {
                text[i] = enc - key - 26;
            } else {
                text[i] = enc - key;
            }
        }
    }

    if (mode == 1) {
        printf("Entschlüsselter Text: %s\n", text);
    } else {
        printf("Verschlüsselter Text: %s\n", text);
    }
}

