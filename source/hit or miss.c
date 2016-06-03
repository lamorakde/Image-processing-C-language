#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
FILE *fio,*fir;


int main()
{
    unsigned char chi;
    int a[9];
    int x,y;
    int tp;
    long int *io, *ir, *it, *iinverse, *it2;
    int min,min2;
    int t1,t2;
    long int i,j,ic,jc,m,l,dimx,ff,dimy,n,taille,maxr,maxv,maxb;

    long int k=3,s=1,nbg;
    char entree[35],sortie[35],chaine[10];

printf("Dilation   \n");
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
it=(int *)malloc(dimx*dimy*sizeof(int));
iinverse=(int *)malloc(dimx*dimy*sizeof(int));
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


////////////////////////////////////////////

for(i=2;i<dimy-2;i++)
  for(j=2;j<dimx-2;j++)
{
    min=io[(i)*dimx+j];

    for (l=-2;l<3;l++)
        for (m=-2;m<3;m++)
    {
        if ( (io[(i+l)*dimx+j+m])<min )
        {
            min=io[(i+l)*dimx+j+m];
        }
    }

    it[i*dimx+j]=min;            //取最小，做腐蚀运算,erosion
}

for(i=0;i<dimy;i++)
 for(j=0;j<dimx;j++)
 {
	 iinverse[i*dimx+j]=255-io[i*dimx+j];
 }

 for(i=3;i<dimy-3;i++)
  for(j=3;j<dimx-3;j++)
{
    for(l=-3;l<4;l++)
      {
          if ((iinverse[(i-3)*dimx+j+l]==0)||(iinverse[(i+3)*dimx+j+l]==0)||(iinverse[(i+l)*dimx+j-3]==0)||(iinverse[(i+l)*dimx+j+3]==0))
            t1=1;
        }
    for (l=-2;l<3;l++)
        for (m=-2;m<3;m++)
            {
            if(iinverse[(i+l)*dimx+j+m]==255) t2=1;
            }
    if(t1==1||t2==1){  it2[i*dimx+j]=0;}
}

for(i=3;i<dimy-3;i++)
  for(j=3;j<dimx-3;j++)
  {
      if(it2[i*dimx+j]==0)
        t1=1;
      if(it[i*dimx+j]==0)
        t2=1;
      if (t1&&t2)
        ir[i*dimx+j]=0;
      else ir[i*dimx+j]=255;
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
