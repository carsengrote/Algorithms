import sys;
instances = int(sys.stdin.readline());

for currentInstance in range(instances):

    numJobs = int(sys.stdin.readline());
    jobArray = [0] * numJobs;

    for currJob in range(0, numJobs):
        line = sys.stdin.readline();
        line = line.strip();
        newJob = line.split();
        newJob[0] = int(newJob[0]);
        newJob[1] = int(newJob[1]);
        jobArray[currJob] = newJob;

    sortedArray = sorted(jobArray, key=lambda x: x[1], reverse=False);
    currStart = 0;
    totalRun = 0;
    for index in range(0,numJobs):
        if sortedArray[index][0] >= currStart:
            currStart = sortedArray[index][1];
            totalRun = totalRun + 1;

    print(totalRun, end='\n');
