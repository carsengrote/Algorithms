import sys;
instances = int(sys.stdin.readline());

def dfs(numNodes, edgeMatrix, nodes, stack):

    explored = [0] * numNodes;
    visitedOrder = [];

    while (len(stack) > 0):
        currNode = stack.pop();
        print(currNode);
        nodeIndex = currNode[1];
        
        if explored[nodeIndex] == 0:
            explored[nodeIndex] = 1;
            visitedOrder.append(currNode[0]);
            for neighbor in reversed(range(len(edgeMatrix[nodeIndex][0]))):
                stack.append(edgeMatrix[nodeIndex][0][neighbor]);

    print(*visitedOrder);

    return

for i in range(instances): 
    
    currNodes = int(sys.stdin.readline());
    edgeMatrix = [0] * currNodes;
    nodes = [0] * currNodes;
    stack = [];

    for currLine in range(0, currNodes):
        line = sys.stdin.readline();
        newRow = line.split();  # assume constant? 
        nodes.append([newRow[0], currLine])
        stack.insert(0, [newRow[0], currLine]);
        edgeMatrix[currLine] = [newRow, currLine];
    print(stack);
    dfs(currNodes, edgeMatrix, nodes, stack);

exit();
