#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <inttypes.h>

int ** adjMatrix;
int numNodes;
int * finalPath;
int finalPathSize;
int finalBottleneck;
int currCapacity;

int BFS(int * currPath, int srcNode, int * visited, int *bottleneck, int * pathSize){

    int oldBottleneck; 
    int oldPathSize;
    int originalBottleneck  = *bottleneck;

    for (int neighbor = 1; neighbor < numNodes; neighbor++){

        if (visited[neighbor] != 1 && adjMatrix[srcNode][neighbor] >= currCapacity){
            visited[neighbor] = 1;

            if ((*bottleneck < 0) || (adjMatrix[srcNode][neighbor] < *bottleneck)){
                oldBottleneck = *bottleneck;
                *bottleneck = adjMatrix[srcNode][neighbor];
            }
            currPath[*pathSize] = neighbor;
            oldPathSize = *pathSize;
            *pathSize = *pathSize + 1;
            

            if (neighbor == numNodes - 1){
                finalPath = currPath;
                finalPathSize = *pathSize;
                finalBottleneck = *bottleneck;
                return 1;

            } else {
                
                // make local copies 
                int * currPathCpy= (int *) malloc(numNodes * sizeof(int));
                int * visitedCpy = (int *) malloc(numNodes * sizeof(int));
                int * pathSizeCpy = (int *) malloc(sizeof(int));
                *pathSizeCpy = oldPathSize;
                int * bottleneckCpy = (int *) malloc(sizeof(int));
                *bottleneckCpy = oldBottleneck;
                memcpy(currPathCpy, currPath, numNodes * sizeof(int));
                memcpy(visitedCpy, visited, sizeof(int) * numNodes);

                int rc = BFS(currPath, neighbor, visited, bottleneck, pathSize);
                
                if (rc == 1){
                    return 1;

                } else{
                    currPath = currPathCpy;
                    visited = visitedCpy;
                    visited[neighbor] = 0;
                    pathSize = pathSizeCpy;
                    *pathSize = *pathSizeCpy;
                    bottleneck = bottleneckCpy;
                    currPath[oldPathSize] = 0;
                }

            }

        }
    }

    *pathSize = *pathSize - 1;
    currPath[*pathSize] = 0;
    *bottleneck = originalBottleneck;
    visited[srcNode] = 0;

    return 0;

}


int main(int argc, char **argv){
    char * buf = NULL;
    size_t len = 0;
    getline(&buf, &len, stdin);
    int instances  = atoi(buf);
    char * token;
    
    for (long long instance = 0; instance < instances; instance ++){

        getline(&buf, &len, stdin);
        int numEdges;
        numNodes = atoi(strtok(buf, " "));
        numEdges = atoi(strtok(NULL, " "));
        
        adjMatrix = (int **) malloc(sizeof(int *) * numNodes);
        for (int i = 0; i < numNodes; i++){
            adjMatrix[i] = (int *) calloc(numNodes, sizeof(int));
        }

        int currRequest = 0;
        int srcNode;
        int dstNode;
        int capacity;
        int maxCapacity = 0;

        while (currRequest <  (numEdges)){

            getline(&buf, &len, stdin);
            srcNode = atoi(strtok(buf, " ")) - 1;
            dstNode = atoi(strtok(NULL, " ")) - 1;
            capacity = atoi(strtok(NULL, " "));
            
            if (capacity > maxCapacity){
                maxCapacity = capacity;
            }
            if (dstNode != 0){
                adjMatrix[srcNode][dstNode] = adjMatrix[srcNode][dstNode] + capacity;
            }
            currRequest++;
        }

        if (maxCapacity % 2 == 0){
            currCapacity = maxCapacity;
        }else {
            currCapacity = maxCapacity + 1;
        }

        int pathExists = 1;
        int rc = 1;
        int * currPath;
        int * visited;
        int * pathSize = (int *) malloc(sizeof(int));
        int * bottleneck = (int *) malloc(sizeof(int));

        while(pathExists || currCapacity > 1){
            if (pathExists  == 0){
                currCapacity = currCapacity /2;
                //printf("curr capacity : %d\n", currCapacity);
                pathExists = 1;
            }
            currPath = (int *) calloc(numNodes, sizeof(int));
            currPath[0] = 0;
            visited = (int *) calloc(numNodes, sizeof(int));
            *pathSize = 1;
            *bottleneck = -1;
            rc = BFS(currPath, 0, visited,  bottleneck, pathSize);

            if (rc == 0){
                //done
                pathExists = 0;

            } else{

                finalBottleneck = -1;
                for(int i = 0; i < finalPathSize - 1; i ++){
                    if (finalBottleneck < 0 || adjMatrix[finalPath[i]][finalPath[i+1]] < finalBottleneck){
                        finalBottleneck = adjMatrix[finalPath[i]][finalPath[i+1]];
                    }
                
                }
                for(int i = 0; i < finalPathSize - 1; i ++){
                    adjMatrix[finalPath[i]][finalPath[i+1]] = adjMatrix[finalPath[i]][finalPath[i+1]] - finalBottleneck;
                    adjMatrix[finalPath[i+1]][finalPath[i]] = adjMatrix[finalPath[i+1]][finalPath[i]] + finalBottleneck;
                }
            }
            memset(currPath, 0, sizeof(int) * numNodes);
            memset(visited, 0, sizeof(int) * numNodes);
        }

        int flow = 0;
        
        for(int i = 1; i < numNodes; i++){   
            flow = flow + adjMatrix[i][0];
        }

        printf("%d\n",flow);

        free(pathSize);
        free(bottleneck);
        free(currPath);
        free(visited);
        for (int i = 0; i < numNodes; i++){
           free(adjMatrix[i]);
        }
        free(adjMatrix);

    }


}
