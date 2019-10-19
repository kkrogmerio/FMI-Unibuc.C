
ok=[]
n,m=input().split()
def DF(i):
   # i=int(i)
    ok[i]=0
   # print(i)
    for j in v[i]:
       # val=int(j)
        DF(j)
        if ok[j]==1:
            ok[i]=1
    if ok[i]==0:
        print(i," ")
        ok[i]=1
n=int(n)
m=int(m)
oki=[0]*(n+1)
ok=[0]*(n+1)
v=[]
for i in range(n+1):
    v.append([])
for i in range(m):
    a,b=(input().split())
    a=int(a)
    b=int(b)
   # print(len(v))
    v[a].append(b)
    oki.append(b)
rad=0
for i in range(1,n):
    if oki[i]==0:
        rad=i
        break
print(rad," ")
for i in range(n):
    v[i].sort()
DF(rad)