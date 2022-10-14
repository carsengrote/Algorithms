#include <string>
#include <iostream>
#include <string.h>
using namespace std;

int mergeCount(int * frontHalf, int * backHalf, int frontSize, int backSize, int * combinedArray){

    int frontIndex = 0;
    int backIndex = 0;
    int diff;
    int inversionCount = 0;
    int combinedIndex = 0;

    while ((frontIndex < frontSize) || (backIndex < backSize)){

        if (frontIndex == frontSize){
            combinedArray[combinedIndex] = backHalf[backIndex];
            combinedIndex++;
            backIndex++;
            continue;
        }
        if (backIndex == backSize){
            combinedArray[combinedIndex] = frontHalf[frontIndex];
            frontIndex++;
            combinedIndex++;
            continue;
        }

        diff = frontHalf[frontIndex] - backHalf[backIndex];

        if (diff > 0){
            inversionCount = inversionCount + (frontSize - frontIndex);
            combinedArray[combinedIndex] = backHalf[backIndex];
            backIndex ++;
        }else{
            combinedArray[combinedIndex] = frontHalf[frontIndex];
            frontIndex++;
        }

        combinedIndex++;
    }

    return(inversionCount);
}

int countSort(int * A, int * size, int *combinedArray){

    if (*size == 1){
        combinedArray[0] = A[0];
        return 0;
    }

    int * frontHalf;
    int * backHalf;
    int * frontSize = (int *) malloc(sizeof(int));
    int * backSize = (int *) malloc(sizeof(int));

   frontHalf = (int *) malloc(sizeof(int) * (*size / 2));
   *frontSize = (*size / 2);

   if (*size % 2 == 1){
       backHalf = (int *) malloc(sizeof(int)* ((*size / 2) + 1) );
       *backSize = (*size / 2) + 1;
   }else{
       backHalf = (int *) malloc(sizeof(int) * (*size / 2));
       *backSize = (*size / 2);
   }

   for(int index = 0; index < *size; index++){
       if (index < (*size / 2)){
           frontHalf[index] = A[index];
       }else{
           backHalf[index - (*size / 2)] = A[index];
       }
   }

    int * combinedFront = (int *) malloc(sizeof(int) * (*frontSize));
    int * combinedBack = (int *) malloc(sizeof(int) * (*backSize));

    int frontInversionsCount = countSort(frontHalf, frontSize, combinedFront);
    int backInversionsCount = countSort(backHalf, backSize, combinedBack);

    int totalInversions = 0;

    int c = mergeCount(combinedFront, combinedBack, *frontSize, *backSize, combinedArray);

    totalInversions = c + frontInversionsCount + backInversionsCount;

    free(frontHalf);
    free(backHalf);
    free(combinedFront);
    free(combinedBack);
    
    return(totalInversions);
}

int main(int argc, char **argv){

    string line = "";
    getline(cin, line);
    int instances  = stoi(line);
    string currLine;
    string elements;
    char * token;
    
    for (int instance = 0; instance < instances; instance ++){

        currLine = "";
        elements = "";
        getline(cin, currLine);

        int * numElements = (int *) malloc(sizeof(int));
        *numElements = stoi(currLine);

        getline(cin, elements);

        token = NULL;
        token = strtok(&(elements[0])," ");
        
        int * elementsArray = (int *)malloc(sizeof(int)* (*numElements));
        int currRequest = 0;

        while (currRequest < *numElements){
            elementsArray[currRequest] = stoi(token);
            token = strtok(NULL, " ");
            currRequest++;
        }

        int *combinedArray = (int *) malloc(sizeof(int) * (*numElements));

        int totalInversions = countSort(elementsArray, numElements, combinedArray);

        free(elementsArray);
        free(numElements);
        free(combinedArray);

        printf("%d\n", totalInversions);
    }

}
