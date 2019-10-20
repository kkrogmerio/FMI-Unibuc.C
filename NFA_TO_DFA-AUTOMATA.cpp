#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

int st_fin[100],st_ini,nr_st_fin,nr_lit,nr_tranz,nrsir,x,z;
int stare[200];
char y;
int lambda=int('{' - 'a');
int ok;
int n;
int v[100][100][100];
int alfa[50];
char sir[40];

void transformare(char *p,int pozi,int ind)
{
    int ln3;
    int i;
    //cout<<"da";
   // cout<<p[ind]<<"\n";
    if(ok==1)
    {
        return;
    }

    if(ind==strlen(p))
    {
        for(i=0; i<nr_st_fin; ++i)
            if(st_fin[i]==pozi)
            {
                cout<<"da"<<'\n';
                ok=1;
                return;
            }

        cout<<"nu"<<'\n';
        ok=1;
        return;
    }
    else
    {
        char k=p[ind];
        int kla;
        if(k == '.')
            kla = '{' - 'a';
        else
            kla=k-'a';

        //for(i=0;i<nr_lit;++i)
        for(ln3=0; ln3<n; ++ln3)
        {


            if(v[pozi][kla][stare[ln3]]==1&&kla!=lambda)
            {



                /* strrev(p);
                 p[strlen(p)-1]='\0';
                 strrev(p);*/
                transformare(p,stare[ln3],ind+1);
            }
            else
                if(v[pozi][kla][stare[ln3]]==1&&kla==lambda)
                {


                transformare(p,stare[ln3],ind);
                }
        }




    }



}
int main()
{
    //freopen("date.in","r",stdin);
  //  freopen("date.out","w",stdout);
    cin>>n;
    int i;
    for(i=0;i<n;++i)
        cin>>stare[i];
    cin>>nr_lit;
    char lit;
    for(i=0; i<nr_lit; ++i)
    {
        cin>>lit;
        alfa[i]=lit-'a';
    }
    ++nr_lit;
    alfa[nr_lit-1]=lambda;
    cin>>st_ini;
    cin>>nr_st_fin;
    for(i=0; i<nr_st_fin; ++i)
        cin>>st_fin[i];
    cin>>nr_tranz;
    for(i=0; i<nr_tranz; ++i)
    {


        cin>>x>>y>>z;
        int num;
        if(y=='.')
            num = int('{' - 'a');
        else
            num=y-'a';
        v[x][num][z]=1;
    }


    n++;
    stare[n-1] = n;
    int j;
    for(i=0;i<n;++i)
        for(j=0;j<nr_lit;++j)
            v[stare[i]][alfa[j]][stare[n-1]] = 1;

    cin>>nrsir;
    for(i=0; i<nrsir; ++i)
    {
        ok=0;
        cin>>sir;
        char *p=sir;

        transformare(p,st_ini,0);
    }




    return 0;
}
