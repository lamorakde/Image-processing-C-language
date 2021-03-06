#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
FILE *fio,*fir;
double gx(double d);
double kappa=20;


int main()
{
    unsigned char chi;
    int T;
    double test,test1,test2,test3;
    double alpha,delta0,delta1,delta2,delta3;
    int a;
    long int *io,*ir,*Dx,*Dy,*it,*it2;
    long int i,j,g,m,l,dimx,ff,dimy,n,taille,maxr,maxv,maxb;
    long int k=3,s=1,nbg;
    char entree[35],entree2[35],sortie[35],chaine[10];

printf("Perona-Malik Filter \n");
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
Dx=(int *)malloc(dimx*dimy*sizeof(int));
Dy=(int *)malloc(dimx*dimy*sizeof(int));
ir=(int *)malloc(dimx*dimy*sizeof(int));
it=(int *)malloc(dimx*dimy*sizeof(int));
it2=(int *)malloc(dimx*dimy*sizeof(int));


if(ir==NULL) printf("allocation iob impossible\n");


taille=dimx*dimy;
printf("taille=%d\n",taille);
for(i=0;i<dimy;i++)
 for(j=0;j<dimx;j++)
 {
  chi=(unsigned char)fgetc(fio);
  io[i*dimx+j]=(int)chi;
 }

/////////////////////////////////////////////
alpha=0.2;
T=20;

for(i=0;i<dimy;i++)
for(j=0;j<dimx;j++)
{
    it[i*dimx+j]=io[i*dimx+j];
}

for(a=0;a<T;a++)
{
    for(i=0;i<dimy-1;i++)
     for(j=0;j<dimx-1;j++)
     {
        Dx[i*dimx+j]=it[i*dimx+j+1]-it[i*dimx+j];
        Dy[i*dimx+j]=it[(i+1)*dimx+j]-it[i*dimx+j];
     }

     for(i=1;i<dimy;i++)
      for(j=1;j<dimx;j++)
      {
          delta0=Dx[i*dimx+j];
          delta1=Dy[i*dimx+j];

          delta2=-Dx[i*dimx+j-1];
          delta3=-Dy[(i-1)*dimx+j];
          it2[i*dimx+j]=it[i*dimx+j]+alpha*((gx(abs(delta0))*delta0)+(gx(abs(delta1))*delta1)+(gx(abs(delta2))*delta2)+(gx(abs(delta3))*delta3));
      }

      for(i=1;i<dimy;i++)
      for(j=1;j<dimx;j++)
      {
          it[i*dimx+j]=it2[i*dimx+j];
      }

}


for(i=0;i<dimy;i++)
for(j=0;j<dimx;j++)
{
    ir[i*dimx+j]=it[i*dimx+j];
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

double gx(double d)
{
    double z;

    z=exp(-(d/kappa)*(d/kappa));

    return z;
}
