#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
FILE *fio,*fir;


int main()
{
    unsigned char chi;

    int *io, *ir;
    long int i,j,ic,jc,m,l,dimx,ff,dimy,n,taille,maxr,maxv,maxb;
    double udark[256];
    double ugray[256];
    double ubright[256];
    int vd=35;
    int vg=127;
    int vb=220;
    long int k=3,s=1,nbg;
    char entree[35],sortie[35],chaine[10];

printf("Intensity Transformation with fuzzy sets\n");
printf("donner entree sans .pgm\n");
scanf("%s",entree);
strcat(entree,".pgm");

printf("donner sortie sans .pgm\n");
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


      // ºËÐÄ //

for (n=0;n<256;n++)
{
    if(n<=70)
    {
        udark[n]=1;
    }
    else if((n>=71)&&(n<=128))           // definition of udark
    {
        udark[n]=-(1/57.)*(n-128);
    }
    else udark[n]=0;
}


for (n=0;n<256;n++)
{
    if(n<=70)
    {
        ugray[n]=0;
    }
    else if((n>=71)&&(n<=128))           // definition of ugray
    {
        ugray[n]=(1/57.)*(n-71);
    }
    else if((n>=129)&&(n<=180))
    {
        ugray[n]=-(1/57.)*(n-180);
    }
    else ugray[n]=0;
}

for (n=0;n<256;n++)
{
    if(n<=127)
    {
        ubright[n]=0;                    // definition of bright
    }
    else if((n>=128)&&(n<180))
    {
        ubright[n]=(1/57.)*(n-128);
    }
    else ubright[n]=1;
}

for(n=0;n<256;n++)
{
    printf("[%d]=%f--%f--%f\n",n,udark[n],ugray[n],ubright[n]);
}

for(i=0;i<dimy;i++)
 for(j=0;j<dimx;j++)
 {

   ir[i*dimx+j]=(udark[io[i*dimx+j]]*vd+ugray[io[i*dimx+j]]*vg+ubright[io[i*dimx+j]]*vb)/(udark[io[i*dimx+j]]+ugray[io[i*dimx+j]]+ubright[io[i*dimx+j]]);

 }


for(i=0;i<dimy;i++)
 for(j=0;j<dimx;j++)
 {
	 fputc((unsigned char)ir[i*dimx+j],fir);   // Êä³ö //
 }


free(io); //...

fclose(fio);fclose(fir);
return 0;
}

