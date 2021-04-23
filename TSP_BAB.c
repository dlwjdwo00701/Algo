#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <stdbool.h>


int travel2(int n, int** W);

typedef struct node {
   	int level;
    int *path;
    int bound;
  	struct node* next;
} node;

node* newnode(int level, int bound, int *path, int n) {
  	node* tmp = (node*)malloc(sizeof(node));
  	tmp->path=(int*)malloc(sizeof(int)*(n+1));
  	tmp->level = level;
  	tmp->bound = bound;
   	int i;
  	for(i=0;i<n-1;i++){
  	 	tmp->path[i]=path[i];
  	}
  	tmp->next=NULL;
  	return tmp;
}

node remove_(node** head) {
  	node* tmp = *head;
  	node temp;
  	(*head) = (*head)->next;
  	temp.bound=tmp->bound;
  	temp.level=tmp->level;
  	temp.path=tmp->path;
  	free(tmp);
  	return temp;
}

void insert(node** head, int level, int bound, int *path, int n) {
  	node* start = *head;
  	node* tmp = newnode(level, bound, path,n);
 	if ((*head)->bound > bound) {
 	    tmp->next = *head;
  	    (*head) = tmp;
  	} 
  	else {
   	   	while (start->next != NULL&&start->next->bound < bound) {
 	      	start = start->next;
	    }
 	    tmp->next = start->next;
 	    start->next = tmp;
 	}
}

int empty(node** head) {
   	return (*head) == NULL;
}

int bound(node v, int n, int** W){
	int i, j, bound=0;
	
	int **TMP;
	TMP=(int**)malloc(sizeof(int *)*n);
	for(i=0;i<n;i++){
		TMP[i]=(int*)malloc(sizeof(int)*n);
	}
	
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(W[i][j]==0){
				TMP[i][j]=999;
			}
			else{
				TMP[i][j]=W[i][j];
			}
		}
	}
	
	i=0;

	while(v.path[i+1]!=0){
		bound+=W[v.path[i]-1][v.path[i+1]-1];
		for(j=0;j<n;j++){
			TMP[v.path[i]-1][j]=999;
			TMP[j][v.path[i+1]-1]=999;
		}
		TMP[v.path[i+1]-1][0]=999;
		i++;
	}
	
	int min;
	for(i=0;i<n;i++){
		min=999;
		for(j=0;j<n;j++){
			if(TMP[i][j]<min){
				min=TMP[i][j];
			}
		}
		if(min!=999){
			bound+=min;
		}
	}
	
	free(TMP);
	return bound;
}

int length(int n, node u, int** W){
	int i, length=0;
	for(i=0;i<n;i++){
		length+=W[u.path[i]-1][u.path[i+1]-1];
	}
	return length;
}
	
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
	
	for(i=0;i<n;i++){
		printf("W배열의 %d행의 값들을 입력해주세요.(무한이라면 999를 입력해주세요): ",i+1);
		printf("\n");
		for(j=0;j<n;j++){
			scanf("%d",&W[i][j]);
		}
	}
	 
	int solution;
	
	solution=travel2(n,W);
	printf("\n\n----------\n최적일주여행길의 길이:%d\n\n",solution);
	
	system("PAUSE");
}

int travel2(int n, int** W){
	node *PQ;
	node u, v;
	v.path=(int*)malloc(sizeof(int)*(n+1));
	u.path=(int*)malloc(sizeof(int)*(n+1));
	
	int *opttour;
	opttour=(int *)malloc(sizeof(int)*(n+1));
	
	int i, j, here;
	for(i=0;i<n-1;i++){
		v.path[i]=0;
	}
	
	for(i=0;i<n-1;i++){
		u.path[i]=0;
	}
	
	int sum=0;
	for(i=1;i<=n;i++){
		sum+=i;
	}
	
	v.level=0;
	v.path[0]=1;
	
	v.bound=bound(v,n,W);
	int minlength=999;
	
	int sum_u;
	PQ=newnode(v.level,v.bound,v.path,n);
	while(!empty(&PQ)){
		v=remove_(&PQ);
		if(v.bound<minlength){
			u.level=v.level+1;
			for(i=2;i<=n;i++){
				here=0;
				for(j=0;j<n-1;j++){
					if(v.path[j]==i){
						here++;
					}
				}
				if(here==0){
					for(j=0;j<n-1;j++){
						u.path[j]=v.path[j];
					}
					for(j=0;j<n-1;j++){
						if(u.path[j]!=0){
							here=j;
						}
					}
					u.path[here+1]=i;
					if(u.level==n-2){
						sum_u=sum;
						for(j=0;j<n-1;j++){
							sum_u-=u.path[j];
						}
						u.path[n-1]=sum_u;
						u.path[n]=1;
						if(length(n,u,W)<minlength){
							minlength=length(n,u,W);
							for(j=0;j<n+1;j++){
								opttour[j]=u.path[j];
							}
						}
					}
					else{
						u.bound=bound(u,n,W);
						if(u.bound<minlength){
							if(PQ==NULL){
								PQ=newnode(u.level, u.bound, u.path,n);
							}
							else{
								insert(&PQ, u.level, u.bound, u.path,n);
							}
						}
					}
				}
			}
		}
	}
	
	printf("\n\n----------\n입력 행렬\n");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(W[i][j]<10){
				printf("%d  ",W[i][j]);
			}
			else if(W[i][j]==999){
				printf("∞ ");
			}
			else{
				printf("%d ",W[i][j]);
			}
		}
		printf("\n");
	}
	
	printf("\n\n----------\n최적 경로: ");
	for(i=0;i<n+1;i++){
		printf("v%d ",opttour[i]);
	}
	printf("\n");
	
	return minlength;
}
