import sys;
instances = int(sys.stdin.readline());

for currentInstance in range(instances):

    cacheSize = int(sys.stdin.readline());
    numRequests = int(sys.stdin.readline());
    requests = sys.stdin.readline();
    requests = requests.strip();
    requestsArray = requests.split();
    cache = []; 
    cachePop = 0;

    pageFaults = 0;

    for currentRequest in range(0, numRequests):
        
        if (cache.count(requestsArray[currentRequest]) == 0):

            pageFaults = pageFaults + 1;

            if (cachePop < cacheSize):
                cache.append(requestsArray[currentRequest]);
                cachePop = cachePop + 1;
            
            else:

                farthestAway = cache[0];
                distance = 0;

                for page in cache:

                    if (requestsArray[currentRequest :].count(page) == 0):
                        farthestAway = page;
                        break;
                        
                    elif (requestsArray[currentRequest :].index(page) > distance):
                        distance = requestsArray[currentRequest :].index(page);
                        farthestAway = page;
                    
                cache[cache.index(farthestAway)] = requestsArray[currentRequest];
    
    print(pageFaults);
