#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
FILE *fio,*fir;

int main()
{
    unsigned char chi;

    int *ior,*iov,*iob,*irr,*irv,*irb;
    int Sx,Sy, *thetar, *thetav, *thetab;
    int sx[3][3]={{-1,0,1},{-2,0,2},{-1,0,1}};
    int sy[3][3]={{1,2,1},{0,0,0},{-1,-2,-1}};
    long int k=3,s=1,nbg;
    long int i,j,m,l,dimx,dimy,taille,maxr,maxv,maxb;
    float theta2;
    float PI = 3.141592653589793;
    int SEUIL=35;
    int DIV=4;

    char entree[35],sortie[35],chaine[10];

printf("aa donner entree sans .ppm\n");
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


 for(i=1;i<dimy-1;i++)
  for(j=1;j<dimx-1;j++)
    {
    for(l=-1;l<2;l++)
    for(m=-1;m<2;m++)
    {
       Sx+=ior[(i+l)*dimx+(j+m)]*sx[l+1][m+1];
       Sy+=ior[(i+l)*dimx+(j+m)]*sy[l+1][m+1];
    }
       irr[i*dimx+j]=(abs(Sx)+abs(Sy))/DIV;    // R分量 //

    if((irr[i*dimx+j])<=SEUIL)
    {
        theta2 = 5. ;
    }
    else if (Sx==0)
       {
           if (Sy==0) { theta2= 5.; }

		   else theta2 = PI/2.;
       }
    else theta2=atan(Sy/Sx);


			if(theta2!=5.)
			{
                if(((theta2> 3.*PI/8.)&&(theta2<=PI/2.))||(((theta2 <-(3.*PI/8.)&&(theta2>=-(PI/2.))))))
			{
				thetar[i*dimx+j] =1.;
			}
			else if ((theta2<=3.*PI/8.)&&(theta2> PI/8.))
			{
				thetar[i*dimx+j] =2.;
			}
			else if ((theta2<=PI/8.) && (theta2> -(PI/8.)))
			{
				thetar[i*dimx+j] =3.;
			}
			else if ((theta2<=-(PI/8.)) && (theta2>= -(3.*PI/8.)))
			{
				thetar[i*dimx+j] =4.;
			}
		}

    Sx=0;
    Sy=0;
    for(l=-1;l<2;l++)
    for(m=-1;m<2;m++)
    {
		Sx+=iov[(i+l)*dimx+(j+m)]*sx[l+1][m+1];    // G分量
        Sy+=iov[(i+l)*dimx+(j+m)]*sy[l+1][m+1];
    }
        irv[i*dimx+j] = (abs(Sx)+abs(Sy))/DIV;

    if((irv[i*dimx+j])<=SEUIL)
    {
        theta2 = 5. ;
    }
    else if (Sx==0)
       {
           if (Sy==0) { theta2= 5.; }

		   else theta2 = PI/2.;
       }
    else theta2=atan(Sy/Sx);

			if(theta2!=5.)
			{
                    if(((theta2> 3.*PI/8.)&&(theta2<=PI/2.))||(((theta2 <-(3.*PI/8.)&&(theta2>=-(PI/2.))))))
			{
				thetav[i*dimx+j] =1.;
			}
			else if ((theta2<=3.*PI/8.)&&(theta2> PI/8.))
			{
				thetav[i*dimx+j] =2.;
			}
			else if ((theta2<=PI/8.) && (theta2> -(PI/8.)))
			{
				thetav[i*dimx+j] =3.;
			}
			else if ((theta2<=-(PI/8.)) && (theta2>= -(3.*PI/8.)))
			{
				thetav[i*dimx+j] =4.;
			}
		}

    Sx=0;
    Sy=0;
    for(l=-1;l<2;l++)
    for(m=-1;m<2;m++)
    {
		Sx+=iob[(i+l)*dimx+(j+m)]*sx[l+1][m+1];    // B分量
        Sy+=iob[(i+l)*dimx+(j+m)]*sy[l+1][m+1];
    }
        irb[i*dimx+j] = (abs(Sx)+abs(Sy))/DIV;

       if((irb[i*dimx+j])<=SEUIL)
    {
        theta2 = 5. ;
    }
    else if (Sx==0)
       {
           if (Sy==0) { theta2= 5.; }

		   else theta2 = PI/2.;
       }
    else theta2=atan(Sy/Sx);

			if(theta2!=5.)
			{
                    if(((theta2> 3.*PI/8.)&&(theta2<=PI/2.))||(((theta2 <-(3.*PI/8.)&&(theta2>=-(PI/2.))))))
			{
				thetab[i*dimx+j] =1.;
			}
			else if ((theta2<=3.*PI/8.)&&(theta2> PI/8.))
			{
				thetab[i*dimx+j] =2.;
			}
			else if ((theta2<=PI/8.) && (theta2> -(PI/8.)))
			{
				thetab[i*dimx+j] =3.;
			}
			else if ((theta2<=-(PI/8.)) && (theta2>= -(3.*PI/8.)))
			{
				thetab[i*dimx+j] =4.;
			}
		}
    }




for(i=1;i<dimy-1;i++)
	for(j=1;j<dimx-1;j++)
	{
		if (irr[i*dimx+j]<=SEUIL)    // R分量//
		{
			irr[i*dimx+j] = 0;
		}
		else if(thetar[i*dimx+j] == 1.)
		{
			if(irr[i*dimx+j]>=irr[(i-1)*dimx+j] && irr[i*dimx+j]>=irr[(i+1)*dimx+j])
			{
				irr[i*dimx+j]=255;
			}
			else
			{
				irr[i*dimx+j]=0;
			}
		}

		else if(thetar[i*dimx+j] == 2.)
		{
			if(irr[i*dimx+j]>=irr[(i-1)*dimx+j+1] && irr[i*dimx+j]>=irr[(i+1)*dimx+j-1])
			{
				irr[i*dimx+j]=255;
			}
			else
			{
				irr[i*dimx+j]=0;
			}
		}

		else if(thetar[i*dimx+j] == 3.)
		{
			if(irv[i*dimx+j]>=irv[i*dimx+j+1] && irv[i*dimx+j]>=irv[i*dimx-1])
			{
				irr[i*dimx+j]=255;
			}
			else
			{
				irr[i*dimx+j]=0;
			}
		}

		else if(thetar[i*dimx+j] == 4.)
		{
			if(irr[i*dimx+j]>=irr[(i-1)*dimx+j-1] && irr[i*dimx+j]>=irr[(i+1)*dimx+j+1])
			{
				irr[i*dimx+j]=255;
			}
			else
			{
				irr[i*dimx+j]=0;
			}
		}


		// G分量 //
		if (irv[i*dimx+j]<=SEUIL)
		{
			irv[i*dimx+j] = 0;
		}
		else if(thetav[i*dimx+j] == 1.)
		{
			if(irv[i*dimx+j]>=irv[(i-1)*dimx+j] && irv[i*dimx+j]>=irv[(i+1)*dimx+j])
			{
				irv[i*dimx+j]=255;
			}
			else
			{
				irv[i*dimx+j]=0;
			}
		}

		else if(thetav[i*dimx+j] == 2.)
		{
			if(irv[i*dimx+j]>=irv[(i-1)*dimx+j+1] && irv[i*dimx+j]>=irv[(i+1)*dimx+j-1])
			{
				irv[i*dimx+j]=255;
			}
			else
			{
				irv[i*dimx+j]=0;
			}
		}

		else if(thetav[i*dimx+j] == 3.)
		{
			if(irv[i*dimx+j]>=irv[i*dimx+j+1] && irv[i*dimx+j]>=irv[i*dimx-1])
			{
				irv[i*dimx+j]=255;
			}
			else
			{
				irv[i*dimx+j]=0;
			}
		}

		else if(thetav[i*dimx+j] == 4.)
		{
			if(irv[i*dimx+j]>=irv[(i-1)*dimx+j-1] && irv[i*dimx+j]>=irv[(i+1)*dimx+j+1])
			{
				irv[i*dimx+j]=255;
			}
			else
			{
				irv[i*dimx+j]=0;
			}
		}


		// B分量 //
		if (irb[i*dimx+j]<=SEUIL)    // R分量//
		{
			irb[i*dimx+j] = 0;
		}
		else if(thetab[i*dimx+j] == 1.)
		{
			if(irb[i*dimx+j]>=irb[(i-1)*dimx+j] && irb[i*dimx+j]>=irb[(i+1)*dimx+j])
			{
				irb[i*dimx+j]=255;
			}
			else
			{
				irb[i*dimx+j]=0;
			}
		}

		else if(thetab[i*dimx+j] == 2.)
		{
			if(irb[i*dimx+j]>=irb[(i-1)*dimx+j+1] && irb[i*dimx+j]>=irb[(i+1)*dimx+j-1])
			{
				irb[i*dimx+j]=255;
			}
			else
			{
				irb[i*dimx+j]=0;
			}
		}

		else if(thetab[i*dimx+j] == 3.)
		{
		    if(irb[i*dimx+j]>=irb[i*dimx+j+1] && irb[i*dimx+j]>=irb[i*dimx-1])
			{
				irb[i*dimx+j]=255;
			}
			else
			{
				irb[i*dimx+j]=0;
			}
		}

		else if(thetab[i*dimx+j] == 4.)
		{
			if(irb[i*dimx+j]>=irb[(i-1)*dimx+j-1] && irb[i*dimx+j]>=irb[(i+1)*dimx+j+1])
			{
				irb[i*dimx+j]=255;
			}
			else
			{
				irb[i*dimx+j]=0;
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

