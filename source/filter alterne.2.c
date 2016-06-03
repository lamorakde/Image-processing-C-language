#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
FILE *fio,*fir;


int main()
{
    unsigned char chi;
    int x,y;
    int test;
    int max,min;
    long int *io,*ir,*it,*it1,*it2,*it3;    // iop=iopening

    long int i,j,ic,jc,m,l,dimx,ff,dimy,n,taille,maxr,maxv,maxb;

    long int k=3,s=1,nbg;
    char entree[35],sortie[35],chaine[10];

printf("Filtre alterne\n");
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
it1=(int *)malloc(dimx*dimy*sizeof(int));
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


////////////////////////////////////////////

for(i=1;i<dimy-1;i++)
  for(j=1;j<dimx-1;j++)
{
    max=io[(i)*dimx+j];

    for (l=-1;l<2;l++)
        for (m=-1;m<2;m++)
    {
        if ( (io[(i+l)*dimx+j+m])>max )
        {
            max=io[(i+l)*dimx+j+m];
        }
    }
    it1[i*dimx+j]=max;            //取最小，做腐蚀运算,erosion
}

for(i=1;i<dimy-1;i++)
  for(j=1;j<dimx-1;j++)
{
    min=it1[(i)*dimx+j];

    for (l=-1;l<2;l++)
        for (m=-1;m<2;m++)
    {
        if ( (it1[(i+l)*dimx+j+m])<min )
        {
            min=it1[(i+l)*dimx+j+m];
        }
    }
    it2[i*dimx+j]=min;            //取最大，做膨胀运算,dilation，完成开运算
}

for(i=1;i<dimy-1;i++)
  for(j=1;j<dimx-1;j++)
{
    min=it2[(i)*dimx+j];

    for (l=-1;l<2;l++)
        for (m=-1;m<2;m++)
    {
        if ( (it2[(i+l)*dimx+j+m])<min )
        {
            min=it2[(i+l)*dimx+j+m];
        }
    }
    it3[i*dimx+j]=min;            //取最大，做膨胀运算,dilatation
}

for(i=1;i<dimy-1;i++)
  for(j=1;j<dimx-1;j++)
{
    max=it3[(i)*dimx+j];

    for (l=-1;l<2;l++)
        for (m=-1;m<2;m++)
    {
        if ( (it3[(i+l)*dimx+j+m])>max )
        {
            max=it3[(i+l)*dimx+j+m];
        }
    }
    it[i*dimx+j]=max;            //取最小，做腐蚀运算,erosion，完成闭运算
}

/////////////////////////////////////////////////////////////////////////////////////

for(i=2;i<dimy-2;i++)
  for(j=2;j<dimx-2;j++)
{
    max=it[(i)*dimx+j];

    for (l=-2;l<3;l++)
        for (m=-2;m<3;m++)
    {
        if ( (it[(i+l)*dimx+j+m])> max )
        {
            max=it[(i+l)*dimx+j+m];
        }
    }
    it1[i*dimx+j]=max;            //取最小，做腐蚀运算,erosion
}

for(i=2;i<dimy-2;i++)
  for(j=2;j<dimx-2;j++)
{
    min=it1[(i)*dimx+j];

    for (l=-2;l<3;l++)
        for (m=-2;m<3;m++)
    {
        if ( (it1[(i+l)*dimx+j+m])<min )
        {
            min=it1[(i+l)*dimx+j+m];
        }
    }
    it2[i*dimx+j]=min;            //取最大，做膨胀运算,dilation，完成开运算
}


for(i=2;i<dimy-2;i++)
  for(j=2;j<dimx-2;j++)
{
    min=it2[(i)*dimx+j];

    for (l=-2;l<3;l++)
        for (m=-2;m<3;m++)
    {
        if ( (it2[(i+l)*dimx+j+m])<min )
        {
            min=it2[(i+l)*dimx+j+m];
        }
    }
    it3[i*dimx+j]=min;            //取最大，做膨胀运算,dilatation
}

for(i=2;i<dimy-3;i++)
  for(j=2;j<dimx-3;j++)
{
    max=it3[(i)*dimx+j];

    for (l=-1;l<2;l++)
        for (m=-1;m<2;m++)
    {
        if ( (it3[(i+l)*dimx+j+m])>max )
        {
            max=it3[(i+l)*dimx+j+m];
        }
    }
    ir[i*dimx+j]=max;            //取最小，做腐蚀运算,erosion，完成闭运算
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

