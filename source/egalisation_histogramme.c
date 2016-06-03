#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
FILE *fio,*fir;

int main()
{
    unsigned char chi;

    int *io, *ir;
    long int i,j,m,l,dimx,ff,dimy,n,taille,maxr,maxv,maxb;
    double hist[256];
    double histc[256];
    long int LUT[256];
    double histt,f;
    double gamma=2.2;
    long int k=3,s=1,nbg;
    char entree[35],sortie[35],chaine[10];

printf("histc donner entree sans .pgm\n");
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


      // ���� //



    for (n=0;n<256;n++)
{
        hist[n]=0;           //ֱ��ͼ��ʼ��
}


    for (i=0;i<dimy;i++)
        for (j=0;j<dimx;j++)
    {
        ff=io[i*dimx+j];
        hist[ff]++;           // ����ÿ�����ص㣬��ֱ��ͼÿ���Ҷȵ�ֵ
    }



    histc[0]=hist[0];
    for (n=1;n<256;n++)
    {
        histc[n]=histc[n-1]+hist[n];      // �ҶȻ��۷ֲ����� -- histogramme cumule //
    }



    for(i=0;i<256;i++)
    {
        LUT[i]=(histc[i]*255)/(taille);   // �ҶȻ��۷ֲ����� -- ��һ�� //
            }


/*    for(n=0;n<256;n++)
        {
        printf("[%d]=%f -- %f -- %d\n",n,hist[n],histc[n],LUT[n]);    // ��ӡ��ԭֱ��ͼֵ -- ����ֱ��ͼֵ -- ��һ��ֱ��ͼֵ //
        }
*/


    for(i=0;i<dimy;i++)
    {
        for(j=0;j<dimx;j++)
        {
                ir[i*dimx+j]=LUT[io[i*dimx+j]];
        }
    }


for(i=0;i<dimy;i++)
 for(j=0;j<dimx;j++)
 {
	 fputc((unsigned char)ir[i*dimx+j],fir);   // ��� //
 }


free(io); //...

fclose(fio);fclose(fir);
return 0;
}

