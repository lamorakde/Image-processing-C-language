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
    int *ior,*iov,*iob,*irr,*irv,*irb;
    long int i,j,ic,jc,m,l,dimx,ff,dimy,n,taille,maxr,maxv,maxb;
    long int k=3,s=1,nbg;
    char entree[35],sortie[35],chaine[10];

printf("Filtre Bilateral en couleur\n");
printf("Donner entree sans .ppm\n");
scanf("%s",entree);
strcat(entree,".ppm");

printf("Donner sortie sans .ppm\n");
scanf("%s",sortie);
strcat(sortie,".ppm");


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

ior=(int *)malloc(dimx*dimy*sizeof(int));
iov=(int *)malloc(dimx*dimy*sizeof(int));
iob=(int *)malloc(dimx*dimy*sizeof(int));

irr=(int *)malloc(dimx*dimy*sizeof(int));
irv=(int *)malloc(dimx*dimy*sizeof(int));
irb=(int *)malloc(dimx*dimy*sizeof(int));

if(irb==NULL) printf("allocation iob impossible\n");

taille=dimx*dimy;
printf("taille=%d\n",taille);
for(i=0;i<dimy;i++)
 for(j=0;j<dimx;j++)
 {
  chi=(unsigned char)fgetc(fio);
  ior[i*dimx+j]=(int)chi;
  chi=(unsigned char)fgetc(fio);
  iov[i*dimx+j]=(int)chi;
  chi=(unsigned char)fgetc(fio);
  iob[i*dimx+j]=(int)chi;
 }

////////////////////////////////////////////

sigmad=5;
sigmar=10;

printf("*********************************\n");
printf("\n");
printf("      Bilateral Filter\n");
printf("      sigmad=%d\n",sigmad);
printf("      sigmar=%d\n",sigmar);
printf("\n");
printf("*********************************\n");

for(i=7;i<dimy-7;i++)
 for(j=7;j<dimx-7;j++)
 {
     S=0;
     W=0;
     a=ior[i*dimx+j];

     for(m=-7;m<8;m++)
        for(n=-7;n<8;n++)
     {
        b=ior[(i+m)*dimx+j+n];
        wd=exp(-(m*m+n*n)/(2*sigmad*sigmad));
        wr=exp(-(a-b)*(a-b)/(2*sigmad*sigmad));
        w=wd*wr;
        S=S+w*b;
        W=W+w;
     }

     irr[i*dimx+j]=S/W;
 }

printf("Filter for Red:   Completed.\n");


 for(i=7;i<dimy-7;i++)
 for(j=7;j<dimx-7;j++)
 {
     S=0;
     W=0;
     a=iov[i*dimx+j];

     for(m=-7;m<8;m++)
        for(n=-7;n<8;n++)
     {
        b=iov[(i+m)*dimx+j+n];
        wd=exp(-(m*m+n*n)/(2*sigmad*sigmad));
        wr=exp(-(a-b)*(a-b)/(2*sigmad*sigmad));
        w=wd*wr;
        S=S+w*b;
        W=W+w;
     }

     irv[i*dimx+j]=S/W;
 }

printf("Filter for Green: Completed.\n");


 for(i=7;i<dimy-7;i++)
 for(j=7;j<dimx-7;j++)
 {
     S=0;
     W=0;
     a=iob[i*dimx+j];

     for(m=-7;m<8;m++)
        for(n=-7;n<8;n++)
     {
        b=iob[(i+m)*dimx+j+n];
        wd=exp(-(m*m+n*n)/(2*sigmad*sigmad));
        wr=exp(-(a-b)*(a-b)/(2*sigmad*sigmad));
        w=wd*wr;
        S=S+w*b;
        W=W+w;
     }

     irb[i*dimx+j]=S/W;
 }


printf("Filter for Blue:  Completed.\n");


////////////////////////////////////////////

for(i=0;i<dimy;i++)
 for(j=0;j<dimx;j++)
 {
   fputc((unsigned char)irr[i*dimx+j],fir);
   fputc((unsigned char)irv[i*dimx+j],fir);
   fputc((unsigned char)irb[i*dimx+j],fir);
 }


free(ior); //...

fclose(fio);fclose(fir);
return 0;
}

