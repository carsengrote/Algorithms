#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <inttypes.h>

struct job{
    long long s;
    long long f;
    long long v;
};

int compFunc(const void * a, const void* b){

    struct job * jobA = (struct job *)a;
    struct job * jobB = (struct job *)b;

   return (jobA->f - jobB->f);

}

int main(int argc, char **argv){

    char * buf = NULL;
    size_t len = 0;
    getline(&buf, &len, stdin);
    int instances  = atoi(buf);
    char * token;
    
    for (int instance = 0; instance < instances; instance ++){

        getline(&buf, &len, stdin);
        long long  numJobs;
        numJobs = atoll(buf);
        
        struct job * jobs = (struct job *)malloc(sizeof(struct job)* (numJobs));
        long long currRequest = 0;
        long long s;
        long long f;
        long long v;

        while (currRequest < numJobs){

            getline(&buf, &len, stdin);
            s = atoll(strtok(buf, " "));
            f = atoll(strtok(NULL, " "));
            v = atoll(strtok(NULL, " "));

            jobs[currRequest].s = s;
            jobs[currRequest].f = f;
            jobs[currRequest].v = v;
            currRequest++;
        }

        qsort(jobs, numJobs, sizeof(struct job), compFunc);

        long long * Bellman = malloc(sizeof(long long) * (numJobs + 1));
        Bellman[0] = 0;

        for (int index  = 1; index <= numJobs; index++){

            long long jobStartTime = jobs[index - 1].s;
            long long largestCompatibleIndex = 0;
            int found = 0;
            long long j = index - 2;
            
            while(found == 0 && j >=0){
                if (jobs[j].f <= jobStartTime){
                    largestCompatibleIndex = j + 1;
                    found = 1;
                }
                j--;
            }

            if (Bellman[index - 1] >= Bellman[largestCompatibleIndex] + jobs[index - 1].v){
                Bellman[index] = Bellman[index - 1];
            }else{
                Bellman[index] = Bellman[largestCompatibleIndex] + jobs[index - 1].v;
            }
        }

        printf("%lld\n", Bellman[numJobs]);
        free(jobs);
        free(Bellman);
    }

}
