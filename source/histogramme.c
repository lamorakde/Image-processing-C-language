#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
FILE *fio,*fir;

int main()
{
    unsigned char chi;

    int *io, *ir;
    long int i,j,m,l,dimx,ff,dimy,n,taille,maxr,maxv,maxb;
    double hist[256];
    double histt,f;
    long int dimxo=256;
    long int dimyo=144;
    long int k=3,s=1,nbg;
    char entree[35],sortie[35],chaine[10];

printf("1 donner entree sans .pgm\n");
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
fprintf(fir,"%ld %ld\n",dimxo,dimyo);


fscanf(fio,"%d\n",&nbg);
fprintf(fir,"%d\n",nbg);

printf("dimx=%d dimy=%d nbg=%d\n",dimx,dimy,nbg);

io=(int *)malloc(dimx*dimy*sizeof(int));

ir=(int *)malloc(dimxo*dimyo*sizeof(int));

if(ir==NULL) printf("allocation iob impossible\n");


taille=dimx*dimy;
printf("taille=%d\n",taille);
for(i=0;i<dimy;i++)
 for(j=0;j<dimx;j++)
 {
  chi=(unsigned char)fgetc(fio);
  io[i*dimx+j]=(int)chi;
 }


     // calcul l'histogramme //
    for (n=0;n<256;n++)
{
        hist[n]=0;
}


    for (i=0;i<dimy;i++)
        for (j=0;j<dimx;j++)
    {
        ff=io[i*dimx+j];
        hist[ff]++;
    }


    // printf("%d \n",hist[0]);



     for(n=0;n<256;n++)
    {
        histt=hist[n];
        hist[n]=(histt/taille*4500);
    }

for(n=0;n<256;n++)
     {
         printf(" hist[%d]=%lf \n",n,hist[n]);
     }


    //»æÖÆÖ±·½Í¼//
    for(n=0;n<256;n++)
    {
        f=144-hist[n];
        for (i=0;i<144;i++)
        {
            if (i<=f)
            {
                ir[i*256+n]=255;
                }
                else ir[i*256+n]=0;
            }
        }


for(i=0;i<144;i++)
 for(j=0;j<256;j++)
 {
	 fputc((unsigned char)ir[i*256+j],fir);
 }


free(io); //...

fclose(fio);fclose(fir);
return 0;
}

