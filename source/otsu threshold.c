#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
FILE *fio,*fir;


int main()
{
    unsigned char chi;
    long int *io, *ir;
    long hist[256];
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
    double test;


    long int i,j,ic,jc,m,l,dimx,ff,dimy,n,taille,maxr,maxv,maxb;

    long int k=3,s=1,nbg;
    char entree[35],sortie[35],chaine[10];

printf(" Otsu Threshold \n");
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
ir=(int *)malloc(dimx*dimy*sizeof(int));


if(ir==NULL) printf("allocation iob impossible\n");


taille=dimx*dimy;
tailled=taille;
printf("taille=%d\n",taille);
for(i=0;i<dimy;i++)
 for(j=0;j<dimx;j++)
 {
  chi=(unsigned char)fgetc(fio);
  io[i*dimx+j]=(int)chi;
 }

for(j=0;j<dimx;j++)                  // 将最上最下两行的像素值置为0
{
	ir[j] = 0;
	ir[j+(dimy-1)*dimx] = 0;
}

for(i=0;i<dimy;i++)                  // 将最左最右两行的像素值置为0
{
	ir[i*dimx] = 0;
	ir[(i+1)*dimx-1] = 0;
}

////////////////////////////////////////////
for (n=0;n<256;n++)
{
    hist[n]=0;     //直方图初始化
}


for (i=0;i<dimy;i++)   //得到直方图
    for (j=0;j<dimx;j++)
    {
        ff=io[i*dimx+j];
        hist[ff]=hist[ff]+1;
    }

for(n=0;n<256;n++)
{
    printf("hist[%d]=%d\n",n,hist[n]);
}


for (i=0;i<256;i++)
{
    pi[i]=hist[i]/tailled;     // obtain pi
    //printf("pi[%d]=%f\n",i,pi[i]);
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



for(i=0;i<dimy;i++)
 for(j=0;j<dimx;j++)
 {
	 if (io[i*dimx+j]>seuil)
        ir[i*dimx+j]=255;
     else ir[i*dimx+j]=0;
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
