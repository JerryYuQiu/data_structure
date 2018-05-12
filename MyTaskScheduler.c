/*
 * MyTaskScheduler.c
 *
 *  Created on: 2018/5/4
 *      Author: qy
 *          id: z5170998
 */


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// all the basic data structures and functions are included in this template
// you can add your own auxiliary functions as you like

// data type for heap nodes
typedef struct HeapNode {
	// each node stores the priority (key), name, execution time,
	//  release time and deadline of one task
	int key; //key of this item
	int TaskName;  // task name
	int Etime; //execution time
	int Rtime; // release time
	int Dline; // deadline
	struct HeapNode *parent; //pointer to parent
	struct HeapNode *left; //pointer to left child
	struct HeapNode *right; //pointer to right child
} HeapNode;

//data type for a priority queue (heap)
typedef struct Heap{ //this is heap header
	int  size;      // count of items in the heap
	HeapNode *LastNode; // last node pointer
	HeapNode *root; // pointer to the root of heap
} Heap;

// create a new heap node to store an item (task)
HeapNode *newHeapNode(int k, int n, int c, int r, int d, HeapNode *L, HeapNode *R, HeapNode *P)
{ // k:key, n:task name, c: execution time, r:release time, d:deadline
  // L, R, L: pointers to left child, right child and parent, respectively
	HeapNode *new;
	new = malloc(sizeof(HeapNode));
	assert(new != NULL);
	new->key = k;
	new->TaskName = n;
	new->Etime = c;
	new->Rtime = r;
	new->Dline = d;
	new->left = L; // left child
	new->right = R; // righ child
	new->parent = P; // parent
	return new;
}

// create a new empty heap-based priority queue
 Heap *newHeap()
{ // this function creates an empty heap-based priority queue
	Heap *T;
	T = malloc(sizeof(Heap));
	assert (T != NULL);
	T->size = 0;
	T->LastNode=NULL;
	T->root = NULL;
	return T;
}

HeapNode *InsertNode(HeapNode *N, int k, int n, int c, int r, int d){

	if(N->left==NULL&&N->right==NULL){
		HeapNode * new= newHeapNode(k,n,c,r,d,NULL,NULL,N);
		N->left=new;
		return new;
	}
	else if(N->right==NULL&&N->left!=NULL){
		HeapNode * new= newHeapNode(k,n,c,r,d,NULL,NULL,N);
		N->right=new;
		return new;
	}
	else{
		int lr=0;
		int rr=0;
		HeapNode *new;
		HeapNode *leftright=N->left;
		HeapNode *rightright=N->right;
		while(leftright!=NULL){
			lr++;
			leftright=leftright->right;
		}
		while(rightright!=NULL){
			rr++;
			rightright=rightright->right;
		}
		if(lr==rr){
			new=InsertNode(N->left,k,n,c,r,d);
		}
		else{
			new=InsertNode(N->right,k,n,c,r,d);
		}

		return new;
	}
}

// put the time complexity analysis for Insert() here
// Time complexity is the height of heap,O(logn)
void Insert(Heap *T, int k, int n, int c, int r, int d)
{ // k: key, n: task name, c: execution time, r: release time, d:deadline
  // You don't need to check if this item already exists in T
  // put your code here
	HeapNode *node;
	if(T->root==NULL){
		node=newHeapNode(k,n,c,r,d,NULL,NULL,NULL);
		T->root=T->LastNode=node;
	}
	else{
		node=InsertNode(T->root,k,n,c,r,d);
		T->LastNode=node;
		HeapNode* new=node;
		while((new->parent!=NULL)&&(new->key<=new->parent->key)){
			int nk,nn,nc,nr,nd;
			nk=new->key;
			nn=new->TaskName;
			nc=new->Etime;
			nr=new->Rtime;
			nd=new->Dline;
			new->key=new->parent->key;
			new->TaskName=new->parent->TaskName;
			new->Etime=new->parent->Etime;
			new->Rtime=new->parent->Rtime;
			new->Dline=new->parent->Dline;
			new->parent->key=nk;
			new->parent->TaskName=nn;
			new->parent->Etime=nc;
			new->parent->Rtime=nr;
			new->parent->Dline=nd;
			new=new->parent;
		}
	}
	T->size++;
}


HeapNode *FindMinNode(HeapNode *N){
	if(N->left==NULL&&N->right==NULL){
		return N;
	}
	else{
		int ll=0;
		int rl=0;
		HeapNode *new;
		HeapNode *leftleft=N->left;
		HeapNode *rightleft=N->right;
		while(leftleft!=NULL){
			ll++;
		    leftleft=leftleft->left;
		}
		while(rightleft!=NULL){
			rl++;
			rightleft=rightleft->left;
		}
		if(ll==rl){
			new=FindMinNode(N->right);
		}
		else{
			new=FindMinNode(N->left);
		}
		return new;
	}
}


HeapNode *DownHeap(HeapNode *N){
	if(N->left&&N->right){
		int l,r;
		l=N->left->key;
		r=N->right->key;
		if(N->key>l||N->key>r){
			if(l<=r){
				int nk,nn,nc,nr,nd;
				nk=N->key;
				nn=N->TaskName;
				nc=N->Etime;
				nr=N->Rtime;
				nd=N->Dline;
				N->key=N->left->key;
				N->TaskName=N->left->TaskName;
				N->Etime=N->left->Etime;
				N->Rtime=N->left->Rtime;
				N->Dline=N->left->Dline;
				N->left->key=nk;
				N->left->TaskName=nn;
				N->left->Etime=nc;
				N->left->Rtime=nr;
				N->left->Dline=nd;
				N->left=DownHeap(N->left);
			}
			else{
				int nk,nn,nc,nr,nd;
				nk=N->key;
				nn=N->TaskName;
				nc=N->Etime;
				nr=N->Rtime;
				nd=N->Dline;
				N->key=N->right->key;
				N->TaskName=N->right->TaskName;
				N->Etime=N->right->Etime;
				N->Rtime=N->right->Rtime;
				N->Dline=N->right->Dline;
				N->right->key=nk;
				N->right->TaskName=nn;
				N->right->Etime=nc;
				N->right->Rtime=nr;
				N->right->Dline=nd;
				N->right=DownHeap(N->right);
			}
		}
	}

	if(N->left!=NULL&&N->right==NULL){
		if(N->left->key<N->key){
			int nk,nn,nc,nr,nd;
			nk=N->key;
			nn=N->TaskName;
			nc=N->Etime;
			nr=N->Rtime;
			nd=N->Dline;
			N->key=N->left->key;
			N->TaskName=N->left->TaskName;
			N->Etime=N->left->Etime;
			N->Rtime=N->left->Rtime;
			N->Dline=N->left->Dline;
			N->left->key=nk;
			N->left->TaskName=nn;
			N->left->Etime=nc;
			N->left->Rtime=nr;
			N->left->Dline=nd;
			N->left=DownHeap(N->left);
		}
	}

	return N;
}

// put your time complexity for RemoveMin() here
// Time complexity is the height of heap,O(logn)
HeapNode *RemoveMin(Heap *T)
{
 // put your code here
	HeapNode *Min=newHeapNode(T->root->key,T->root->TaskName,T->root->Etime,T->root->Rtime,T->root->Dline,NULL,NULL,NULL);
	T->root->key=T->LastNode->key;
	T->root->TaskName=T->LastNode->TaskName;
	T->root->Etime=T->LastNode->Etime;
	T->root->Rtime=T->LastNode->Rtime;
	T->root->Dline=T->LastNode->Dline;
	if(T->root->left==NULL&&T->root->right==NULL){
		HeapNode *r=T->root;
		T->root=NULL;
		T->LastNode=NULL;
		free(r);
		T->size--;
	}
	else if(T->root!=T->LastNode){
		if(T->LastNode->parent->right==T->LastNode){
			T->LastNode->parent->right=NULL;
		}

		if(T->LastNode->parent->left==T->LastNode){
			T->LastNode->parent->left=NULL;
		}
		T->root=DownHeap(T->root);
		HeapNode *N=T->LastNode;
		T->LastNode=FindMinNode(T->root);
		free(N);
		T->size--;
	}
	return Min;
}



int Min(Heap *T)
{
  // put your code here
	if(T->root==NULL){
		return -1;
	}
	return T->root->key;
}


// put your time complexity analysis for MyTaskScheduler here
// remove the node from T1 to T2 is O(1), remove node from T2 is height of heap O(logn)
// overall time complexity is O(nlogn)
int TaskScheduler(char *f1, char *f2, int m )
{
 // put your code here
	Heap *T1=newHeap();
	Heap *T2=newHeap();
	FILE *fp;
	fp = fopen(f1,"r");
    if(fp==NULL)
    {
        printf("file1 does not exist");
        exit(0);
    }
	int i,e;
	int n=-1,c=-1,r=-1,d=-1;
	for(i=1;fscanf(fp,"%d",&e)!=EOF;i++){
	    if(i%4==1){
	    	n=e;
	    }
	    else if(i%4==2){
	    	c=e;
	    }
	    else if(i%4==3){
	    	r=e;
	    }
	    else{
	    	d=e;
	    	if(d<r){
	            printf("input error when reading the attribute of the task X");
	            exit(0);
	    	}
	    }

	    if((n!=-1)&&(c!=-1)&&(r!=-1)&&(d!=-1)){
	    	Insert(T1,r,n,c,r,d);
	    	n=-1;
	    	c=-1;
	    	r=-1;
	    	d=-1;
	    }
	}
	fclose(fp);
	int core[m];
	int j,time;
	for(j=0;j<m;j++){
		core[j]=0;
	}

	FILE *fp1;
	fp1=fopen(f2,"w");
	for(time=0;T1->root!=NULL||T2->root!=NULL;time++){
		if(T1->root!=NULL){
			while(Min(T1)==time){
				HeapNode *M=RemoveMin(T1);
				Insert(T2,M->Dline,M->TaskName,M->Etime,M->Rtime,M->Dline);
			}
		}
	    int c;
	    for(c=0;c<m;c++){
	    	if(core[c]<time){
	    		core[c]=time;
	    	}
	    	if(core[c]==time){
				if(T2->root!=NULL){
					HeapNode *new=RemoveMin(T2);
					if(new->Etime+time>new->Dline){
						return 0;
					}
					else{
						core[c]=new->Etime+time;
						fprintf(fp1," %d core%d %d",new->TaskName,c,time);
					}
				}
	    	}
	    }
	}

	fclose(fp);
	return 1;
}

void InorderPrint(HeapNode *N){
	if(N!=NULL){
		InorderPrint(N->left);
		printf("\n(%d,%d,%d,%d,%d)",N->key,N->TaskName,N->Etime,N->Rtime,N->Dline);
		InorderPrint(N->right);
	}

}

int main() //sample main for testing
{ int i;
  i=TaskScheduler("samplefile1.txt", "feasibleschedule1.txt", 4);
  if (i==0) printf("No feasible schedule!\n");
//   There is a feasible schedule on 4 cores
  i=TaskScheduler("samplefile1.txt", "feasibleschedule2.txt", 3);
  if (i==0) printf("No feasible schedule!\n");
 //  There is no feasible schedule on 3 cores
  i=TaskScheduler("samplefile2.txt", "feasibleschedule3.txt", 5);
  if (i==0) printf("No feasible schedule!\n");
 //  There is a feasible scheduler on 5 cores
  i=TaskScheduler("samplefile2.txt", "feasibleschedule4.txt", 4);
  if (i==0) printf("No feasible schedule!\n");
 //  There is no feasible schedule on 4 cores
  i=TaskScheduler("samplefile3.txt", "feasibleschedule5.txt", 2);
  if (i==0) printf("No feasible schedule!\n");
 //  There is no feasible scheduler on 2 cores
  i=TaskScheduler("samplefile4.txt", "feasibleschedule6.txt", 2);
  if (i==0) printf("No feasible schedule!\n");
//   There is a feasible scheduler on 2 cores
  return 0;
}
