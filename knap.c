#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <inttypes.h>

struct item{
    long long v;
    long long w;
};

int main(int argc, char **argv){
    char * buf = NULL;
    size_t len = 0;
    getline(&buf, &len, stdin);
    long long instances  = atoll(buf);
    char * token;
    
    for (long long instance = 0; instance < instances; instance ++){

        getline(&buf, &len, stdin);
        long long numItems;
        long long capacity;
        numItems = atoll(strtok(buf, " "));
        capacity = atoll(strtok(NULL, " "));
        
        struct item * items = (struct item *) malloc(sizeof(struct item)* (numItems + 1));
        long long currRequest = 1;
        long long v;
        long long w;

        while (currRequest <  (numItems + 1)){

            getline(&buf, &len, stdin);
            w = atoll(strtok(buf, " "));
            v = atoll(strtok(NULL, " "));

            items[currRequest].v = v;
            items[currRequest].w = w;
            currRequest++;
        }

        long long ** Bellman = (long long **) malloc(sizeof(long long *) * (numItems + 1));
        
        for (long long i = 0; i < numItems  + 1; i ++){
            Bellman[i] = (long long *) malloc(sizeof(long long) * (capacity + 1));
            Bellman[i][0] = 0;
            Bellman[0][i] = 0;
        }

        int weightSwitch;

        for (long long currItem  = 1; currItem < numItems + 1; currItem++){

            for (long long currCapacity = 1; currCapacity < capacity + 1; currCapacity++){
                
                weightSwitch = 0;
                if (items[currItem].w <= currCapacity){
                    weightSwitch = 1;
                } 

                if (weightSwitch == 0 || (Bellman[currItem - 1][currCapacity] >= (Bellman[currItem - 1][currCapacity - items[currItem].w] + items[currItem].v))){
                    Bellman[currItem][currCapacity] = Bellman[currItem - 1][currCapacity];
                } else{
                    Bellman[currItem][currCapacity] = (Bellman[currItem - 1][currCapacity - items[currItem].w] + items[currItem].v);
                }

            }
        }

        printf("%lld\n", Bellman[numItems][capacity]);

        //for (long long i = 0; i < numItems + 1; i ++){
        //    free(Bellman[i]);
        //}
        //free(Bellman);
        //free(items);
    }

}
