    import math
    mark = dict()
    #ceva["ANAA"]=(4,5,6)
    #ceva["ANAA"][2]+=1
    #print(ceva["ANAA"])

    with open('F1.in','r') as f:
        for line in f:
            for word in line.split():
                if word not in mark:
                mark[word]=(1,0)
                else:
                mark[word]=(mark[word][0]+1,mark[word][1])
                #print(mark[word][0])
    with open('F2.in','r') as f:
        for line in f:
            for word in line.split():
                if word not in mark:
                mark[word]=(0,1)
                else:
                mark[word]=(mark[word][0],mark[word][1]+1)
            
    prod=0
    sq1=0
    sq2=0
    for it in mark:
        prod+=mark[it][0]*mark[it][1]
        sq1+=mark[it][0]*mark[it][0]
        sq2+=mark[it][1]*mark[it][1]
    dcos=float(prod)/(math.sqrt(sq1)*math.sqrt(sq2))
    print("Dcos(F1,F2)= ",dcos)
        

