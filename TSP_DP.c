#include <stdio.h>
#include <malloc.h>
#include <math.h>


int travel(int n, int** W, int** P);

	
int main(void){
	
	int max=1000;
	int n, i, j;
	printf("n의 값을 입력해주세요: ");
	scanf("%d",&n);
	
	int **W;
	W=(int**)malloc(sizeof(int *)*n);
	for(i=0;i<n;i++){
		W[i]=(int*)malloc(sizeof(int)*n);
	}
	
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			W[i][j]=max;
		}
	}
	
	int **P;
	P=(int**)malloc(sizeof(int *)*n);
	for(i=0;i<n;i++){
		P[i]=(int*)malloc(sizeof(int)*pow(2,n-1));
	}
	
	for(i=0;i<n;i++){
		for(j=0;j<pow(2,n-1);j++){
			P[i][j]=max;
		}
	}
	
	for(i=0;i<n;i++){
		printf("W배열의 %d 행의 값들을 입력해주세요.(무한이라면 999를 입력해주세요): ",i+1);
		printf("\n");
		for(j=0;j<n;j++){
			scanf("%d",&W[i][j]);
		}
	}
	 
	int solution;
	
	solution=travel(n,W,P);
	printf("\n\n----------\n최적일주여행길의 길이:%d\n\n",solution);
	
	system("PAUSE");
}

int travel(int n, int** W, int** P){
	int i, j, k, A, max=1000;
	int minlength;
	int **D;
	D=(int**)malloc(sizeof(int *)*n);
	for(i=0;i<n;i++){
		D[i]=(int*)malloc(sizeof(int)*(pow(2,n-1)));
	}
	
	for(i=0;i<n;i++){
		for(j=0;j<pow(2,n-1);j++){
			D[i][j]=max;
		}
	}
	
	for(i=1;i<=n-1;i++){
		D[i][0]=W[i][0];
		
	}
	
	int tmp, count_A, count_i, count_j, min, where_j;
	
	for(k=1;k<=n-2;k++){
		
		for(A=1;A<pow(2,n-1);A++){
			tmp=A;
			count_A=0;
			if(tmp==1){
				count_A++;
			}
			else{
				while(tmp!=1){
					if(tmp%2==0){
						tmp/=2;
					}
					else{
						count_A++;
						tmp/=2;
					}
				}
				count_A++;
			}
			if(count_A==k){
				
				for(i=1;i<=n-1;i++){
					tmp=A+pow(2,i-1);
					count_i=0;
					while(tmp!=1){
						if(tmp%2==0){
							tmp/=2;
						}
						else{
							count_i++;
							tmp/=2;
						}
					}
					count_i++;
					if(count_i==k+1){
						
						min=999;
						where_j=1000;
						for(j=1;j<=n-1;j++){
							tmp=A+pow(2,j-1);
							count_j=0;
							while(tmp!=1){
								if(tmp%2==0){
									tmp/=2;
								}
								else{
									count_j++;
									tmp/=2;
								}
							}
							count_j++;
							if(count_j!=k+1){
								if(W[i][j]+D[j][(int)(A-pow(2,j-1))]<min){
									min=W[i][j]+D[j][(int)(A-pow(2,j-1))];
									where_j=j;
								}
								if(min==999){
									if(j<where_j){
										where_j=j;
									}
								}
							}
						}
						D[i][A]=min;
						P[i][A]=where_j;
					}
				}
			}
		}	
	}
	
	min=999;
	where_j=999;
	for(j=1;j<=n-1;j++){
		if(W[0][j]+D[j][(int)(pow(2,n-1)-pow(2,j-1)-1)]<min){
			min=W[0][j]+D[j][(int)(pow(2,n-1)-pow(2,j-1)-1)];
			where_j=j;
		}
	}
	
	D[0][(int)(pow(2,n-1))-1]=min;
	P[0][(int)(pow(2,n-1))-1]=where_j;
	
	minlength=D[0][(int)pow(2,n-1)-1];
	
	printf("\n----------\n입력행렬\n");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(W[i][j]==999){
				printf("∞ ");
			} 
			else{
				if(W[i][j]<10){
					printf("%d  ",W[i][j]);
				}
				else{
					printf("%d ",W[i][j]);
				}
			}
		}
		printf("\n");
	}
	
	printf("\n\n*각 정점들에 대한 집합의 포함 여부를 이진수로 설정해 배열을 작성했습니다.\n5번째 열의 배열일 경우 101으로 v4와v2을 포함하고 있는 집합을 나타냅니다.\n3번째 열의 경우 011으로 v3와 v2를 포함하고 있는 집합을 나타냅니다.\n\n");
	printf("\n----------\nD행렬\n");
	for(i=0;i<n;i++){
		for(j=0;j<pow(2,n-1);j++){
			if(D[i][j]==max){
				printf("x  ");
			}
			else if(D[i][j]==999){
				printf("∞ ");
			}
			else{
				if(D[i][j]<10){
					printf("%d  ",D[i][j]);
				}
				else{
					printf("%d ",D[i][j]);
				}
			}
		}
		printf("\n");
	}
	
	printf("\n----------\nP행렬\n");
	for(i=0;i<n;i++){
		for(j=0;j<pow(2,n-1);j++){
			if(P[i][j]==max){
				printf("x  ");
			}
			else if(P[i][j]==999){
				printf("∞ ");
			}
			else{
				if(P[i][j]+1<10){
					printf("%d  ",P[i][j]+1);
				}
				else{
					printf("%d ",P[i][j]+1);
				}
			}
		}
		printf("\n");
	}
	
	printf("\n----------\n최적경로\n");
	printf("v1 ");
	int where=0, tmp_v;
	int v=(int)pow(2,n-1)-1;
	for(i=1;i<=n-1;i++){
		printf("v%d ",P[where][v]+1);
		tmp_v=P[where][v];
		where=tmp_v;
		v=v-(int)pow(2,tmp_v-1);
	} 
	printf("v1 ");
	
	return minlength;
}
