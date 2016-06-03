#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
FILE *fio,*fir;


int main()
{
    unsigned char chi;
    int a[9];
    int x,y,dif;
    int test;
    int itest,jtest;
    long int *io,*ir,*it,*it2,*it3;
    int pointfinded;
    long int i,j,g,m,l,dimx,ff,dimy,n,taille,maxr,maxv,maxb;

    long int k=3,s=1,nbg;
    char entree[35],sortie[35],chaine[10];

printf(" Extraction of Connected Components \n");
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
for(i=1;i<dimy-1;i++)                  // find a start point
{
  for(j=1;j<dimx-1;j++)                // find the first point which is white in the original image
    {
        if (io[i*dimx+j]==255)         // 如果在原图中是白色，置it图中对应位置为白色
        {
            it[i*dimx+j]=255;
            pointfinded=1;
            itest=i;      //test
            jtest=j;      //test
            printf("found!!!\n");      //test
            break;
        }
    }
    if (pointfinded==1)
    {
        break;
    }
}
/////

for(g=0;;g++)
{
for(i=1;i<dimy-1;i++)
  for(j=1;j<dimx-1;j++)
  {
      if(it[i*dimx+j]==255)
      {
        it2[(i-1)*dimx+j-1]=255;
        it2[(i-1)*dimx+j]=255;
        it2[(i-1)*dimx+j+1]=255;
        it2[i*dimx+j-1]=255;
        it2[i*dimx+j]=255;
        it2[i*dimx+j+1]=255;
        it2[(i+1)*dimx+j-1]=255;
        it2[(i+1)*dimx+j]=255;
        it2[(i+1)*dimx+j+1]=255;
      }
  }

for(i=1;i<dimy-1;i++)
  for(j=1;j<dimx-1;j++)
  {
      if((io[i*dimx+j]==255)&&(it2[i*dimx+j]==255))
      {
          it3[i*dimx+j]=255;
      }
  }

dif=0;

for(i=1;i<dimy-1;i++)
{
    for(j=1;j<dimx-1;j++)
  {
      if (it3[i*dimx+j]!=it[i*dimx+j])
      {
          dif=1;
          break;
      }
  }
    if(dif==1)
    {
        break;
    }
}

for(i=1;i<dimy-1;i++)
  for(j=1;j<dimx-1;j++)
  {
      it[i*dimx+j]=it3[i*dimx+j];
  }


if (dif==0)
{
    break;
}

}
/////////////////////////////////////////////

for(i=1;i<dimy-1;i++)
  for(j=1;j<dimx-1;j++)
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
