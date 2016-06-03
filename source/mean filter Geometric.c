#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
FILE *fio,*fir;


int main()
{
    unsigned char chi;

    long int *io, *ir;
    double result_tp;
    double it;
    int s1,s2,s3;
    long int i,j,ic,jc,m,l,dimx,ff,dimy,n,taille,maxr,maxv,maxb;
    int model[3][3]={{1,1,1},{1,1,1},{1,1,1}};

    long int k=3,s=1,nbg;
    char entree[35],sortie[35],chaine[10];

printf("Geometric Mean Filter 3*3\n");
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

////////////////////////////////////////////

for(i=1;i<dimy-1;i++)
  for(j=1;j<dimx-1;j++)
{
    result_tp=1;
    for(l=-1;l<2;l++)
    for(m=-1;m<2;m++)
    {   if (io[(i+l)*dimx+(j+m)]!=0)
        {
       result_tp=result_tp*(io[(i+l)*dimx+(j+m)]/255.)*model[l+1][m+1];
            }
    }
    it = pow(result_tp,1./9);
    ir[i*dimx+j]= it*255;
    // printf("io[i*dimx+j]=%d,ir[i*dimx+j]=%d\n",io[i*dimx+j],ir[i*dimx+j]);
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

