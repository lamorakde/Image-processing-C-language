#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define SEUIL 30

//int dimx,dimy;

FILE *fio,*fir;

int main()
{
unsigned char chi;

int *io, *ir, Sx,Sy, *theta;
float theta2; 
float PI = 3.141592653589793;
long int k=3,s=1,nbg;
long int i,j,dimx,dimy,taille,max;


char entree[35],sortie[35],chaine[10];

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
theta=(int *)malloc(dimx*dimy*sizeof(int));

if(ir==NULL) printf("allocation iob impossible\n");

taille=dimx*dimy;
printf("taille=%d\n",taille);
for(i=0;i<dimy;i++)
 for(j=0;j<dimx;j++)
 {
  chi=(unsigned char)fgetc(fio);
  io[i*dimx+j]=(int)chi;
 }

//bords haut et bas
for(j=0;j<dimx;j++)
{
	ir[j] = 0;
	ir[j+(dimy-1)*dimx] = 0;
}
//bords droits et gauches
for(i=0;i<dimy;i++)
{
	ir[i*dimx] = 0;
	ir[(i+1)*dimx-1] = 0;
}



for(i=1;i<dimy-1;i++)
 { 
	for(j=1;j<dimx-1;j++)
	{
		Sx = 	-1*io[(i-1)*dimx+j-1]
				-2*io[(i)*dimx+j-1]
				-1*io[(i+1)*dimx+j-1]
				+1*io[(i-1)*dimx+j+1]
				+2*io[(i)*dimx+j+1]
				+1*io[(i+1)*dimx+j+1];
				
		Sy = 	-1*io[(i-1)*dimx+j-1]
				-2*io[(i-1)*dimx+j]
				-1*io[(i-1)*dimx+j+1]
				+1*io[(i+1)*dimx+j-1]
				+2*io[(i+1)*dimx+j]
				+1*io[(i+1)*dimx+j+1];
				
		ir[i*dimx+j] = (abs(Sx)+abs(Sy))/8;
		
		//argument
		
		if(Sx == 0)
		{
			theta[i*dimx+j] = 2;
		}
		else if (ir[i*dimx+j]<SEUIL)
		{
			ir[i*dimx+j] = 0;
		}
		else
		{
			theta2 = atan(Sy/Sx);
			theta2 = fmod(theta2,PI);
			if(theta2< PI/8)
			{
				theta[i*dimx+j] =0.;
			}
			else if (theta2< 3*PI/8)
			{
				theta[i*dimx+j] =1.;
			}
			else if (theta2< 5*PI/8)
			{
				theta[i*dimx+j] =2.;
			}
			else if (theta2< 7*PI/8)
			{
				theta[i*dimx+j] =3.;
			}
			else 
			{
				theta[i*dimx+j] =0.;
			}
		}
	}
 }
 
 
 
for(i=1;i<dimy-1;i++)
 { 
	for(j=1;j<dimx-1;j++)
	{
		if (ir[i*dimx+j]<SEUIL)
		{
			ir[i*dimx+j] = 0;
		}
		else if(theta[i*dimx+j] == 0)
		{
			if(ir[i*dimx+j]>=ir[i*dimx+j+1] && ir[i*dimx+j]>=ir[i*dimx+j-1])
			{
				ir[i*dimx+j]=ir[i*dimx+j];
			}
			else
			{
				ir[i*dimx+j]=0;
			}
		}
		
		else if(theta[i*dimx+j] == 1)
		{
			if(ir[i*dimx+j]>=ir[(i-1)*dimx+j+1] && ir[i*dimx+j]>=ir[(i+1)*dimx+j-1])
			{
				ir[i*dimx+j]=ir[i*dimx+j];
			}
			else
			{
				ir[i*dimx+j]=0;
			}
		}
		
		else if(theta[i*dimx+j] == 2)
		{
			if(ir[i*dimx+j]>=ir[(i-1)*dimx+j] && ir[i*dimx+j]>=ir[(i+1)*dimx+j])
			{
				ir[i*dimx+j]=ir[i*dimx+j];
			}
			else
			{
				ir[i*dimx+j]=0;
			}
		}
		
		else if(theta[i*dimx+j] == 3)
		{
			if(ir[i*dimx+j]>=ir[(i-1)*dimx+j-1] && ir[i*dimx+j]>=ir[(i+1)*dimx+j+1])
			{
				ir[i*dimx+j]=ir[i*dimx+j];
			}
			else
			{
				ir[i*dimx+j]=0;
			}
		}
	}
}
 
 
 







for(i=0;i<dimy;i++)
 for(j=0;j<dimx;j++)
 { 
	 fputc((unsigned char)ir[i*dimx+j],fir);
 }


free(io); //...

fclose(fio);fclose(fir);
return 0;
}
