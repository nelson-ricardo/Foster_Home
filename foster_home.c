#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* suffix;       // suffix to add to cat's name
    int currentCage;    // current cage index
    int numCagesFwd;    // number of cages the family will move forward
    int hasCat;         // 1 for true, 0 for false
} FosterFamily;

int addKitties(char* array[], int numIndex);

int main() {
    int numOfCages, numOfWeeks;

    char buffer;

    scanf("%d %d\n", &numOfCages, &numOfWeeks); //gets the number of cages and number of weeks

    //TODO: check that numOfCages is between 3 an 500 and that numOfWeeks is between 1 and 500
    if((numOfCages < 3 || numOfCages > 500) || (numOfWeeks < 1 || numOfWeeks > 500)) {
        return 1;
    }

    char* arrayOfKitties[numOfCages];

    int completeFlag = addKitties(arrayOfKitties, numOfCages);

    if(completeFlag) return 1; // stops the program if the cat's name is longer than 19


    FosterFamily FamilyArray[3] = {
            {"Lee", 0, 2, 1}, // family1
            {"Lyn", 1, 3, 1}, // family2
            {"Eve", 2, 5, 1}  // family3
    };

    for(int i = 1; i < numOfWeeks; i++) {
        for(int j = 0; j < 3; j++) {
            
            // add the suffix of the family to the cat's name if the family has the cat
            if(FamilyArray[j].hasCat) {
                int currentKitty = FamilyArray[j].currentCage;

                char newCatName[strlen(arrayOfKitties[currentKitty] + 3)];

                strcpy(newCatName, arrayOfKitties[currentKitty]);

                arrayOfKitties[currentKitty] = strcat(newCatName, FamilyArray[j].suffix);

                printf("%s\n", arrayOfKitties[FamilyArray[j].currentCage]);
            }
            

            int famCurrentCage = FamilyArray[j].currentCage;
            FamilyArray[j].currentCage = (famCurrentCage + FamilyArray[j].numCagesFwd) % numOfCages;
        }
    }

    // TODO: update the name of the kitty to add the suffix 
    // TODO: add logic to verify that the cat is not taken by someone else 

    return 0;
}


int addKitties(char* array[], int numIndex) {


    for(int i = 0; i < numIndex; i++) {
        char* tempKitty = malloc(sizeof(char*));
        // TODO: add logic to not allow a name longer than 19 characters
        scanf("%s", tempKitty);

        if(strlen(tempKitty) > 19) {
            return 1;
        }
        array[i] = tempKitty;
    }

    return 0;
}

