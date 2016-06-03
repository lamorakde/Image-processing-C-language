#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//int dimx,dimy;

FILE *fio,*fir;

int main()
{
unsigned char chi;
int max,min;
int x,y;
int test;
int *ior,*iov,*iob,*irr,*irv,*irb,*it,*it1,*it2,*it3;
long int k=3,s=1,nbg;
long int i,j,ic,jc,m,l,dimx,ff,dimy,n,taille,maxr,maxv,maxb;


char entree[35],sortie[35],chaine[10];

printf("Filter Alterne en couleur\n");
printf("Donner entree sans .ppm\n");
scanf("%s",entree);
strcat(entree,".ppm");

printf("donner sortie sans .ppm\n");
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

it=(int *)malloc(dimx*dimy*sizeof(int));
it1=(int *)malloc(dimx*dimy*sizeof(int));
it2=(int *)malloc(dimx*dimy*sizeof(int));
it3=(int *)malloc(dimx*dimy*sizeof(int));

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


//////////////////////////////////////////////////////////
/////////////////////   rouge   //////////////////////////
//////////////////////////////////////////////////////////
for(i=1;i<dimy-1;i++)
  for(j=1;j<dimx-1;j++)
{
    min=ior[(i)*dimx+j];

    for (l=-1;l<2;l++)
        for (m=-1;m<2;m++)
    {
        if ( (ior[(i+l)*dimx+j+m])< min )
        {
            min=ior[(i+l)*dimx+j+m];
        }
    }
    it1[i*dimx+j]=min;            //取最小，做腐蚀运算,erosion
}

for(i=1;i<dimy-1;i++)
  for(j=1;j<dimx-1;j++)
{
    max=it1[(i)*dimx+j];

    for (l=-1;l<2;l++)
        for (m=-1;m<2;m++)
    {
        if ( (it1[(i+l)*dimx+j+m])>max )
        {
            max=it1[(i+l)*dimx+j+m];
        }
    }
    it2[i*dimx+j]=max;            //取最大，做膨胀运算,dilation，完成开运算
}

for(i=1;i<dimy-1;i++)
  for(j=1;j<dimx-1;j++)
{
    max=it2[(i)*dimx+j];

    for (l=-1;l<2;l++)
        for (m=-1;m<2;m++)
    {
        if ( (it2[(i+l)*dimx+j+m])>max )
        {
            max=it2[(i+l)*dimx+j+m];
        }
    }
    it3[i*dimx+j]=max;            //取最大，做膨胀运算,dilatation
}

for(i=1;i<dimy-1;i++)
  for(j=1;j<dimx-1;j++)
{
    min=it3[(i)*dimx+j];

    for (l=-1;l<2;l++)
        for (m=-1;m<2;m++)
    {
        if ( (it3[(i+l)*dimx+j+m])<min )
        {
            min=it3[(i+l)*dimx+j+m];
        }
    }
    it[i*dimx+j]=min;            //取最小，做腐蚀运算,erosion，完成闭运算
}

/////////////////////////////////////////////////////////////////////////////////////

for(i=2;i<dimy-2;i++)
  for(j=2;j<dimx-2;j++)
{
    min=it[(i)*dimx+j];

    for (l=-2;l<3;l++)
        for (m=-2;m<3;m++)
    {
        if ( (it[(i+l)*dimx+j+m])< min )
        {
            min=it[(i+l)*dimx+j+m];
        }
    }
    it1[i*dimx+j]=min;            //取最小，做腐蚀运算,erosion
}

for(i=2;i<dimy-2;i++)
  for(j=2;j<dimx-2;j++)
{
    max=it1[(i)*dimx+j];

    for (l=-2;l<3;l++)
        for (m=-2;m<3;m++)
    {
        if ( (it1[(i+l)*dimx+j+m])>max )
        {
            max=it1[(i+l)*dimx+j+m];
        }
    }
    it2[i*dimx+j]=max;            //取最大，做膨胀运算,dilation，完成开运算
}


for(i=2;i<dimy-2;i++)
  for(j=2;j<dimx-2;j++)
{
    max=it2[(i)*dimx+j];

    for (l=-2;l<3;l++)
        for (m=-2;m<3;m++)
    {
        if ( (it2[(i+l)*dimx+j+m])>max )
        {
            max=it2[(i+l)*dimx+j+m];
        }
    }
    it3[i*dimx+j]=max;            //取最大，做膨胀运算,dilatation
}

for(i=2;i<dimy-3;i++)
  for(j=2;j<dimx-3;j++)
{
    min=it3[(i)*dimx+j];

    for (l=-1;l<2;l++)
        for (m=-1;m<2;m++)
    {
        if ( (it3[(i+l)*dimx+j+m])<min )
        {
            min=it3[(i+l)*dimx+j+m];
        }
    }
    irr[i*dimx+j]=min;            //取最小，做腐蚀运算,erosion，完成闭运算
}


//////////////////////////////////////////////////////////
/////////////////////   vert   //////////////////////////
//////////////////////////////////////////////////////////
for(i=1;i<dimy-1;i++)
  for(j=1;j<dimx-1;j++)
{
    min=iov[(i)*dimx+j];

    for (l=-1;l<2;l++)
        for (m=-1;m<2;m++)
    {
        if ( (iov[(i+l)*dimx+j+m])< min )
        {
            min=iov[(i+l)*dimx+j+m];
        }
    }
    it1[i*dimx+j]=min;            //取最小，做腐蚀运算,erosion
}

for(i=1;i<dimy-1;i++)
  for(j=1;j<dimx-1;j++)
{
    max=it1[(i)*dimx+j];

    for (l=-1;l<2;l++)
        for (m=-1;m<2;m++)
    {
        if ( (it1[(i+l)*dimx+j+m])>max )
        {
            max=it1[(i+l)*dimx+j+m];
        }
    }
    it2[i*dimx+j]=max;            //取最大，做膨胀运算,dilation，完成开运算
}

for(i=1;i<dimy-1;i++)
  for(j=1;j<dimx-1;j++)
{
    max=it2[(i)*dimx+j];

    for (l=-1;l<2;l++)
        for (m=-1;m<2;m++)
    {
        if ( (it2[(i+l)*dimx+j+m])>max )
        {
            max=it2[(i+l)*dimx+j+m];
        }
    }
    it3[i*dimx+j]=max;            //取最大，做膨胀运算,dilatation
}

for(i=1;i<dimy-1;i++)
  for(j=1;j<dimx-1;j++)
{
    min=it3[(i)*dimx+j];

    for (l=-1;l<2;l++)
        for (m=-1;m<2;m++)
    {
        if ( (it3[(i+l)*dimx+j+m])<min )
        {
            min=it3[(i+l)*dimx+j+m];
        }
    }
    it[i*dimx+j]=min;            //取最小，做腐蚀运算,erosion，完成闭运算
}

/////////////////////////////////////////////////////////////////////////////////////

for(i=2;i<dimy-2;i++)
  for(j=2;j<dimx-2;j++)
{
    min=it[(i)*dimx+j];

    for (l=-2;l<3;l++)
        for (m=-2;m<3;m++)
    {
        if ( (it[(i+l)*dimx+j+m])< min )
        {
            min=it[(i+l)*dimx+j+m];
        }
    }
    it1[i*dimx+j]=min;            //取最小，做腐蚀运算,erosion
}

for(i=2;i<dimy-2;i++)
  for(j=2;j<dimx-2;j++)
{
    max=it1[(i)*dimx+j];

    for (l=-2;l<3;l++)
        for (m=-2;m<3;m++)
    {
        if ( (it1[(i+l)*dimx+j+m])>max )
        {
            max=it1[(i+l)*dimx+j+m];
        }
    }
    it2[i*dimx+j]=max;            //取最大，做膨胀运算,dilation，完成开运算
}


for(i=2;i<dimy-2;i++)
  for(j=2;j<dimx-2;j++)
{
    max=it2[(i)*dimx+j];

    for (l=-2;l<3;l++)
        for (m=-2;m<3;m++)
    {
        if ( (it2[(i+l)*dimx+j+m])>max )
        {
            max=it2[(i+l)*dimx+j+m];
        }
    }
    it3[i*dimx+j]=max;            //取最大，做膨胀运算,dilatation
}

for(i=2;i<dimy-3;i++)
  for(j=2;j<dimx-3;j++)
{
    min=it3[(i)*dimx+j];

    for (l=-1;l<2;l++)
        for (m=-1;m<2;m++)
    {
        if ( (it3[(i+l)*dimx+j+m])<min )
        {
            min=it3[(i+l)*dimx+j+m];
        }
    }
    irv[i*dimx+j]=min;            //取最小，做腐蚀运算,erosion，完成闭运算
}


//////////////////////////////////////////////////////////
/////////////////////   bleu    //////////////////////////
//////////////////////////////////////////////////////////
for(i=1;i<dimy-1;i++)
  for(j=1;j<dimx-1;j++)
{
    min=iob[(i)*dimx+j];

    for (l=-1;l<2;l++)
        for (m=-1;m<2;m++)
    {
        if ( (iob[(i+l)*dimx+j+m])< min )
        {
            min=iob[(i+l)*dimx+j+m];
        }
    }
    it1[i*dimx+j]=min;            //取最小，做腐蚀运算,erosion
}

for(i=1;i<dimy-1;i++)
  for(j=1;j<dimx-1;j++)
{
    max=it1[(i)*dimx+j];

    for (l=-1;l<2;l++)
        for (m=-1;m<2;m++)
    {
        if ( (it1[(i+l)*dimx+j+m])>max )
        {
            max=it1[(i+l)*dimx+j+m];
        }
    }
    it2[i*dimx+j]=max;            //取最大，做膨胀运算,dilation，完成开运算
}

for(i=1;i<dimy-1;i++)
  for(j=1;j<dimx-1;j++)
{
    max=it2[(i)*dimx+j];

    for (l=-1;l<2;l++)
        for (m=-1;m<2;m++)
    {
        if ( (it2[(i+l)*dimx+j+m])>max )
        {
            max=it2[(i+l)*dimx+j+m];
        }
    }
    it3[i*dimx+j]=max;            //取最大，做膨胀运算,dilatation
}

for(i=1;i<dimy-1;i++)
  for(j=1;j<dimx-1;j++)
{
    min=it3[(i)*dimx+j];

    for (l=-1;l<2;l++)
        for (m=-1;m<2;m++)
    {
        if ( (it3[(i+l)*dimx+j+m])<min )
        {
            min=it3[(i+l)*dimx+j+m];
        }
    }
    it[i*dimx+j]=min;            //取最小，做腐蚀运算,erosion，完成闭运算
}

/////////////////////////////////////////////////////////////////////////////////////

for(i=2;i<dimy-2;i++)
  for(j=2;j<dimx-2;j++)
{
    min=it[(i)*dimx+j];

    for (l=-2;l<3;l++)
        for (m=-2;m<3;m++)
    {
        if ( (it[(i+l)*dimx+j+m])< min )
        {
            min=it[(i+l)*dimx+j+m];
        }
    }
    it1[i*dimx+j]=min;            //取最小，做腐蚀运算,erosion
}

for(i=2;i<dimy-2;i++)
  for(j=2;j<dimx-2;j++)
{
    max=it1[(i)*dimx+j];

    for (l=-2;l<3;l++)
        for (m=-2;m<3;m++)
    {
        if ( (it1[(i+l)*dimx+j+m])>max )
        {
            max=it1[(i+l)*dimx+j+m];
        }
    }
    it2[i*dimx+j]=max;            //取最大，做膨胀运算,dilation，完成开运算
}


for(i=2;i<dimy-2;i++)
  for(j=2;j<dimx-2;j++)
{
    max=it2[(i)*dimx+j];

    for (l=-2;l<3;l++)
        for (m=-2;m<3;m++)
    {
        if ( (it2[(i+l)*dimx+j+m])>max )
        {
            max=it2[(i+l)*dimx+j+m];
        }
    }
    it3[i*dimx+j]=max;            //取最大，做膨胀运算,dilatation
}

for(i=2;i<dimy-3;i++)
  for(j=2;j<dimx-3;j++)
{
    min=it3[(i)*dimx+j];

    for (l=-1;l<2;l++)
        for (m=-1;m<2;m++)
    {
        if ( (it3[(i+l)*dimx+j+m])<min )
        {
            min=it3[(i+l)*dimx+j+m];
        }
    }
    irb[i*dimx+j]=min;            //取最小，做腐蚀运算,erosion，完成闭运算
}


 /////////////////////////////////////////////////////////
for(i=0;i<dimy;i++)
 for(j=0;j<dimx;j++)
 { fputc((unsigned char)irr[i*dimx+j],fir);
   fputc((unsigned char)irv[i*dimx+j],fir);
   fputc((unsigned char)irb[i*dimx+j],fir);
 }


free(ior); //...

fclose(fio);fclose(fir);
return 0;
}
