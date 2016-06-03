#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
FILE *fio,*fir;


int main()
{
    unsigned char chi;

    long int *io, *ir;
    double result_tp;
    double it;
    long int i,j,ic,jc,m,l,dimx,ff,dimy,n,taille,maxr,maxv,maxb;

    long int k=3,s=1,nbg;
    char entree[35],sortie[35],chaine[10];

printf("Harmonic mean filter 3*3\n");
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
    result_tp=0;
    for(l=-1;l<2;l++)
    for(m=-1;m<2;m++)
    {
       it=io[(i+l)*dimx+(j+m)];
       result_tp+=1./it;

    }

    ir[i*dimx+j]= 9./result_tp;

}

/*
for(l=-1;l<2;l++)
    for(m=-1;m<2;m++)
    {
       it=io[(5+l)*dimx+(7+m)];
       result_tp+=1./it;
       printf("io[(5+%d)*dimx+(7+%d)]=%d   it=%f   result=%f\n",l,m,io[(5+l)*dimx+(7+m)],it,result_tp);

    }
    ir[5*dimx+7]= 9./result_tp;
    printf("result=%f  ir=%d\n",result_tp,ir[5*dimx+7]);
    printf("io[5*dimx+7]=%d  ir[5*dimx+7]=%d\n",io[5*dimx+7],ir[5*dimx+7]);
*/

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

