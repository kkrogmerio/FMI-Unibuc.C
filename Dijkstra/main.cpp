#include <iostream>
#include <vector>
#include <fstream>
#include <queue>


using namespace std;

ifstream fin("dijkstra.in");
ofstream fout("dijkstra.out");
vector <int> graph[50005];
vector <int> graphC[50005];
priority_queue<pair<int,int>> myheap;
int dist[50005];
int viz[50005];

#define max_size 20000005


int main()
{
    int N,M,x,y,c,i,k,index;
    fin>>N>>M;
    for(i=1;i<=M;i++)
    {
        fin>>x>>y>>c;
        graph[x].push_back(y);
        graphC[x].push_back(c);
    }

    for(i=1;i<=N;i++){
      if(i==1) dist[i]=0;
       else
        dist[i]=max_size;
     myheap.push(make_pair(-dist[i],i));
    }
    while(!myheap.empty())
    {
        pair<int,int>p=myheap.top();
        index=p.second;
        myheap.pop();
        if(viz[index]==1);
        else
        {
            viz[index]=1;

            int lim=graph[index].size();
            for(k=0;k<lim;k++)
            {
                int vecin=graph[index][k];
                if(dist[vecin]>(dist[index]+graphC[index][k]))
                   {dist[vecin]=dist[index]+graphC[index][k];
                   myheap.push(make_pair(-dist[vecin],vecin));}
            }

       }
    }
    for(i=2;i<=N;i++){
      if(dist[i]==max_size)
        dist[i]=0;
      fout<<dist[i]<<" ";
    }
    return 0;
}
