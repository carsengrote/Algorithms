#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <inttypes.h>

struct line{
    int p;
    int q;
};

int compFunc(const void * a, const void* b){

    struct line * lineA = (struct line *)a;
    struct line * lineB = (struct line *)b;

   return (lineA->p - lineB->p);

}

long long mergeCount(struct line * frontHalf, struct line * backHalf, int frontSize, int backSize, struct line * combinedArray){

    int frontIndex = 0;
    int backIndex = 0;
    int diff;
    long long inversionCount = 0;
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

        diff = frontHalf[frontIndex].q - backHalf[backIndex].q;

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

long long countSort(struct line * A, int * size, struct line * combinedArray){

    if (*size == 1){
        combinedArray[0] = A[0];
        return 0;
    }

    struct line * frontHalf;
    struct line * backHalf;
    int * frontSize = (int *) malloc(sizeof(int));
    int * backSize = (int *) malloc(sizeof(int));

   frontHalf = (struct line *) malloc(sizeof(struct line) * (*size / 2));
   *frontSize = (*size / 2);

   if (*size % 2 == 1){
       backHalf = (struct line *) malloc(sizeof(struct line)* ((*size / 2) + 1) );
       *backSize = (*size / 2) + 1;
   }else{
       backHalf = (struct line *) malloc(sizeof(struct line) * (*size / 2));
       *backSize = (*size / 2);
   }

   for(int index = 0; index < *size; index++){
       if (index < (*size / 2)){
           frontHalf[index] = A[index];
       }else{
           backHalf[index - (*size / 2)] = A[index];
       }
   }

    struct line * combinedFront = (struct line *) malloc(sizeof(struct line) * (*frontSize));
    struct line * combinedBack = (struct line *) malloc(sizeof(struct line) * (*backSize));

    long long frontInversionsCount = countSort(frontHalf, frontSize, combinedFront);
    long long backInversionsCount = countSort(backHalf, backSize, combinedBack);

    long long totalInversions = 0;

    long long c = mergeCount(combinedFront, combinedBack, *frontSize, *backSize, combinedArray);

    totalInversions = c + frontInversionsCount + backInversionsCount;

    free(frontHalf);
    free(backHalf);
    free(combinedFront);
    free(combinedBack);
    
    return(totalInversions);
}


int main(int argc, char **argv){

    char * buf = NULL;
    size_t len = 0;
    getline(&buf, &len, stdin);
    int instances  = atoi(buf);
    char * token;
    
    for (int instance = 0; instance < instances; instance ++){

        getline(&buf, &len, stdin);

        int * numElements = (int *) malloc(sizeof(int));
        *numElements = atoi(buf);
        
        struct line * lines = (struct line *)malloc(sizeof(struct line)* (*numElements));
        int currRequest = 0;
        int p;
        int q;
        struct line currLine;
        while (currRequest < *numElements){
            getline(&buf, &len, stdin);
            p = atoi(buf);
            currLine = lines[currRequest];
            lines[currRequest].p = p;
            currRequest++;
        }

        currRequest = 0;
        while(currRequest < *numElements){
            getline(&buf, &len, stdin);
            q = atoi(buf);
            lines[currRequest].q = q;
            currRequest++;
        }

        qsort(lines, *numElements, sizeof(struct line), compFunc);

        struct line * combined = (struct line *) malloc(sizeof(struct line) * (*numElements));

        long long totalCount = countSort(lines, numElements, combined);

        free(lines);
        free(numElements);

        printf("%lld\n", totalCount);
    }

}
