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
    long int *io, *ir;

    long int i,j,ic,jc,m,l,dimx,ff,dimy,n,taille,maxr,maxv,maxb;

    long int k=3,s=1,nbg;
    char entree[35],sortie[35],chaine[10];

printf("Max Filter 3*3\n");
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
    a[0]=io[(i-1)*dimx+j-1];
    a[1]=io[(i-1)*dimx+j];
    a[2]=io[(i-1)*dimx+j+1];
    a[3]=io[i*dimx+j-1];
    a[4]=io[i*dimx+j];          // point central
    a[5]=io[i*dimx+j+1];
    a[6]=io[(i+1)*dimx+j-1];
    a[7]=io[(i+1)*dimx+j];
    a[8]=io[(i+1)*dimx+j+1];

    for(x=0;x<9;x++)
    {
        for (y=x;y<9;y++)
        {
            if (a[y]>a[x])
            {
                tp=a[y];
                a[y]=a[x];
                a[x]=tp;
            }
        }
    }
    ir[i*dimx+j]=a[0];
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
