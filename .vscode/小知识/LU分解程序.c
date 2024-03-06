#include <stdio.h>  
#define N 3    

void LU_decomposition(){
	double A[N][N]={
		{1,2,3},
		{2,5,8},
		{1,0,1}
	};
	double A_n[N][N],L[N][N],U[N][N],L_n[N][N],U_n[N][N];
	
	double s;
	for(int i=0;i<N;i++) L[i][i]=1.0;//step 2
	for(int j=0;j<N;j++) U[0][j]=A[0][j];//step 3
	for(int i=1;i<N;i++) L[i][0]=A[i][0]/U[0][0];//step 4
	for(int i=1;i<N;i++){//step 5
		for(int j=i;j<N;j++){//��U
			s=0;
			for(int k=0;k<i;k++) s+=L[i][k]*U[k][j];
			U[i][j]=A[i][j]-s;
		}
		for(int d=i;d<N;d++){//��L
			s=0;
			for(int k=0;k<i;k++) s+=L[d][k]*U[k][i];
			L[d][i]=(A[d][i]-s)/U[i][i];
		}
    printf("U\n");
	  for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
		printf("%7.3f", U[i][j]);
    }
    printf("\n");
    }
    printf("L\n");
    for(int d=0;d<N;d++){
		for(int i=0;i<N;i++){
		printf("%7.3f", L[d][i]);
    }
    printf("\n");
    }

	}
	
	for(int j=0;j<N;j++){//��L����
		for(int i=j;i<N;i++){
			if(i==j) L_n[i][j]=1/L[i][j];
			else if(i<j) L_n[i][j]=0;
			else{
				s=0;
				for(int k=j;k<i;k++) s+=L[i][k]*L_n[k][j];
				L_n[i][j]=-L_n[j][j]*s;
			}
		}
	}
 
	for(int i=0;i<N;i++){//��U����
		for(int j=i;j>=0;j--){
			if(i==j) U_n[j][i] = 1 / U[j][i];
			else if(j>i) U_n[j][i] = 0;
			else{
				s=0;
				for(int k=j+1;k<=i;k++) s+=U[j][k]*U_n[k][i];
				U_n[j][i]=-1/U[j][j]*s;
			}
		}
	}
 
 
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			for(int k=0;k<N;k++){
				A_n[i][j]+=U_n[i][k]*L_n[k][j];
			}
		}
	}
 
	printf("ʹ��LU�ֽⷨ����Ľ��Ϊ��\n");
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			printf("%7.3f", A_n[i][j]);
		}
		printf("\n");
	}
}

int main(){
	LU_decomposition();
    return 0;
}
