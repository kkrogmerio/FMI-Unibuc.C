#ifndef COD_H_INCLUDED
#define COD_H_INCLUDED
void imaginea(char* nume_fisier_sursa,char* nume_fisier_destinatie);
unsigned int *xorshift32(unsigned int seed,int n);
void swap(unsigned int *a,unsigned int *b);
typedef struct {
unsigned char b,g,r;}pixel;
typedef struct {  pixel *p;
int w,h;
}imagine;
typedef struct {pixel *p;
int w,h,v;}detectie;
imagine *citire(char *imag_ini);
imagine *citireNormal(char *imag_init);
void criptare(char *imag_ini,char *img_cript,char *fisier_chei);
void chi_patrat(char *imag_ini);
void template_matching(char *imag_ini,float ps,detectie **cor[300]);
int compar(const void*a,const void*b);

#endif // COD_H_INCLUDED
