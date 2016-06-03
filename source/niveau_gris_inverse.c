#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
FILE *fio,*fir;

int main()
{
    unsigned char chi;

    int *io, *ir, Sx,Sy, *theta;
    long int i,j,m,l,dimx,dimy,taille,maxr,maxv,maxb;
    int sx[3][3]={{-1,0,1},{-2,0,2},{-1,0,1}};
    int sy[3][3]={{1,2,1},{0,0,0},{-1,-2,-1}};
    float theta2;
    float PI = 3.141592653589793;
    long int k=3,s=1,nbg;
    int seuil=70;
    char entree[35],sortie[35],chaine[10];
printf(" Inverse\n");
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

theta=(int *)malloc(dimx*dimy*sizeof(int));

if(ir==NULL) printf("allocation iob impossible\n");


taille=dimx*dimy;
printf("taille=%d\n",taille);
for(i=0;i<dimy;i++)
 for(j=0;j<dimx;j++)
 {
  chi=(unsigned char)fgetc(fio);
  io[i*dimx+j]=(int)chi;
 }



// niveau gris inverse //
 for (i=0;i<dimy-1;i++)
    for (j=0;j<dimx-1;j++)
 {
     ir[i*dimx+j]=255-io[i*dimx+j];
 }



for(i=0;i<dimy;i++)
 for(j=0;j<dimx;j++)
 {
	 fputc((unsigned char)ir[i*dimx+j],fir);
 }


free(io); //...

fclose(fio);fclose(fir);
return 0;
}
