#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
FILE *fio,*fir;


int main()
{
    unsigned char chi;
    int a,test,dif,jump,circle;
    long int *io,*ir,*it,*it2,*icase1,*icase2,*icase3,*icase4;
    long int i,j,g,m,l,dimx,ff,dimy,n,taille,maxr,maxv,maxb;
    long int k=3,s=1,nbg;
    char entree[35],entree2[35],sortie[35],chaine[10];

printf(" Convex Hull \n");
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
it2=(int *)malloc(dimx*dimy*sizeof(int));
icase1=(int *)malloc(dimx*dimy*sizeof(int));
icase2=(int *)malloc(dimx*dimy*sizeof(int));
icase3=(int *)malloc(dimx*dimy*sizeof(int));
icase4=(int *)malloc(dimx*dimy*sizeof(int));
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

/////    case 1    /////
jump=0;
dif=0;

for(i=0;i<dimy;i++)
    for(j=0;j<dimx;j++)
    {
        it[i*dimx+j]=io[i*dimx+j];
        it2[i*dimx+j]=0;
    }

for(g=0;;g++)
{
        dif=0;

        for(i=1;i<dimy-1;i++)
        for(j=1;j<dimx-1;j++)
        {
            if((it[i*dimx+j]==0)&&(it[i*dimx+j-1]==255)&&(it[(i-1)*dimx+j-1]==255)&&(it[(i+1)*dimx+j-1]==255))
            {
                it2[i*dimx+j]=255;
            }
            else it2[i*dimx+j]=0;
        }

        for(i=1;i<dimy-1;i++)
        for(j=1;j<dimx-1;j++)
        {
            if((it[i*dimx+j]==255)||(it2[i*dimx+j]==255))
            {
                icase1[i*dimx+j]=255;
            }
            else icase1[i*dimx+j]=0;
        }


        for(i=1;i<dimy-1;i++)
            {
                for(j=1;j<dimx-1;j++)
                 {
                    if (icase1[i*dimx+j]!=it[i*dimx+j])
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

        if (dif==0)   //如果两次没有任何变化，则完成所有操作，赋值，结束程序
            {
                jump=1;
                break;
            }


        if(jump==1)
            {
                break;
            }

        for(i=1;i<dimy-1;i++)
        for(j=1;j<dimx-1;j++)
        {
            it[i*dimx+j]=icase1[i*dimx+j];
        }
}
printf("case1: ok\n");



 /////    case 2    /////
jump=0;
dif=0;


for(i=0;i<dimy;i++)
    for(j=0;j<dimx;j++)
    {
        it[i*dimx+j]=io[i*dimx+j];
        it2[i*dimx+j]=0;
    }

for(g=0; ;g++)
{
        dif=0;

        for(i=1;i<dimy-1;i++)
        for(j=1;j<dimx-1;j++)
        {
            if((it[i*dimx+j]==0)&&(it[(i-1)*dimx+j]==255)&&(it[(i-1)*dimx+j-1]==255)&&(it[(i-1)*dimx+j+1]==255))
            {
                it2[i*dimx+j]=255;
                a++;
            }
            else it2[i*dimx+j]=0;
        }

        for(i=1;i<dimy-1;i++)
        for(j=1;j<dimx-1;j++)
        {
            if((it[i*dimx+j]==255)||(it2[i*dimx+j]==255))
            {
                icase2[i*dimx+j]=255;
            }
            else icase2[i*dimx+j]=0;
        }


        for(i=1;i<dimy-1;i++)
            {
                for(j=1;j<dimx-1;j++)
                 {
                    if (icase2[i*dimx+j]!=it[i*dimx+j])
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

        if (dif==0)   //如果两次没有任何变化，则完成所有操作，赋值，结束程序
            {
                jump=1;
                break;
            }


        if(jump==1)
            {
                break;
            }

        for(i=1;i<dimy-1;i++)
        for(j=1;j<dimx-1;j++)
        {
            it[i*dimx+j]=icase2[i*dimx+j];
        }
}
printf("case2: ok\n");


/////    case 3    /////
jump=0;
dif=0;

for(i=0;i<dimy;i++)
    for(j=0;j<dimx;j++)
    {
        it[i*dimx+j]=io[i*dimx+j];
        it2[i*dimx+j]=0;
    }

for(g=0; ;g++)
{
        dif=0;

        for(i=1;i<dimy-1;i++)
        for(j=1;j<dimx-1;j++)
        {
            if((it[i*dimx+j]==0)&&(it[i*dimx+j+1]==255)&&(it[(i-1)*dimx+j+1]==255)&&(it[(i+1)*dimx+j+1]==255))
            {
                it2[i*dimx+j]=255;
            }
            else it2[i*dimx+j]=0;
        }

        for(i=1;i<dimy-1;i++)
        for(j=1;j<dimx-1;j++)
        {
            if((it[i*dimx+j]==255)||(it2[i*dimx+j]==255))
            {
                icase3[i*dimx+j]=255;
            }
            else icase3[i*dimx+j]=0;
        }

        for(i=1;i<dimy-1;i++)
            {
                for(j=1;j<dimx-1;j++)
                 {
                    if (icase3[i*dimx+j]!=it[i*dimx+j])
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

        if (dif==0)   //如果两次没有任何变化，则完成所有操作，赋值，结束程序
            {
                jump=1;
                break;
            }


        if(jump==1)
            {
                break;
            }

        for(i=1;i<dimy-1;i++)
        for(j=1;j<dimx-1;j++)
        {
            it[i*dimx+j]=icase3[i*dimx+j];
        }
}
printf("case3: ok\n");

/////    case 4    /////
jump=0;
dif=0;

for(i=0;i<dimy;i++)
    for(j=0;j<dimx;j++)
    {
        it[i*dimx+j]=io[i*dimx+j];
        it2[i*dimx+j]=0;
    }

for(g=0; ;g++)
{
        dif=0;

        for(i=1;i<dimy-1;i++)
        for(j=1;j<dimx-1;j++)
        {
            if((it[i*dimx+j]==0)&&(it[(i+1)*dimx+j]==255)&&(it[(i+1)*dimx+j-1]==255)&&(it[(i+1)*dimx+j+1]==255))
            {
                it2[i*dimx+j]=255;
            }
            else it2[i*dimx+j]=0;
        }

        for(i=1;i<dimy-1;i++)
        for(j=1;j<dimx-1;j++)
        {
            if((it[i*dimx+j]==255)||(it2[i*dimx+j]==255))
            {
                icase4[i*dimx+j]=255;
            }
            else icase4[i*dimx+j]=0;
        }

        for(i=1;i<dimy-1;i++)
            {
                for(j=1;j<dimx-1;j++)
                 {
                    if (icase4[i*dimx+j]!=it[i*dimx+j])
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

        if (dif==0)   //如果两次没有任何变化，则完成所有操作，赋值，结束程序
            {
                jump=1;
                break;
            }


        if(jump==1)
            {
                break;
            }

        for(i=1;i<dimy-1;i++)
        for(j=1;j<dimx-1;j++)
        {
            it[i*dimx+j]=icase4[i*dimx+j];
        }
}
printf("case4: ok\n");


///////////////////////////

for(i=1;i<dimy-1;i++)
 for(j=1;j<dimx-1;j++)
 {
     if((icase1[i*dimx+j]==255)||(icase2[i*dimx+j]==255)||(icase3[i*dimx+j]==255)||(icase4[i*dimx+j]==255))
     {
         ir[i*dimx+j]=255;
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
