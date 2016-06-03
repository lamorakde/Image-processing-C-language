#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
FILE *fio,*fir;


int main()
{
    unsigned char chi;
    int x,y;
    int tp;
    int max,min;
    long int *io,*ir,*it,*icl;    // iop=iopening

    long int i,j,ic,jc,m,l,dimx,ff,dimy,n,taille,maxr,maxv,maxb;

    long int k=3,s=1,nbg;
    char entree[35],sortie[35],chaine[10];

printf("Top  Hat 9*9 square\n");
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
icl=(int *)malloc(dimx*dimy*sizeof(int));
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
//  先做膨胀运算，在做腐蚀运算，为闭运算  //

for(i=3;i<dimy-3;i++)
  for(j=3;j<dimx-3;j++)
{
    max=io[(i)*dimx+j];

    for (l=-3;l<4;l++)
        for (m=-3;m<4;m++)
    {
        if ( (io[(i+l)*dimx+j+m])>max )
        {
            max=io[(i+l)*dimx+j+m];
        }
    }

    it[i*dimx+j]=max;            //取最小，做腐蚀运算,erosion
}





for(i=3;i<dimy-3;i++)
  for(j=3;j<dimx-3;j++)
{
    min=it[(i)*dimx+j];

    for (l=-3;l<4;l++)
        for (m=-3;m<4;m++)
    {
        if ( (it[(i+l)*dimx+j+m])<min )
        {
            min=it[(i+l)*dimx+j+m];
        }
    }

    icl[i*dimx+j]=min;            //取最小，做腐蚀运算,erosion
}



for(i=3;i<dimy-3;i++)
  for(j=3;j<dimx-3;j++)
  {
      ir[i*dimx+j]=icl[i*dimx+j]-io[i*dimx+j];
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
