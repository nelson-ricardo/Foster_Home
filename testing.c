#include <string.h>
#include <stdio.h>

int main() {
    char* array[] = {
        "Steve",
        "CrunchyCatLuna",
        "PrincessHoneybelle",
        "Bruce",
        "TippyToe",
        "Ili"
    };

    char tempArray[strlen(array[0]) + 3];

    strcpy(tempArray, array[0]);

    array[0] = strcat(tempArray, "Lyn");

    printf("%s\n", array[0]);
}