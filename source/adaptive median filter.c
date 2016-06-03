#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
FILE *fio,*fir;


int main()
{
    unsigned char chi;
    int a[9];
    int b[24];
    int x,y;
    int tp;
    int zmin,zmax,zmed,zxy;
    int A1,A2,B1,B2;
    long int *io, *ir;

    long int i,j,ic,jc,m,l,dimx,ff,dimy,n,taille,maxr,maxv,maxb;

    long int k=3,s=1,nbg;
    char entree[35],sortie[35],chaine[10];

printf("Median Filter 3*3\n");
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

for(i=2;i<dimy-2;i++)
  for(j=2;j<dimx-2;j++)
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
        for (y=x;y<9;y++)         //3*3的窗口排序，a[0]最大，a[8]最小
        {
            if (a[y]>a[x])
            {
                tp=a[y];
                a[y]=a[x];
                a[x]=tp;
            }
        }
    }
    zmin=a[8];
    zmax=a[0];
    zmed=a[4];
    zxy=io[i*dimx+j];

    A1=zmed-zmin;
    A2=zmed-zmax;
    if ((A1>0)&&(A2<0))
    {
        B1=zxy-zmin;
        B2=zxy-zmax;
        if ((B1>0)&&(B2<0)) {ir[i*dimx+j]=zxy;}
        else ir[i*dimx+j]=zmed;
    }
    else
        {
            b[0]=io[(i-2)*dimx+j-2];
            b[1]=io[(i-2)*dimx+j-1];
            b[2]=io[(i-2)*dimx+j];
            b[3]=io[(i-2)*dimx+j+1];
            b[4]=io[(i-2)*dimx+j+2];

            b[5]=io[(i-1)*dimx+j-2];
            b[6]=io[(i-1)*dimx+j-1];
            b[7]=io[(i-1)*dimx+j];
            b[8]=io[(i-1)*dimx+j+1];
            b[9]=io[(i-1)*dimx+j+2];

            b[10]=io[i*dimx+j-2];
            b[11]=io[i*dimx+j-1];
            b[12]=io[i*dimx+j];
            b[13]=io[i*dimx+j+1];
            b[14]=io[i*dimx+j+2];

            b[15]=io[(i+1)*dimx+j-2];
            b[16]=io[(i+1)*dimx+j-1];
            b[17]=io[(i+1)*dimx+j];
            b[18]=io[(i+1)*dimx+j+1];
            b[19]=io[(i+1)*dimx+j+2];

            b[20]=io[(i+2)*dimx+j-2];
            b[21]=io[(i+2)*dimx+j-1];
            b[22]=io[(i+2)*dimx+j];
            b[23]=io[(i+2)*dimx+j+1];
            b[24]=io[(i+2)*dimx+j+2];

            for(x=0;x<25;x++)
                {
                    for (y=x;y<25;y++)         //5*5的窗口排序，a[0]最大，a[8]最小
                    {
                        if (b[y]>b[x])
                        {
                            tp=b[y];
                            b[y]=b[x];
                            b[x]=tp;
                        }
                    }
                }

            zmin=b[24];
            zmax=b[0];
            zmed=b[12];
            zxy=io[i*dimx+j];

            A1=zmed-zmin;
            A2=zmed-zmax;

            if ((A1>0)&&(A2<0))
            {
                B1=zxy-zmin;
                B2=zxy-zmax;
                if ((B1>0)&&(B2<0)) {ir[i*dimx+j]=zxy;}
                else ir[i*dimx+j]=zmed;
            }
            else ir[i*dimx+j]=zmed;

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


