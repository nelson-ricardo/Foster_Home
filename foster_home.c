#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* suffix;       // suffix to add to cat's name
    int currentCage;    // current cage index
    int numCagesFwd;    // number of cages the family will move forward
    int hasCat;         // 1 for true, 0 for false
} FosterFamily;

int addCats(char* array[], int numIndex);
int getCatOwnership(FosterFamily newFamily, FosterFamily otherFam1, FosterFamily otherFam2);
void printCatCages(char* catCages[], FosterFamily families[], int numOfCages);

int main() {
    int numOfCages, numOfWeeks;

    scanf("%d %d", &numOfCages, &numOfWeeks); //gets the number of cages and number of weeks

    if((numOfCages < 3 || numOfCages > 500) || (numOfWeeks < 1 || numOfWeeks > 500)) {
        return 1;
    }

    char* catArray[numOfCages];

    int completeFlag = addCats(catArray, numOfCages);

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

                char *newCatName = (char* ) calloc(strlen(catArray[currentCage]) + 3, sizeof(char));

                strcpy(newCatName, catArray[currentCage]);

                catArray[currentCage] = strcat(newCatName, FamilyArray[j].suffix);
            }
            
            FamilyArray[j].currentCage = (currentCage + FamilyArray[j].numCagesFwd) % numOfCages;

            // verify if the current family will get ownership of the new kitty
            if(j == 0) {
                FamilyArray[j].hasCat = getCatOwnership(FamilyArray[j], FamilyArray[1], FamilyArray[2]);
            }
            else if(j == 1) {
                FamilyArray[j].hasCat = getCatOwnership(FamilyArray[j], FamilyArray[0], FamilyArray[2]);
            }
            else {
                FamilyArray[j].hasCat = getCatOwnership(FamilyArray[j], FamilyArray[1], FamilyArray[0]);
            }
        }
    } 

    printCatCages(catArray, FamilyArray, numOfCages);

    return 0;
}


int addCats(char* array[], int numIndex) {


    for(int i = 0; i < numIndex; i++) {
        char* tempCat = malloc(sizeof(char*));
        
        scanf("%s", tempCat);

        if(strlen(tempCat) > 19) {
            return 1;
        }
        array[i] = tempCat;
    }

    return 0;
}

int getCatOwnership(FosterFamily newFamily, FosterFamily otherFam1, FosterFamily otherFam2) {
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

void printCatCages(char* catCages[], FosterFamily families[], int numOfCages) {
    int numberOfOwnedCats = 0, currentIndex = 0;

    // get the number of kitties in the foster homes
    for(int i = 0; i < 3; i++) {
        if(families[i].hasCat) {
            numberOfOwnedCats++;
        }
    }

    // make an array of indexes of the kitties in the foster homes
    int ownedCatsPosition[numberOfOwnedCats];

    for(int i = 0; i < 3; i++) {
        if(families[i].hasCat) {
            ownedCatsPosition[currentIndex] = families[i].currentCage;
            currentIndex++;
        }
    }
    
    // print the cages that have kitties
    for(int i = 0; i < numOfCages; i++) {
        int found = 0;

        for(int j = 0; j < numberOfOwnedCats; j++) {
            if(ownedCatsPosition[j] == i) {
                found = 1;
                break;
            }
        }

        if(found) {
            printf("No cat found.\n");
        } else {
            printf("%s\n", catCages[i]);
        }
    }
}