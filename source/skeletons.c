#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
FILE *fio,*fir;


int main()
{
    unsigned char chi;
    int a,b,test,jump,zero;
    int circle;
    long int *io,*ir,*ic,*it,*it2,*iopen,*iresult;
    long int i,j,g,m,l,dimx,ff,dimy,n,taille,maxr,maxv,maxb;
    long int k=3,s=1,nbg;
    char entree[35],entree2[35],sortie[35],chaine[10];

printf("Skeletons \n");
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
ic=(int *)malloc(dimx*dimy*sizeof(int));
it=(int *)malloc(dimx*dimy*sizeof(int));
iopen=(int *)malloc(dimx*dimy*sizeof(int));
iresult=(int *)malloc(dimx*dimy*sizeof(int));
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


for(a=1;;a++)   //  这里需要确定跳出的条件
{
    circle=0;
    test=0;
    zero=0;
    jump=0;

    for(i=0;i<dimy;i++)
        for(j=0;j<dimx;j++)
        {
            it[i*dimx+j]=io[i*dimx+j];
            it2[i*dimx+j]=0;
            iopen[i*dimx+j]=0;
        }

    for(circle=0;circle<a;circle++)
    {
        for(i=1;i<dimy-1;i++)
            for(j=1;j<dimx-1;j++)
        {
            if((it[i*dimx+j]==255)&&(it[i*dimx+j-1]==255)&&(it[i*dimx+j+1]==255)&&(it[(i-1)*dimx+j]==255)&&(it[(i-1)*dimx+j-1]==255)&&(it[(i-1)*dimx+j+1]==255)&&(it[(i+1)*dimx+j]==255)&&(it[(i+1)*dimx+j-1]==255)&&(it[(i+1)*dimx+j+1]==255))
         {
             it2[i*dimx+j]=255;
         }
         else it2[i*dimx+j]=0;
        }

        for(i=1;i<dimy-1;i++)
            for(j=1;j<dimx-1;j++)
            {
                it[i*dimx+j]=it2[i*dimx+j];
            }
    }

    for(i=0;i<dimy;i++)
        for(j=0;j<dimx;j++)
        {
            if(it[i*dimx+j]==0)
            {
                zero=zero+1;
            }
        }

    if(zero==taille)
    {
        jump=1;
        break;
    }


    for(i=1;i<dimy-1;i++)               // first step of opening operation
        for(j=1;j<dimx-1;j++)
        {
            if((it[i*dimx+j]==255)&&(it[i*dimx+j-1]==255)&&(it[i*dimx+j+1]==255)&&(it[(i-1)*dimx+j]==255)&&(it[(i-1)*dimx+j-1]==255)&&(it[(i-1)*dimx+j+1]==255)&&(it[(i+1)*dimx+j]==255)&&(it[(i+1)*dimx+j-1]==255)&&(it[(i+1)*dimx+j+1]==255))
         {
             it2[i*dimx+j]=255;
         }
         else it2[i*dimx+j]=0;
        }

    for(i=1;i<dimy-1;i++)               // second step of opening operation
        for(j=1;j<dimx-1;j++)           // finish the opening operation
        {
            if(it2[i*dimx+j]==255)
            {
                iopen[i*dimx+j]=255;
                iopen[i*dimx+j-1]=255;
                iopen[i*dimx+j+1]=255;
                iopen[(i-1)*dimx+j]=255;
                iopen[(i-1)*dimx+j-1]=255;
                iopen[(i-1)*dimx+j+1]=255;
                iopen[(i+1)*dimx+j]=255;
                iopen[(i+1)*dimx+j-1]=255;
                iopen[(i+1)*dimx+j+1]=255;
            }
        }

    for(i=1;i<dimy-1;i++)
        for(j=1;j<dimx-1;j++)
        {
            iresult[i*dimx+j]=it[i*dimx+j]-iopen[i*dimx+j];
        }

    for(i=1;i<dimy-1;i++)
        for(j=1;j<dimx-1;j++)
        {
            if((ir[i*dimx+j]==255)||(iresult[i*dimx+j]==255))
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
