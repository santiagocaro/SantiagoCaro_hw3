#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

//double datos(int i, int j);
double acex(int i, int j, double *masas, double G, double *X, double *Y, double *Z, int n, double ax);
double acey(int i, int j, double *masas, double G, double *X, double *Y, double *Z, int n, double ay);
double acez(int i, int j, double *masas, double G, double *X, double *Y, double *Z, int n, double az);
void velmed(int i, int j, int n, double *Vx, double *Vy, double *Vz, double ax, double ay, double az, float dt, double *Vmx, double *Vmy, double *Vmz);
void vel(int i, int j, int n, double ax1, double ay1, double az1, float dt, double *Vx, double *Vy, double *Vz, double *Vmx, double *Vmy, double *Vmz);
void pos(int i, int j, int n, float dt, double *X, double *Y, double *Z, double *Vmx, double *Vmy, double *Vmz);
	
int main(){	
	
	FILE*file;
	file=fopen("coordinates.csv","r");
	
	int len=250;
	char line_buffer[len];
	char *split_buffer;
	const char *delimiter;
	delimiter=",";
	int i=0;
	int j=0;
	float matriz[10][7];
	while(fgets(line_buffer,len,file)){
		j=0;
		split_buffer=strtok(line_buffer,delimiter);
		while(split_buffer != NULL){
			if (j != 0)
			{
				matriz[i][j-1]=atof(split_buffer);
				//printf("%f\n",matriz[i][j-1]);
			}
			split_buffer=strtok(NULL,delimiter);
			
			j+=1;
	}
	i+=1;
	}
	//datos(0,1);
	//printf("%f\n",matriz[0][2]);
	
	int n=2000;
	float dt=0.1;
	double G=4*pow(3.1415,2);

	double *masas=malloc(10*sizeof(double));

	double *X=malloc(n*10*sizeof(double));
	double *Y=malloc(n*10*sizeof(double));
	double *Z=malloc(n*10*sizeof(double));

	double *Vx=malloc(n*10*sizeof(double));
	double *Vy=malloc(n*10*sizeof(double));
	double *Vz=malloc(n*10*sizeof(double));
	
	double *Vmx=malloc(10*sizeof(double));
	double *Vmy=malloc(10*sizeof(double));
	double *Vmz=malloc(10*sizeof(double));

	for(int i=0;i<10;i++){
	masas[i]=matriz[i][0]/matriz[0][0];
	X[i]=matriz[i][1];
	Y[i]=matriz[i][2];
	Z[i]=matriz[i][3];
	Vx[i]=matriz[i][4];
	Vy[i]=matriz[i][5];
	Vz[i]=matriz[i][6];
	//printf("%lf\n",Y[i]);
	}
	
	double ax=0.0;
	double ay=0.0;
	double az=0.0;
	double ax1=0.0;
	double ay1=0.0;
	double az1=0.0;
	
	for(i; i<10 ;i++){	
		for(j;j<n;j++){
			ax=acex(i,j,masas,G,X,Y,Z,n,ax);
			ay=acey(i,j,masas,G,X,Y,Z,n,ay);
			az=acez(i,j,masas,G,X,Y,Z,n,az);
			ax1=acex(i,(j+1),masas,G,X,Y,Z,n,ax);
			ay1=acey(i,(j+1),masas,G,X,Y,Z,n,ay);
			az1=acez(i,(j+1),masas,G,X,Y,Z,n,az);
			velmed(i,j,n,Vx,Vy,Vz,ax,ay,az,dt,Vmx,Vmy,Vmz);
			vel(i,j,n,ax1,ay1,az1,dt,Vx,Vy,Vz,Vmx,Vmy,Vmz);
			pos(i,j,n,dt,X,Y,Z,Vmx,Vmy,Vmz);
		}
	}
	return 0;
}

double acex(int i, int j, double *masas, double G, double *X, double *Y, double *Z, int n, double ax){
	for(int k=0;k<10;k++){
		if(i!=k){
		double dx=X[n*i+j]-X[n*k+j];
		double dy=Y[n*i+j]-Y[n*k+j];
		double dz=Z[n*i+j]-Z[n*k+j];
		double r=pow((pow(dx,2)+pow(dy,2)+pow(dz,2)),1.5);
		double *axx;
		axx[i]=G*masas[k]*dx/r;	
		ax=ax+axx[k];
		}
	}
return ax;
}

double acey(int i, int j, double *masas, double G, double *X, double *Y, double *Z, int n, double ay){
	for(int k=0;k<10;k++){
		if(i!=k){
		double dx=X[n*i+j]-X[n*k+j];
		double dy=Y[n*i+j]-Y[n*k+j];
		double dz=Z[n*i+j]-Z[n*k+j];
		double r=pow((pow(dx,2)+pow(dy,2)+pow(dz,2)),1.5);
		double *ayy;
		ayy[i]=G*masas[k]*dy/r;	
		ay=ay+ayy[k];
		}
	}
return ay;
}

double acez(int i, int j, double *masas, double G, double *X, double *Y, double *Z, int n, double az){
	
	for(int k=0;k<10;k++){
		if(i!=k){
		double dx=X[n*i+j]-X[n*k+j];
		double dy=Y[n*i+j]-Y[n*k+j];
		double dz=Z[n*i+j]-Z[n*k+j];
		double r=pow((pow(dx,2)+pow(dy,2)+pow(dz,2)),1.5);
		double *azz;
		azz[i]=G*masas[k]*dz/r;
		az=az+azz[k];
		}
	}
return az;
}

void velmed(int i, int j, int n, double *Vx, double *Vy, double *Vz, double ax, double ay, double az, float dt, double *Vmx, double *Vmy, double *Vmz){
	Vmx[i]=Vx[n*i+j]+0.5*ax*dt;
	Vmy[i]=Vy[n*i+j]+0.5*ay*dt;
	Vmz[i]=Vz[n*i+j]+0.5*az*dt;
}

void vel(int i, int j, int n, double ax1, double ay1, double az1, float dt, double *Vx, double *Vy, double *Vz, double *Vmx, double *Vmy, double *Vmz){
	Vx[n*i+(j+1)]=Vmx[n*i+j]+0.5*ax1*dt;
	Vy[n*i+(j+1)]=Vmy[n*i+j]+0.5*ay1*dt;
	Vz[n*i+(j+1)]=Vmz[n*i+j]+0.5*az1*dt;
}

void pos(int i, int j, int n, float dt, double *X, double *Y, double *Z, double *Vmx, double *Vmy, double *Vmz){
	X[n*i+(j+1)]=X[n*i+j]+Vmx[n*i+j]*dt;
	Y[n*i+(j+1)]=Y[n*i+j]+Vmy[n*i+j]*dt;
	Z[n*i+(j+1)]=Z[n*i+j]+Vmz[n*i+j]*dt;
}




