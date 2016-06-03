#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
FILE *fio,*fir;


int main()
{
    unsigned char chi;
    double hist[256];
    double pi[256];
    double omega[256];
    double omega0[256];
    double omega1[256];
    double tailled;
    double mu[256];
    double mu0[256];
    double mu1[256];
    double sigma[256];
    double sigmamax;
    int sigma_num;
    int seuil;
    int a,b,test,jump,zero;
    int circle,loop,heng,zong;
    long int *io,*ir,*it,*it2,*it3;
    long int i,j,g,m,l,dimx,ff,dimy,n,taille,maxr,maxv,maxb;
    long int k=3,s=1,nbg;
    char entree[35],entree2[35],sortie[35],chaine[10];

printf("Hole Filling \n");
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
it3=(int *)malloc(dimx*dimy*sizeof(int));
it2=(int *)malloc(dimx*dimy*sizeof(int));
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

/////////////////////////////////////////////

a=2;
b=2;
zong=1;
heng=0;


for(loop=1;loop<(a*b+1);loop++)
{

    heng++;
    tailled=taille/(a*b);

    if(heng==a+1)
    {
        heng=1;
        zong++;
    }

    for(i=0;i<256;i++)
    {
        hist[i]=0; //直方图初始化
        pi[i]=0;
        omega[i]=0;
        omega0[i]=0;
        omega1[i]=0;
        mu[i]=0;
        mu0[i]=0;
        mu1[i]=0;
        sigma[i]=0;
    }

    for (i=(0+(dimy/b)*(zong-1));i<((dimy/b)+(dimy/b)*(zong-1));i++)
     for (j=(0+(dimx/a)*(heng-1));j<((dimx/a)+(dimx/a)*(heng-1));j++)
     {
        ff=io[i*dimx+j];
        hist[ff]++;      //得到直方图
     }


    for (i=0;i<256;i++)
     {
         pi[i]=hist[i]/(tailled/(a*b));     // obtain pi
     }

    for(i=0;i<256;i++)
     {

     }

    for (i=0;i<256;i++)
     {
        for (n=i;n>=0;n--)
         {
             omega[i]+=pi[n];         // obtain omega
             mu[i]+=n*pi[n];          // obtain mu
         }

         omega0[i]=omega[i];       // obtain omega0
         omega1[i]=1-omega0[i];  // obtain omega1
     }


    for (i=0;i<256;i++)
     {
         mu0[i]=mu[i]/omega[i];                   // mu0
         mu1[i]=(mu[255]-mu[i])/(1-omega[i]);     // mu1
     }


    for (i=0;i<256;i++)
     {
         if (omega[i]!=0)
         {
             sigma[i]=((mu[255]*omega[i]-mu[i])*(mu[255]*omega[i]-mu[i]))/(omega[i]*(1-omega[i]));
         }
         else sigma[i]=0;
     }


     sigmamax=sigma[1];
     sigma_num=1;

     for (i=1;i<255;i++)
     {
         if (sigma[i]>sigmamax)
         {
             sigmamax=sigma[i];
             sigma_num=i;
             seuil=sigma_num;
         }
     }



    for (i=0;i<256;i++)
     {
         printf("omega[%d]=%f\n",i,omega[i]);
     }
     printf("%f",omega[22]);

    for (i=(0+(dimy/b)*(zong-1));i<((dimy/b)+(dimy/b)*(zong-1));i++)
     for (j=(0+(dimx/a)*(heng-1));j<((dimx/a)+(dimx/a)*(heng-1));j++)
     {
         if (io[i*dimx+j]>seuil)
             it[i*dimx+j]=255;
         else it[i*dimx+j]=0;
     }

     for (i=(0+(dimy/b)*(zong-1));i<((dimy/b)+(dimy/b)*(zong-1));i++)
     for (j=(0+(dimx/a)*(heng-1));j<((dimx/a)+(dimx/a)*(heng-1));j++)
      {
          if((it[i*dimx+j]==255)||(ir[i*dimx+j]==255))
          {
              ir[i*dimx+j]=255;
          }
      }
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
