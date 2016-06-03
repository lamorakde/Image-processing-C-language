#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
FILE *fio,*fir;


int main()
{
    unsigned char chi;
    int x,y,a,b;
    double wd,wr,w,S,W;
    int sigmad,sigmar;
    int test1;
    double test2;
    long int *io,*ir,*it,*it1,*it2,*it3;
    long int i,j,ic,jc,m,l,dimx,ff,dimy,n,taille,maxr,maxv,maxb;
    long int k=3,s=1,nbg;
    char entree[35],sortie[35],chaine[10];

printf("Filtre alterne\n");
printf("Donner entree sans .pgm\n");
scanf("%s",entree);
strcat(entree,".pgm");

printf("Donner sortie sans .pgm\n");
scanf("%s",sortie);
strcat(sortie,".pgm");


fio=fopen(entree,"rb");
fir=fopen(sortie,"wb+");

if(fio !=NULL) printf("ouverture du fichier in\n");
if(fir !=NULL) printf("ouverture du fichier out\n");

//if(im!=0) printf("allocation de im\n");

fscanf(fio,"%s\n",chaine);
fprintf(fir,"%s\n",chaine);


i=0;
while(i<1)
{chi=fgetc(fio);
// if((int)chi==6)  fputc((unsigned char)5,fr);
 fputc(chi,fir);
 if(chi=='\n') i++;
}

fscanf(fio,"%ld %ld\n",&dimx,&dimy);
fprintf(fir,"%ld %ld\n",dimx,dimy);


fscanf(fio,"%d\n",&nbg);
fprintf(fir,"%d\n",nbg);

printf("dimx=%d dimy=%d nbg=%d\n",dimx,dimy,nbg);

io=(int *)malloc(dimx*dimy*sizeof(int));
it=(int *)malloc(dimx*dimy*sizeof(int));
it1=(int *)malloc(dimx*dimy*sizeof(int));
it2=(int *)malloc(dimx*dimy*sizeof(int));
it3=(int *)malloc(dimx*dimy*sizeof(int));
ir=(int *)malloc(dimx*dimy*sizeof(int));


if(ir==NULL) printf("allocation iob impossible\n");


taille=dimx*dimy;
printf("taille=%d\n",taille);
for(i=0;i<dimy;i++)
 for(j=0;j<dimx;j++)
 {
  chi=(unsigned char)fgetc(fio);
  io[i*dimx+j]=(int)chi;
 }


////////////////////////////////////////////

sigmad=5;
sigmar=20;

for(i=7;i<dimy-7;i++)
 for(j=7;j<dimx-7;j++)
 {
     S=0;
     W=0;
     a=io[i*dimx+j];

     for(m=-7;m<8;m++)
        for(n=-7;n<8;n++)
     {
        b=io[(i+m)*dimx+j+n];
        wd=exp(-(m*m+n*n)/(2*sigmad*sigmad));
        wr=exp(-(a-b)*(a-b)/(2*sigmad*sigmad));
        w=wd*wr;
        S=S+w*b;
        W=W+w;
     }
     ir[i*dimx+j]=S/W;
 }





////////////////////////////////////////////

for(i=0;i<dimy;i++)
 for(j=0;j<dimx;j++)
 {
	 fputc((unsigned char)ir[i*dimx+j],fir);   // Êä³ö //
 }


free(io); //...

fclose(fio);fclose(fir);
return 0;
}

