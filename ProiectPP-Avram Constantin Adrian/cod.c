#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cod.h"

void imaginea(char* nume_fisier_sursa,char* nume_fisier_destinatie)
{
    FILE *fin, *fout;
    unsigned int dim_img, latime_img, inaltime_img;
    unsigned char pRGB[3], header[54], aux;

    printf("nume_fisier_sursa = %s \n",nume_fisier_sursa);

    fin = fopen(nume_fisier_sursa, "rb");
    if(fin == NULL)
    {
        printf("nu am gasit imaginea sursa din care citesc");
        return;
    }

    fout = fopen(nume_fisier_destinatie, "wb+");

    fseek(fin, 2, SEEK_SET);
    fread(&dim_img, sizeof(unsigned int), 1, fin);
    printf("Dimensiunea imaginii in octeti: %u\n", dim_img);

    fseek(fin, 18, SEEK_SET);
    fread(&latime_img, sizeof(unsigned int), 1, fin);
    fread(&inaltime_img, sizeof(unsigned int), 1, fin);
    printf("Dimensiunea imaginii in pixeli (latime x inaltime): %u x %u\n",latime_img, inaltime_img);

    //copiaza octet cu octet imaginea initiala in cea noua
    fseek(fin,0,SEEK_SET);
    unsigned char c;
    while(fread(&c,1,1,fin)==1)
    {
        fwrite(&c,1,1,fout);
        fflush(fout);
    }
    fclose(fin);

    //calculam padding-ul pentru o linie
    int padding;
    if(latime_img % 4 != 0)
        padding = 4 - (3 * latime_img) % 4;
    else
        padding = 0;

    printf("padding = %d \n",padding);

    fseek(fout, 54, SEEK_SET);
    int i,j;
    for(i = 0; i < inaltime_img; i++)
    {
        for(j = 0; j < latime_img; j++)
        {
            //citesc culorile pixelului
            fread(pRGB, 3, 1, fout);
            //fac conversia in pixel gri
            aux = 0.299*pRGB[2] + 0.587*pRGB[1] + 0.114*pRGB[0];
            pRGB[0] = pRGB[1] = pRGB[2] = aux;
            fseek(fout, -3, SEEK_CUR);
            fwrite(pRGB, 3, 1, fout);
            fflush(fout);
        }

    }
    fclose(fout);
}

unsigned int *xorshift32(unsigned int seed,int n)
{
    unsigned int r,k;
    unsigned int *v=(unsigned int*)malloc(n*sizeof(int));
    r=seed;

    for(k=0; k<n; ++k)
    {
        r=r^r<<13;
        r=r^r>>17;
        r=r^r<<5;
        v[k+1]=r;
    }
    return v;
}

void swap(unsigned int *a,unsigned int *b)
{
    unsigned int aux=*a;
    *a=*b;
    *b=aux;
}
unsigned int *durstenfeld(unsigned int *a,int n)
{
    a=(unsigned int*)malloc(n*sizeof(int));
    unsigned int r,k;
    for(k=0; k<n; ++k)
        a[k]=k;
    for(k=n-1; k>=1; --k)
    {
        r=rand()%(k+1);
        swap(&a[r],&a[k]);
    }
    return a;

}


imagine *citire(char *imag_init)
{
    FILE *f;
    f=fopen(imag_init,"rb");
    //fread(a->header,54,1,f);
    fseek(f,18,SEEK_SET);
    int w;
    fread(&w,4,1,f);
    int h;
    fread(&h,4,1,f);
    imagine *a=(imagine*)malloc(sizeof(imagine));
    a->p=calloc(sizeof(pixel),w*h);

    fseek(f, 54, SEEK_SET);
    int i,j;
    for(i = h-1; i>=0 ; i--)
    {
        for(j = 0; j < w; j++)
        {

            //k++;
            fread(&a->p[w*i+j],sizeof(pixel),1,f);
            //swap(&a->p[w*i+j].r,&a->p[w*i+j].b);

        }

    }



    a->w=w;
    a->h=h;



    fclose(f);
    return a;

}
imagine *citireNormal(char *imag_ini)
{
    FILE *f;
    f=fopen(imag_ini,"rb");
    fseek(f,18,SEEK_SET);
    unsigned int w;
    fread(&w,4,1,f);
    unsigned int h;
    fread(&h,4,1,f);



    imagine *a=(imagine*)malloc(sizeof(imagine));
    a->p=calloc(sizeof(pixel),w*h);
    fseek(f, 54, SEEK_SET);
    int i,j;
    for(i = h-1; i>=0 ; i--)
    {
        for(j = 0; j < w; j++)
        {


            fread(&a->p[w*i+j],sizeof(pixel),1,f);


        }

    }



    a->w=w;
    a->h=h;



    fclose(f);
    return a;

}

void criptare(char *imag_ini,char *img_cript,char *fisier_chei)
{


    FILE *f,*g,*h;

    unsigned int cheie,sv;
    int i;
    imagine *a=citire(imag_ini);
    h=fopen(img_cript,"wb+");
    f=fopen(fisier_chei,"r");
    g=fopen(imag_ini,"rb");
    fseek(f,0,SEEK_SET);
    fscanf(f,"%d %d",&cheie,&sv);


    unsigned int *v=xorshift32(cheie,2*a->w*a->h-1);



    unsigned int *r=durstenfeld(v,a->w*a->h-1);



    imagine *a2=(imagine*)malloc(sizeof(imagine));
    a2->h=a->h;
    a2->w=a->w;
    a2->p=calloc(sizeof(pixel),a2->w*a2->h);
    for(i=0; i<a->w*a->h; ++i)
        a2->p[r[i]]=a->p[i];




    int k;
    for(k=0; k<a->w*a->h; ++k)
        if(k==0)
        {
            a2->p[0].r=sv^a2->p[0].r;
            a2->p[0].r^=(v[a->w*a->h]>>(8*0))&255;
            a2->p[0].g=sv^a2->p[0].g;
            a2->p[0].g^=(v[a->w*a->h]>>(8*1))&255;
            a2->p[0].b=sv^a2->p[0].b;
            a2->p[0].b^=(v[a->w*a->h]>>(8*2))&255;
        }
        else
        {

            a2->p[k].r^=a2->p[k-1].r;
            a2->p[k].r^=(v[a->w*a->h+k]>>(8*0))&255;
            a2->p[k].g^=a2->p[k-1].g;
            a2->p[k].g^=(v[a->w*a->h+k]>>(8*1))&255;
            a2->p[k].b^=a2->p[k-1].b;
            a2->p[k].b^=(v[a->w*a->h+k]>>(8*2))&255;
        }

   fseek(h,18,SEEK_SET);
    fwrite(&a2->w,sizeof(int),1,h);
    fwrite(&a2->h,sizeof(int),1,h);
    int j;
    fseek(h,0,SEEK_SET);
    fseek(f,0,SEEK_SET);

    int *vd=(int*)malloc(14*sizeof(int));
    unsigned char m;
        for(j=1;j<=13;++j)
       fread(&vd[j],sizeof(int),1,f);
        fread(&m,1,1,f);
        for(j=1;j<=13;++j)
        fwrite(&vd[j],sizeof(int),1,h);
        fwrite(&m,1,1,h);

    fseek(h,54,SEEK_SET);
    for(i = a->h-1; i>=0 ; i--)
    {
        for(j = 0; j < a->w; j++)
        {


            fwrite(&a2->p[(a->w)*i+j],sizeof(pixel),1,h);
            //swap(&a->p[k].r,&a->p[k].b);

        }

    }

    free(vd);
    free(a);
    free(a2);
    fclose(f);

    fclose(h);
    fclose(g);
    fflush(f);
    fflush(h);
    fflush(g);




}
void decriptare(char *imag_ini,char *imag_fin,char *fisier_cheie)
{
    FILE *f,*g,*h;
    f=fopen(imag_ini,"rb");
    h=fopen(imag_fin,"wb+");
    g=fopen(fisier_cheie,"r");
    int cheie,sv;
    fscanf(g,"%d %d",&cheie,&sv);
    imagine *a=citire(imag_ini);
    unsigned int *v=xorshift32(cheie,a->w*a->h);
    unsigned int *r1=durstenfeld(v,a->h*a->w);
    int *r=calloc(a->h*a->w,sizeof(int));
    int i;

    for(i=0; i<a->h*a->w; ++i)
        r[r1[i]]=i;
    imagine *a2=(imagine*)malloc(sizeof(imagine));
    a2->h=a->h;
    a2->w=a->w;
    a2->p=calloc(sizeof(pixel),a2->w*a2->h);
    for(i=0; i<a->w*a->h; ++i)
        a2->p[i]=a->p[i];




    int k;
    for(k=0; k<=a->w*a->h; ++k)
        if(k==0)
        {
            a2->p[0].r=sv^a2->p[0].r;
            a2->p[0].r^=(v[a->w*a->h]>>(8*2))&255;
            a2->p[0].g=sv^a2->p[0].g;
            a2->p[0].g^=(v[a->w*a->h]>>(8*1))&255;
            a2->p[0].b=sv^a2->p[0].b;
            a2->p[0].b^=(v[a->w*a->h]>>(8*0))&255;
        }
        else
        {

            a2->p[k].r^=a2->p[k-1].r;
            a2->p[k].r^=(v[a->w*a->h+k]>>(8*2))&255;
            a2->p[k].g^=a2->p[k-1].g;
            a2->p[k].g^=(v[a->w*a->h+k]>>(8*1))&255;
            a2->p[k].b^=a2->p[k-1].b;
            a2->p[k].b^=(v[a->w*a->h+k]>>(8*0))&255;
        }

    imagine *decript=(imagine*)malloc(sizeof(imagine));
    decript->h=a->h;
    decript->w=a->w;
    decript->p=calloc(sizeof(pixel),a2->w*a2->h);
    for(i=0; i<a->w*a->h-1; ++i)
        decript->p[i]=a2->p[r[i]];
    int j;
     fseek(h,0,SEEK_SET);
    fseek(f,0,SEEK_SET);

    int *vd=(int*)malloc(14*sizeof(int));
    unsigned char m;
        for(j=1;j<=13;++j)
       fread(&vd[j],sizeof(int),1,f);
        fread(&m,1,1,f);
        for(j=1;j<=13;++j)
        fwrite(&vd[j],sizeof(int),1,h);
        fwrite(&m,1,1,h);
    fseek(h,54,SEEK_SET);
    for(i = a->h-1; i>=0 ; i--)
    {
        for(j = 0; j < a->w; j++)
        {


            fwrite(&decript->p[(a->h-1)*i+j],sizeof(pixel),1,h);
            //swap(&a->p[k].r,&a->p[k].b);

        }

    }
    free(a);
    free(a2);
    free(decript);
    fclose(f);

    fclose(h);
    fclose(g);
    fflush(f);
    fflush(h);
    fflush(g);





}

void chi_patrat(char *imag_ini)
{
    int i;
    imagine *a=citire(imag_ini);
    float k=(a->w*a->h)/256.0;
    //int r[300],g[300],b[300];
    int *r=calloc(256,sizeof(int));
    int *g=calloc(256,sizeof(int));
    int *b=calloc(256,sizeof(int));
    for(i=0; i<a->w*a->h; ++i)
    {
        r[a->p[i].r]++;
        g[a->p[i].g]++;
        b[a->p[i].g]++;
    }
    float fr=0,fg=0,fb=0;
    for(i=0; i<=255; ++i)
    {
        fr+=(r[i]-k)*(r[i]-k)/k;
        fg+=(g[i]-k)*(g[i]-k)/k;
        fb+=(b[i]-k)*(b[i]-k)/k;
    }

    printf("%f , %f , %f",fr,fg,fb);
    free(a);
    free(r);
    free(g);
    free(b);


}
void colorare(char *imagi,imagine **b,int nr,int poz)
{
    FILE *f;
    int x,y,h,w;
    imagine *a=citire(imagi);
    f=fopen(imagi,"wb");
    x=poz-(*b)->w/2;
    y=poz-(*b)->h/2;
    w=(*b)->w;
    h=(*b)->h;
    int u,v;
    switch(poz)
    {
    case 0:
        for(u=0; u<=h; ++u)
            a->p[(u+y)*w+x].r=255;
        a->p[(u+y)*w+x].g=0;
        a->p[(u+y)*w+x].b=0;
        for(v=0; v<=w; ++v)
            a->p[y*w+x+v].r=255;
        a->p[y*w+x+v].g=0;
        a->p[y*w+x+v].b=0;
        for(u=0; u<=h; ++u)
            a->p[(u+y)*w+x+w].r=255;
        a->p[(u+y)*w+x+w].g=0;
        a->p[(u+y)*w+x+w].b=0;
        for(v=0; v<=w; ++u)
            a->p[(y+h)*w+x+v].r=255;
        a->p[(y+h)*w+x+v].g=0;
        a->p[(y+h)*w+x+v].b=0;
        break;
    case 1:
        for(u=0; u<=h; ++u)
            a->p[(u+y)*w+x].r=255;
        a->p[(u+y)*w+x].g=255;
        a->p[(u+y)*w+x].b=0;
        for(v=0; v<=w; ++v)
            a->p[y*w+x+v].r=255;
        a->p[y*w+x+v].g=255;
        a->p[y*w+x+v].b=0;
        for(u=0; u<=h; ++u)
            a->p[(u+y)*w+x+w].r=255;
        a->p[(u+y)*w+x+w].g=255;
        a->p[(u+y)*w+x+w].b=0;
        for(v=0; v<=w; ++u)
            a->p[(y+h)*w+x+v].r=255;
        a->p[(y+h)*w+x+v].g=255;
        a->p[(y+h)*w+x+v].b=0;
        break;
    case 2:
        for(u=0; u<=h; ++u)
            a->p[(u+y)*w+x].r=0;
        a->p[(u+y)*w+x].g=255;
        a->p[(u+y)*w+x].b=0;
        for(v=0; v<=w; ++v)
            a->p[y*w+x+v].r=0;
        a->p[y*w+x+v].g=255;
        a->p[y*w+x+v].b=0;
        for(u=0; u<=h; ++u)
            a->p[(u+y)*w+x+w].r=0;
        a->p[(u+y)*w+x+w].g=255;
        a->p[(u+y)*w+x+w].b=0;
        for(v=0; v<=w; ++u)
            a->p[(y+h)*w+x+v].r=0;
        a->p[(y+h)*w+x+v].g=255;
        a->p[(y+h)*w+x+v].b=0;
        break;
    case 3:
        for(u=0; u<=h; ++u)
            a->p[(u+y)*w+x].r=0;
        a->p[(u+y)*w+x].g=255;
        a->p[(u+y)*w+x].b=255;
        for(v=0; v<=w; ++v)
            a->p[y*w+x+v].r=0;
        a->p[y*w+x+v].g=255;
        a->p[y*w+x+v].b=255;
        for(u=0; u<=h; ++u)
            a->p[(u+y)*w+x+w].r=0;
        a->p[(u+y)*w+x+w].g=255;
        a->p[(u+y)*w+x+w].b=255;
        for(v=0; v<=w; ++u)
            a->p[(y+h)*w+x+v].r=0;
        a->p[(y+h)*w+x+v].g=255;
        a->p[(y+h)*w+x+v].b=255;
        break;
    case 4:
        for(u=0; u<=h; ++u)
            a->p[(u+y)*w+x].r=255;
        a->p[(u+y)*w+x].g=0;
        a->p[(u+y)*w+x].b=255;
        for(v=0; v<=w; ++v)
            a->p[y*w+x+v].r=255;
        a->p[y*w+x+v].g=0;
        a->p[y*w+x+v].b=255;
        for(u=0; u<=h; ++u)
            a->p[(u+y)*w+x+w].r=255;
        a->p[(u+y)*w+x+w].g=0;
        a->p[(u+y)*w+x+w].b=255;
        for(v=0; v<=w; ++u)
            a->p[(y+h)*w+x+v].r=255;
        a->p[(y+h)*w+x+v].g=0;
        a->p[(y+h)*w+x+v].b=255;
        break;
    case 5:
        for(u=0; u<=h; ++u)
            a->p[(u+y)*w+x].r=0;
        a->p[(u+y)*w+x].g=0;
        a->p[(u+y)*w+x].b=255;
        for(v=0; v<=w; ++v)
            a->p[y*w+x+v].r=0;
        a->p[y*w+x+v].g=0;
        a->p[y*w+x+v].b=255;
        for(u=0; u<=h; ++u)
            a->p[(u+y)*w+x+w].r=0;
        a->p[(u+y)*w+x+w].g=0;
        a->p[(u+y)*w+x+w].b=255;
        for(v=0; v<=w; ++u)
            a->p[(y+h)*w+x+v].r=0;
        a->p[(y+h)*w+x+v].g=0;
        a->p[(y+h)*w+x+v].b=255;
        break;
    case 6:
        for(u=0; u<=h; ++u)
            a->p[(u+y)*w+x].r=192;
        a->p[(u+y)*w+x].g=192;
        a->p[(u+y)*w+x].b=192;
        for(v=0; v<=w; ++v)
            a->p[y*w+x+v].r=192;
        a->p[y*w+x+v].g=192;
        a->p[y*w+x+v].b=192;
        for(u=0; u<=h; ++u)
            a->p[(u+y)*w+x+w].r=192;
        a->p[(u+y)*w+x+w].g=192;
        a->p[(u+y)*w+x+w].b=192;
        for(v=0; v<=w; ++u)
            a->p[(y+h)*w+x+v].r=192;
        a->p[(y+h)*w+x+v].g=192;
        a->p[(y+h)*w+x+v].b=192;
        break;
    case 7:
        for(u=0; u<=h; ++u)
            a->p[(u+y)*w+x].r=255;
        a->p[(u+y)*w+x].g=140;
        a->p[(u+y)*w+x].b=0;
        for(v=0; v<=w; ++v)
            a->p[y*w+x+v].r=255;
        a->p[y*w+x+v].g=140;
        a->p[y*w+x+v].b=0;
        for(u=0; u<=h; ++u)
            a->p[(u+y)*w+x+w].r=255;
        a->p[(u+y)*w+x+w].g=140;
        a->p[(u+y)*w+x+w].b=0;
        for(v=0; v<=w; ++u)
            a->p[(y+h)*w+x+v].r=255;
        a->p[(y+h)*w+x+v].g=140;
        a->p[(y+h)*w+x+v].b=0;
        break;
    case 8:
        for(u=0; u<=h; ++u)
            a->p[(u+y)*w+x].r=128;
        a->p[(u+y)*w+x].g=0;
        a->p[(u+y)*w+x].b=128;
        for(v=0; v<=w; ++v)
            a->p[y*w+x+v].r=128;
        a->p[y*w+x+v].g=0;
        a->p[y*w+x+v].b=128;
        for(u=0; u<=h; ++u)
            a->p[(u+y)*w+x+w].r=128;
        a->p[(u+y)*w+x+w].g=0;
        a->p[(u+y)*w+x+w].b=128;
        for(v=0; v<=w; ++u)
            a->p[(y+h)*w+x+v].r=128;
        a->p[(y+h)*w+x+v].g=0;
        a->p[(y+h)*w+x+v].b=128;
        break;
    case 9:
        for(u=0; u<=h; ++u)
            a->p[(u+y)*w+x].r=128;
        a->p[(u+y)*w+x].g=0;
        a->p[(u+y)*w+x].b=0;
        for(v=0; v<=w; ++v)
            a->p[y*w+x+v].r=128;
        a->p[y*w+x+v].g=0;
        a->p[y*w+x+v].b=0;
        for(u=0; u<=h; ++u)
            a->p[(u+y)*w+x+w].r=128;
        a->p[(u+y)*w+x+w].g=0;
        a->p[(u+y)*w+x+w].b=0;
        for(v=0; v<=w; ++u)
            a->p[(y+h)*w+x+v].r=128;
        a->p[(y+h)*w+x+v].g=0;
        a->p[(y+h)*w+x+v].b=0;
        break;



    }

    for(u=0; u<=h; ++u)
        for(v=0; v<=w; ++v)
        {

            fseek(f,(u+y)*w+v+x,SEEK_SET);
            fwrite(&a->p[(u+y)*w+v+x],sizeof(pixel),1,f);
        }
    fclose(f);
    free(a);

}
int compar(const void*a,const void*b)
{


    return ((detectie*)a)->v-((detectie*)b)->v;
}
void template_matching(char *imag_ini,float ps,detectie *cor[300])
{
    int i,k;
    imagine *a=citire(imag_ini);
    for(i=0; i<a->w*a->h; ++i)
    {
        k=0.299*a->p[i].r + 0.587*a->p[i].g + 0.114*a->p[i].b;
        a->p[i].r=a->p[i].g=a->p[i].b=k;
    }
    imagine *b[10];
    char c[11];


    int z,nr=-1;
    for(z=0; z<=9; ++z)
    {
        sprintf(c,"cifra%d.bmp",z);
        b[z]=citire(c);


        for(i=0; i<b[z]->w*b[z]->h; ++i)
        {
            k=0.299*b[i]->p[i].r+ 0.587*b[i]->p[i].g + 0.114*b[i]->p[i].b;
            b[z]->p[i].r=b[z]->p[i].g=b[z]->p[i].b=k;
        }

        int w=b[z]->w;
        int h=b[z]->h;



        for(i=0; i<a->w*a->h; ++i)
        {


            int x,y,w,h,u,v;
            x=i-w/2;
            y=i-h/2;

            w=b[z]->w;
            h=b[z]->h;


            if(y+h>a->h||x+w>a->w||y<0||x<0)
                continue;
            else
            {


                float is=0,inf=0,ds=0,df=0;
                for(u=0; u<=h; ++u)




                    for(v=0; v<=w; ++v)
                    {


                        is=is+b[z]->p[u*w+v].r;
                        inf+=a->p[(u+y)*w+v+x].r;

                    }

                is/=w*h;
                inf/=w*h;
                for(u=0; u<=h; ++u)
                    for(v=0; v<=w; ++v)
                    {


                        ds=ds+(b[z]->p[u*w+v].r-is)*(b[z]->p[u*w+v].r-is);
                        df=df+(a->p[(u+y)*w+v+x].r-inf)*(a->p[(u+y)*w+v+x].r-inf);
                    }


                ds/=(w*h-1);
                ds=sqrt(ds);
                df/=(w*h-1);
                df=sqrt(df);
                int dfds=ds*df;
                float sumacor=0;
                for(u=0; u<=h; ++u)




                    for(v=0; v<=w; ++v)
                        sumacor+=(b[z]->p[u*w+v].r-is)*(a->p[(u+y)*w+v+x].r-inf)/dfds;

                sumacor/=w*h;
                if(sumacor>ps)
                {
                    nr++;
                    (*cor)[nr]=(detectie*)malloc(sizeof(detectie));
                    (*cor)[nr]->p=calloc(sizeof(pixel),w*h);
                    (*cor)[nr]->v=sumacor;
                    colorare(imag_ini,&b[z],z,i);


                }

            }
        }
        free(b[z]);












    }
    qsort(cor,nr,sizeof(detectie),compar);
    free(a);

}

