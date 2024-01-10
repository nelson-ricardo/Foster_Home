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
int getKittyOwnership(FosterFamily newFamily, FosterFamily otherFam1, FosterFamily otherFam2);

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

            int currentCage = FamilyArray[j].currentCage;
            
            // add the suffix of the family to the cat's name if the family has the cat
            if(FamilyArray[j].hasCat) {

                char *newCatName = (char* ) calloc(strlen(arrayOfKitties[currentCage]) + 3, sizeof(char));

                strcpy(newCatName, arrayOfKitties[currentCage]);

                arrayOfKitties[currentCage] = strcat(newCatName, FamilyArray[j].suffix);
            }
            
            FamilyArray[j].currentCage = (currentCage + FamilyArray[j].numCagesFwd) % numOfCages;

            // verify if the current family will get ownership of the new kitty
            if(j == 0) {
                FamilyArray[j].hasCat = getKittyOwnership(FamilyArray[j], FamilyArray[1], FamilyArray[2]);
            }
            else if(j == 1) {
                FamilyArray[j].hasCat = getKittyOwnership(FamilyArray[j], FamilyArray[0], FamilyArray[2]);
            }
            else {
                FamilyArray[j].hasCat = getKittyOwnership(FamilyArray[j], FamilyArray[1], FamilyArray[0]);
            }
        }
    }

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

int getKittyOwnership(FosterFamily newFamily, FosterFamily otherFam1, FosterFamily otherFam2) {
    // checks if we are on the same cage and then checks if the other family has the cat. 
    if(newFamily.currentCage == otherFam1.currentCage) {
        if(otherFam1.hasCat) {
            return 0;
        }
    } else if(newFamily.currentCage == otherFam2.currentCage) {
        if(otherFam2.hasCat) {
            return 0;
        }
    }

    return 1;
}