#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
FILE *fio,*fir;


int main()
{
    unsigned char chi;
    int a;
    int x,y,dif,jump;
    int test,test1;
    int itest,jtest;
    long int *io,*ir,*it,*iti,*itloop;
    int pointfinded;
    long int i,j,g,m,l,dimx,ff,dimy,n,taille,maxr,maxv,maxb;

    long int k=3,s=1,nbg;
    char entree[35],sortie[35],chaine[10];

printf("Thinning \n");
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
itloop=(int *)malloc(dimx*dimy*sizeof(int));
iti=(int *)malloc(dimx*dimy*sizeof(int));
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
	ir[j] = 255;
	ir[j+(dimy-1)*dimx] = 255;
}

for(i=0;i<dimy;i++)                  // 将最左最右两行的像素值置为0
{
	ir[i*dimx] = 255;
	ir[(i+1)*dimx-1] = 255;
}

////////////////////////////////////////////
for(i=1;i<dimy-1;i++)
 for(j=1;j<dimx-1;j++)
 {
     itloop[i*dimx+j]=io[i*dimx+j];
     iti[i*dimx+j]=io[i*dimx+j];
     it[i*dimx+j]=io[i*dimx+j];
 }

for(i=1;i<dimy-1;i++)
 for(j=1;j<dimx-1;j++)
 {
     if((io[i*dimx+j]==0)&&(io[(i+1)*dimx+j-1]==0)&&(io[(i+1)*dimx+j]==0)&&(io[(i+1)*dimx+j+1]==0)&&(io[(i-1)*dimx+j-1]==255)&&(io[(i-1)*dimx+j]==255)&&(io[(i-1)*dimx+j+1]==255))
     {
         it[i*dimx+j]=255;
         printf("ok");
     }

     else it[i*dimx+j]=iti[i*dimx+j];
 }

for(i=1;i<dimy-1;i++)
 for(j=1;j<dimx-1;j++)
 {
     iti[i*dimx+j]=it[i*dimx+j];
 }
    test=0;
    a=2;

for(g=0;;g++)
{

    for(i=1;i<dimy-1;i++)        //执行8个模板操作的第一部分
        for(j=1;j<dimx-1;j++)
        {
            test1=0;
            switch(a)
            {
                case 1: if((iti[i*dimx+j]==0)&&(iti[(i+1)*dimx+j-1]==0)&&(iti[(i+1)*dimx+j]==0)&&(iti[(i+1)*dimx+j+1]==0)&&(iti[(i-1)*dimx+j-1]==255)&&(iti[(i-1)*dimx+j]==255)&&(iti[(i-1)*dimx+j+1]==255))
                {
                    it[i*dimx+j]=255;
                }
                        else {it[i*dimx+j]=iti[i*dimx+j];}
                        break;

                case 2: if((iti[i*dimx+j]==0)&&(iti[i*dimx+j-1]==0)&&(iti[(i+1)*dimx+j]==0)&&(iti[(i+1)*dimx+j-1]==0)&&(iti[i*dimx+j+1]==255)&&(iti[(i-1)*dimx+j]==255)&&(iti[(i-1)*dimx+j+1]==255))
                {
                    it[i*dimx+j]=255;
                }
                        else {it[i*dimx+j]=iti[i*dimx+j];}
                        break;

                case 3: if((iti[i*dimx+j]==0)&&(iti[i*dimx+j-1]==0)&&(iti[(i-1)*dimx+j-1]==0)&&(iti[(i+1)*dimx+j-1]==0)&&(iti[i*dimx+j+1]==255)&&(iti[(i-1)*dimx+j+1]==255)&&(iti[(i+1)*dimx+j+1]==255))
                {
                    it[i*dimx+j]=255;
                }
                        else {it[i*dimx+j]=iti[i*dimx+j];}
                        break;

                case 4: if((iti[i*dimx+j]==0)&&(iti[i*dimx+j-1]==0)&&(iti[(i-1)*dimx+j]==0)&&(iti[(i-1)*dimx+j-1]==0)&&(iti[i*dimx+j+1]==255)&&(iti[(i+1)*dimx+j]==255)&&(iti[(i+1)*dimx+j+1]==255))
                {
                    it[i*dimx+j]=255;
                }
                        else {it[i*dimx+j]=iti[i*dimx+j];}
                        break;

                case 5: if((iti[i*dimx+j]==0)&&(iti[(i-1)*dimx+j]==0)&&(iti[(i-1)*dimx+j-1]==0)&&(iti[(i-1)*dimx+j+1]==0)&&(iti[(i+1)*dimx+j]==255)&&(iti[(i+1)*dimx+j-1]==255)&&(iti[(i+1)*dimx+j+1]==255))
                {
                    it[i*dimx+j]=255;
                }
                        else {it[i*dimx+j]=iti[i*dimx+j];}
                        break;

                case 6: if((iti[i*dimx+j]==0)&&(iti[i*dimx+j+1]==0)&&(iti[(i-1)*dimx+j]==0)&&(iti[(i-1)*dimx+j+1]==0)&&(iti[(i+1)*dimx+j]==255)&&(iti[(i+1)*dimx+j-1]==255)&&(iti[i*dimx+j-1]==255))
                {
                    it[i*dimx+j]=255;
                }
                        else {it[i*dimx+j]=iti[i*dimx+j];}
                        break;

                case 7: if((iti[i*dimx+j]==0)&&(iti[i*dimx+j+1]==0)&&(iti[(i-1)*dimx+j+1]==0)&&(iti[(i+1)*dimx+j+1]==0)&&(iti[i*dimx+j-1]==255)&&(iti[(i-1)*dimx+j-1]==255)&&(iti[(i+1)*dimx+j-1]==255))
                {
                    it[i*dimx+j]=255;
                }
                        else {it[i*dimx+j]=iti[i*dimx+j];}
                        break;

                case 8: if((iti[i*dimx+j]==0)&&(iti[i*dimx+j+1]==0)&&(iti[(i+1)*dimx+j]==0)&&(iti[(i+1)*dimx+j+1]==0)&&(iti[i*dimx+j-1]==255)&&(iti[(i-1)*dimx+j-1]==255)&&(iti[(i-1)*dimx+j]==255))
                {
                    it[i*dimx+j]=255;
                }
                        else {it[i*dimx+j]=iti[i*dimx+j];}
                        break;
            }
        }

        a=a+1;  // 使下次循环做8个模板中的下一个模板操作


        for(i=1;i<dimy-1;i++)
         for(j=1;j<dimx-1;j++)
            {
                iti[i*dimx+j]=it[i*dimx+j];
            }


        dif=0;  // 置区别数为0


        if(a>8)  //判别与上一次8个模板操作的结果是否有变化，如果有变化，则跳出，继续下次8个模板的操作
        {
            for(i=1;i<dimy-1;i++)
            {
                for(j=1;j<dimx-1;j++)
                 {
                    if (iti[i*dimx+j]!=itloop[i*dimx+j])
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



            for(i=1;i<dimy-1;i++)
             for(j=1;j<dimx-1;j++)
             {
                 itloop[i*dimx+j]=iti[i*dimx+j];
             }

             a=1;

        }

if(jump==1)
{
    break;
}

}


for(i=1;i<dimy-1;i++)
 for(j=1;j<dimx-1;j++)
 {
     ir[i*dimx+j]=iti[i*dimx+j];
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
