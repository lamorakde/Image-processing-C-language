#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define SEUIL 30
#define DIV 6

//int dimx,dimy;

FILE *fio,*fir;

int main()
{
unsigned char chi;

int *ior,*iov,*iob,*irr,*irv,*irb;
int Sx,Sy, *thetar, *thetav, *thetab;
float theta2;
float PI = 3.141592653589793;
long int k=3,s=1,nbg;
long int i,j,dimx,dimy,taille,maxr,maxv,maxb;


char entree[35],sortie[35],chaine[10];

printf("donner entree sans .ppm\n");
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

thetar=(int *)malloc(dimx*dimy*sizeof(int));
thetav=(int *)malloc(dimx*dimy*sizeof(int));
thetab=(int *)malloc(dimx*dimy*sizeof(int));

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




for(i=0;i<dimy;i++)
 for(j=0;j<dimx;j++)
 { irr[i*dimx+j]=255-ior[i*dimx+j];
   irv[i*dimx+j]=255-iov[i*dimx+j];
   irb[i*dimx+j]=255-iob[i*dimx+j];
 }

//bords haut et bas
for(j=0;j<dimx;j++)
{
	irr[j] = 0;
	irr[j+(dimy-1)*dimx] = 0;

	irv[j] = 0;
	irv[j+(dimy-1)*dimx] = 0;

	irb[j] = 0;
	irb[j+(dimy-1)*dimx] = 0;
}


//bords droits et gauches
for(i=0;i<dimy;i++)
{
	irr[i*dimx] = 0;
	irr[(i+1)*dimx-1] = 0;

	irv[i*dimx] = 0;
	irv[(i+1)*dimx-1] = 0;

	irb[i*dimx] = 0;
	irb[(i+1)*dimx-1] = 0;
}



for(i=1;i<dimy-1;i++)
 {
	for(j=1;j<dimx-1;j++)
	{
		Sx = 	-1*ior[(i-1)*dimx+j-1]
				-2*ior[(i)*dimx+j-1]
				-1*ior[(i+1)*dimx+j-1]
				+1*ior[(i-1)*dimx+j+1]
				+2*ior[(i)*dimx+j+1]
				+1*ior[(i+1)*dimx+j+1];

		Sy = 	-1*ior[(i-1)*dimx+j-1]
				-2*ior[(i-1)*dimx+j]
				-1*ior[(i-1)*dimx+j+1]
				+1*ior[(i+1)*dimx+j-1]
				+2*ior[(i+1)*dimx+j]
				+1*ior[(i+1)*dimx+j+1];

		irr[i*dimx+j] = (abs(Sx)+abs(Sy))/DIV;

		//argument

		if(Sx == 0)
		{
			thetar[i*dimx+j] = 2;
		}
		else if (irr[i*dimx+j]<SEUIL)
		{
			irr[i*dimx+j] = 0;
		}
		else
		{
			theta2 = atan(Sy/Sx);
			theta2 = fmod(theta2,PI);
			if(theta2< PI/8)
			{
				thetar[i*dimx+j] =0.;
			}
			else if (theta2< 3*PI/8)
			{
				thetar[i*dimx+j] =1.;
			}
			else if (theta2< 5*PI/8)
			{
				thetar[i*dimx+j] =2.;
			}
			else if (theta2< 7*PI/8)
			{
				thetar[i*dimx+j] =3.;
			}
			else
			{
				thetar[i*dimx+j] =0.;
			}
		}

		Sx = 	-1*iov[(i-1)*dimx+j-1]
				-2*iov[(i)*dimx+j-1]
				-1*iov[(i+1)*dimx+j-1]
				+1*iov[(i-1)*dimx+j+1]
				+2*iov[(i)*dimx+j+1]
				+1*iov[(i+1)*dimx+j+1];

		Sy = 	-1*iov[(i-1)*dimx+j-1]
				-2*iov[(i-1)*dimx+j]
				-1*iov[(i-1)*dimx+j+1]
				+1*iov[(i+1)*dimx+j-1]
				+2*iov[(i+1)*dimx+j]
				+1*iov[(i+1)*dimx+j+1];

		irv[i*dimx+j] = (abs(Sx)+abs(Sy))/DIV;

		//argument

		if(Sx == 0)
		{
			thetav[i*dimx+j] = 2;
		}
		else if (irv[i*dimx+j]<SEUIL)
		{
			irv[i*dimx+j] = 0;
		}
		else
		{
			theta2 = atan(Sy/Sx);
			theta2 = fmod(theta2,PI);
			if(theta2< PI/8)
			{
				thetav[i*dimx+j] =0.;
			}
			else if (theta2< 3*PI/8)
			{
				thetav[i*dimx+j] =1.;
			}
			else if (theta2< 5*PI/8)
			{
				thetav[i*dimx+j] =2.;
			}
			else if (theta2< 7*PI/8)
			{
				thetav[i*dimx+j] =3.;
			}
			else
			{
				thetav[i*dimx+j] =0.;
			}

		}
		Sx = 	-1*iob[(i-1)*dimx+j-1]
				-2*iob[(i)*dimx+j-1]
				-1*iob[(i+1)*dimx+j-1]
				+1*iob[(i-1)*dimx+j+1]
				+2*iob[(i)*dimx+j+1]
				+1*iob[(i+1)*dimx+j+1];

		Sy = 	-1*iob[(i-1)*dimx+j-1]
				-2*iob[(i-1)*dimx+j]
				-1*iob[(i-1)*dimx+j+1]
				+1*iob[(i+1)*dimx+j-1]
				+2*iob[(i+1)*dimx+j]
				+1*iob[(i+1)*dimx+j+1];

		irb[i*dimx+j] = (abs(Sx)+abs(Sy))/DIV;

		//argument

		if(Sx == 0)
		{
			thetab[i*dimx+j] = 2;
		}
		else if (irb[i*dimx+j]<SEUIL)
		{
			irb[i*dimx+j] = 0;
		}
		else
		{
			theta2 = atan(Sy/Sx);
			theta2 = fmod(theta2,PI);
			if(theta2< PI/8)
			{
				thetab[i*dimx+j] =0.;
			}
			else if (theta2< 3*PI/8)
			{
				thetab[i*dimx+j] =1.;
			}
			else if (theta2< 5*PI/8)
			{
				thetab[i*dimx+j] =2.;
			}
			else if (theta2< 7*PI/8)
			{
				thetab[i*dimx+j] =3.;
			}
			else
			{
				thetab[i*dimx+j] =0.;
			}
		}
	}
 }



for(i=1;i<dimy-1;i++)
 {
	for(j=1;j<dimx-1;j++)
	{
		if (irr[i*dimx+j]<SEUIL)
		{
			irr[i*dimx+j] = 0;
		}
		else if(thetar[i*dimx+j] == 0)
		{
			if(irr[i*dimx+j]>=irr[i*dimx+j+1] && irr[i*dimx+j]>=irr[i*dimx+j-1])
			{
				irr[i*dimx+j]=irr[i*dimx+j];
			}
			else
			{
				irr[i*dimx+j]=0;
			}
		}

		else if(thetar[i*dimx+j] == 1)
		{
			if(irr[i*dimx+j]>=irr[(i-1)*dimx+j+1] && irr[i*dimx+j]>=irr[(i+1)*dimx+j-1])
			{
				irr[i*dimx+j]=irr[i*dimx+j];
			}
			else
			{
				irr[i*dimx+j]=0;
			}
		}

		else if(thetar[i*dimx+j] == 2)
		{
			if(irr[i*dimx+j]>=irr[(i-1)*dimx+j] && irr[i*dimx+j]>=irr[(i+1)*dimx+j])
			{
				irr[i*dimx+j]=irr[i*dimx+j];
			}
			else
			{
				irr[i*dimx+j]=0;
			}
		}

		else if(thetar[i*dimx+j] == 3)
		{
			if(irr[i*dimx+j]>=irr[(i-1)*dimx+j-1] && irr[i*dimx+j]>=irr[(i+1)*dimx+j+1])
			{
				irr[i*dimx+j]=irr[i*dimx+j];
			}
			else
			{
				irr[i*dimx+j]=0;
			}
		}
		//vert
		if (irv[i*dimx+j]<SEUIL)
		{
			irv[i*dimx+j] = 0;
		}
		else if(thetav[i*dimx+j] == 0)
		{
			if(irv[i*dimx+j]>=irv[i*dimx+j+1] && irv[i*dimx+j]>=irv[i*dimx+j-1])
			{
				irv[i*dimx+j]=irv[i*dimx+j];
			}
			else
			{
				irv[i*dimx+j]=0;
			}
		}

		else if(thetav[i*dimx+j] == 1)
		{
			if(irv[i*dimx+j]>=irv[(i-1)*dimx+j+1] && irv[i*dimx+j]>=irv[(i+1)*dimx+j-1])
			{
				irv[i*dimx+j]=irv[i*dimx+j];
			}
			else
			{
				irv[i*dimx+j]=0;
			}
		}

		else if(thetav[i*dimx+j] == 2)
		{
			if(irv[i*dimx+j]>=irv[(i-1)*dimx+j] && irv[i*dimx+j]>=irv[(i+1)*dimx+j])
			{
				irv[i*dimx+j]=irv[i*dimx+j];
			}
			else
			{
				irv[i*dimx+j]=0;
			}
		}

		else if(thetav[i*dimx+j] == 3)
		{
			if(irv[i*dimx+j]>=irv[(i-1)*dimx+j-1] && irv[i*dimx+j]>=irv[(i+1)*dimx+j+1])
			{
				irv[i*dimx+j]=irv[i*dimx+j];
			}
			else
			{
				irv[i*dimx+j]=0;
			}
		}
		//bleu
		if (irb[i*dimx+j]<SEUIL)
		{
			irb[i*dimx+j] = 0;
		}
		else if(thetab[i*dimx+j] == 0)
		{
			if(irb[i*dimx+j]>=irb[i*dimx+j+1] && irb[i*dimx+j]>=irb[i*dimx+j-1])
			{
				irb[i*dimx+j]=irb[i*dimx+j];
			}
			else
			{
				irb[i*dimx+j]=0;
			}
		}

		else if(thetab[i*dimx+j] == 1)
		{
			if(irb[i*dimx+j]>=irb[(i-1)*dimx+j+1] && irb[i*dimx+j]>=irb[(i+1)*dimx+j-1])
			{
				irb[i*dimx+j]=irb[i*dimx+j];
			}
			else
			{
				irb[i*dimx+j]=0;
			}
		}

		else if(thetab[i*dimx+j] == 2)
		{
			if(irb[i*dimx+j]>=irb[(i-1)*dimx+j] && irb[i*dimx+j]>=irb[(i+1)*dimx+j])
			{
				irb[i*dimx+j]=irb[i*dimx+j];
			}
			else
			{
				irb[i*dimx+j]=0;
			}
		}

		else if(thetab[i*dimx+j] == 3)
		{
			if(irb[i*dimx+j]>=irb[(i-1)*dimx+j-1] && irb[i*dimx+j]>=irb[(i+1)*dimx+j+1])
			{
				irb[i*dimx+j]=irb[i*dimx+j];
			}
			else
			{
				irb[i*dimx+j]=0;
			}
		}
	}
}










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
