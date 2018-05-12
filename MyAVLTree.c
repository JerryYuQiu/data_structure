/*
 * MyAVLTree.c
 *
 *  Created on: 2018Äê4ÔÂ11ÈÕ
 *      Author: qy
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

// all the basic data structures and functions are included in this template
// you can add your own auxiliary functions as you like

// data type for avl tree nodes
typedef struct AVLTreeNode {
	int key; //key of this item
	int  value;  //value (int) of this item
	int height; //height of the subtree rooted at this node
	struct AVLTreeNode *parent; //pointer to parent
	struct AVLTreeNode *left; //pointer to left child
	struct AVLTreeNode *right; //pointer to right child
} AVLTreeNode;

//data type for AVL trees
typedef struct AVLTree{
	int  size;      // count of items in avl tree
	AVLTreeNode *root; // root
} AVLTree;

// create a new AVLTreeNode
AVLTreeNode *newAVLTreeNode(int k, int v )
{
	AVLTreeNode *new;
	new = malloc(sizeof(AVLTreeNode));
	assert(new != NULL);
	new->key = k;
	new->value = v;
	new->height = 0; // height of this new node is set to 0
	new->left = NULL; // this node has no child
	new->right = NULL;
	new->parent = NULL; // no parent
	return new;
}

// create a new empty avl tree
AVLTree *newAVLTree()
{
	AVLTree *T;
	T = malloc(sizeof (AVLTree));
	assert (T != NULL);
	T->size = 0;
	T->root = NULL;
	return T;
}

AVLTreeNode *Search(AVLTree *T, int k);
void Insert(AVLTreeNode *N,int k, int v);

// put your time complexity analysis of CreateAVLTree() here
// time complexity is the number of node n times single insertion logn,O(nlogn)
AVLTree *CreateAVLTree(const char *filename)
{
 // put your code here
	AVLTree *T;
	AVLTreeNode *new;
    T=newAVLTree();
    if(filename=="stdin"){ // if stdin
    	int i,key=0,value=0;
    	int flag=0;
    	int judge=0;
    	char line[1000];
    	int k;
    	while (fgets(line,1000,stdin)!=NULL) {
    	    if(line[0] =='\r'||line[0] == '\n'){   //an empty line denotes end of input
    	    	return T;
    	    					}
    	    else{
    	        for(i=0;i<=sizeof(line);i++){
    	    		if((line[i]=='(')){
    	    			flag=1;
    	    		}
    	   			else if(isdigit(line[i])&&flag==1){
    	   				if(judge==0){
    	   				    key=key*10+line[i]-'0';
    	   				}
        				else{
   	    					key=key*10-(line[i]-'0');
   	    				}
   	    			}
   	    			else if(line[i]==','){
   	    				flag=2;
    	    			judge=0;
    	    		}
    	    		else if(isdigit(line[i])&&flag==2){
    	   				if(judge==0){
    	   				    value=value*10+line[i]-'0';
    	   				}
       				    else{
   	    					value=value*10-(line[i]-'0');
   	    				}
   	    			}
   	    			else if((line[i]==')')&&flag==2){
   	    				InsertNode(T,key,value);
    	    			key=0;
    	    			value=0;
    	    			flag=0;
    	   				judge=0;
    	            }
    	    		else if(line[i]=='-'){
    	    			judge=1;
    	    		}
    	    		else if(line[i]==' '){
        			//	k=0;

    	    			}
    	    		else{
    	   				key=0;
    	   				value=0;
    	   				flag=0;
    	   				judge=0;
    	    			}
    	    		}
    	    					}
    	    		}
    }
    else{ // read from files
    	FILE *fp;
    	fp = fopen(filename,"r");
    	int i,key=0,value=0;
    	int flag=0;
    	int judge=0;
    	char line[1000];
    	while (fgets(line,1000,fp)!=NULL) {
    		for(i=0;i<=sizeof(line);i++){
    			if((line[i]=='(')){
    				flag=1;
    			}
    			else if(isdigit(line[i])&&flag==1){
    				if(judge==0){
    				    key=key*10+line[i]-'0';
    				}
    				else{
    					key=key*10-(line[i]-'0');
    				}
    			}
    			else if(line[i]==','){
    				flag=2;
    				judge=0;
    			}
    			else if(isdigit(line[i])&&flag==2){
    				if(judge==0){
    				    value=value*10+line[i]-'0';
    				}
    				else{
    					value=value*10-(line[i]-'0');
    				}
    			}
    			else if((line[i]==')')&&flag==2){
    				InsertNode(T,key,value);
    				key=0;
    				value=0;
    				flag=0;
    				judge=0;

    			}
    			else if(line[i]=='-'){
    				judge=1;
    			}
    			else{
    				key=0;
    				value=0;
    				flag=0;
    				judge=0;
    			}
    		}
    		}


    }
    return T;

}


void *PreorderClone(AVLTree *T,AVLTreeNode *N)
{
	if(N!=NULL){
			if(T->root==NULL){
			   AVLTreeNode *new ;
			   new = newAVLTreeNode(N->key,N->value);
			   T->root=new;
			   //new->height++;
			   T->size++;
			}
			else {
				Insert(T->root,N->key,N->value);
				T->size++;
			}
			PreorderClone(T,N->left);
			PreorderClone(T,N->right);
		}
	}

// put your time complexity analysis for CloneAVLTree() here
// time complexity is the number of nodes times single insertion, O(nlogn)
AVLTree *CloneAVLTree(AVLTree *T)
{
 // put your code here
	AVLTree *new;
	new =newAVLTree();
	if(T != NULL){
		PreorderClone(new,T->root);
	}
	return new;
}


void InorderArray(AVLTreeNode *new,int key[],int value[],int *i){

	if(new!=NULL){
	    InorderArray(new->left,key,value,i);
	    key[*i]=new->key;
	    value[*i]=new->value;
	    (*i)++;
	    InorderArray(new->right,key,value,i);
	}
}

//mergr the key array
void MergeTwoArray_value(int MergeValue[],int key1[],int key2[],int value1[],int value2[],int m,int n){
	int i=0,j=0,k=0;
    while(i<m&&j<n){
    	if(key1[i]<key2[j]){
    		MergeValue[k]=value1[i];
    		i++;
    	}
    	else{
    		MergeValue[k]=value2[j];
    		j++;
    	}
    	k++;
    }

    while(i<m){
    	MergeValue[k]=value1[i];
    	i++;
    	k++;
    }

    while(j<n){
    	MergeValue[k]=value2[j];
    	j++;
    	k++;
    }


}

//merge the value array
void MergeTwoArray_key(int Mergekey[],int key1[],int key2[],int m,int n){
    int i=0;
    int j=0;
    int k=0;

    while(i<m&&j<n){
    	if(key1[i]<key2[j]){
    		Mergekey[k]=key1[i];
    		i++;
        	k++;
    	}
    	else{
    		Mergekey[k]=key2[j];
    		j++;
        	k++;
    	}
    }

    while(i<m&&j>=n){
    	Mergekey[k]=key1[i];
    	i++;
    	k++;
    }

    while(j<n&&i>=m){
    	Mergekey[k]=key2[j];
    	j++;
    	k++;
    }

}

// convert array to tree
//AVLTree *Array_to_Tree(AVLTree *new,int key[],int value[],int start,int end){
AVLTreeNode *Array_to_Tree(AVLTreeNode *parent,int key[],int value[],int start,int end,int height){
	if(start<=end){
		AVLTreeNode *new;
		int middle=0;
		if((start+end)%2==0){
	        middle =(start+end)/2;
		}
		else{
			middle =(start+end+1)/2;
		}
        new = newAVLTreeNode(key[middle],value[middle]);
		if(parent){
		    new->parent=parent;
		}
		new->height=height;
		new->left = Array_to_Tree(new,key,value,start,middle-1,height+1);
		new->right = Array_to_Tree(new,key,value,middle+1,end,height+1);
	    return new;
	}
	else{
		return NULL;
	}

}

// put your time complexity for MergeTwoALVTrees() here
// first convert two Trees into two ordered array , time complexity is the length of two trees ,O(n)and O(m)
// second merge two arrays into one, time complexity is O(n+m)
// finally change the array into Tree by binary insert ,every single insert is O(1),time complexity is O(m+n)
// so the final time complexity is O(m+n)
AVLTree *MergeTwoAVLTrees(AVLTree *T1, AVLTree *T2)
{
	//put your code here
	AVLTree *new;
	new=newAVLTree();
	AVLTreeNode *parent;
	int m = T1->size;
	int n = T2->size;
	int Array1_key[m];
	int Array1_value[m];
	int Array2_key[n];
	int Array2_value[n];
	int MergeValue[m+n];
	int MergeKey[m+n];
	int i=0;
	int j=0;
	int start=0;
	int end=m+n-1;
	int t=0;
	InorderArray(T1->root,Array1_key,Array1_value,&i);
	InorderArray(T2->root,Array2_key,Array2_value,&j);
	MergeTwoArray_key(MergeKey,Array1_key,Array2_key,m,n);
	MergeTwoArray_value(MergeValue,Array1_key,Array2_key,Array1_value,Array2_value,m,n);
//	new = Array_to_Tree(new,MergeKey,MergeValue,start,end);
	new->root = Array_to_Tree(new->root,MergeKey,MergeValue,start,end,0);
	new->size=m+n;
	FreeAVLTree(T1);
	FreeAVLTree(T2);
	return new;
}

// compute the deepest height of a node
int height(AVLTreeNode *node){
	int height_left = 0;
	int height_right = 0;

	if( node->left ) {
		height_left = height( node->left );
	}
	if( node->right ) {
		height_right = height( node->right );
	}

	return height_right > height_left ? ++height_right : ++height_left;
}

//judge if it is LL or LR ,RR or RL
int dif(AVLTreeNode *node){
	int diff=0;
	if(node->left){
		diff += height(node->left);
	}
	if(node->right){
		diff -= height(node->right);
	}

	return diff;
}

//rotation left-left
AVLTreeNode *Rotation_LL(AVLTreeNode *c){
	AVLTreeNode *z = c;
	AVLTreeNode *y = z->left;
	AVLTreeNode *x = y->left;
	z->left= y->right;
	if(y->right!=NULL){
		y->right->parent=c;
	}
	y->parent=z->parent;
	y->right= z;
	z->parent =y;
	return y;
}

//rotation right-right
AVLTreeNode *Rotation_RR(AVLTreeNode *c){
	AVLTreeNode *z = c;
	AVLTreeNode *y = z->right;
	AVLTreeNode *x = y->right;
	z->right= y->left;
	if(y->left!=NULL){
	y->left->parent=z;
	}
	y->parent=z->parent;
	y->left= z;
	z->parent =y;
	return y;
}

//rotation left-right
AVLTreeNode *Rotation_LR(AVLTreeNode *c){
	AVLTreeNode *z = c;
	AVLTreeNode *y = z->left;
	AVLTreeNode *x = y->right;
	z->left=x->right;
	if(x->right!=NULL){
	x->right->parent=z;
	}
	y->right=x->left;
	if(x->left!=NULL){
	x->left->parent=y;
	}
	x->parent=z->parent;
	x->left=y;
	y->parent=x;
	x->right=z;
	z->parent=x;
	return x;
}

//rotation right-left
AVLTreeNode *Rotation_RL(AVLTreeNode *c){
	AVLTreeNode *z = c;
	AVLTreeNode *y = z->right;
	AVLTreeNode *x = y->left;
	z->right=x->left;
	if(x->left!=NULL){
	x->left->parent=z;
	}
	y->left=x->right;
	if(x->right!=NULL){
	x->right->parent=y;
	}
	x->parent=z->parent;
	x->right=y;
	y->parent=x;
	x->left=z;
	z->parent=x;
	return x;
}

//revalue the height after rotation
void Balance_height(AVLTreeNode *root,int h){
	if(root!=NULL){
		if(root->height!=h){
			root->height=h;
		}
		if(root->left){
			Balance_height(root->left,h+1);
		}
		if(root->right){
			Balance_height(root->right,h+1);
		}
	}
}

//input is the root of tree, output is the new root after rotation
AVLTreeNode *Balance(AVLTreeNode *node){

	AVLTreeNode *new;

	if(node->left){
		node->left = Balance(node->left);
	}
	if(node->right){
		node->right = Balance(node->right);
	}

	int diff =dif(node);

    if(diff >=2){
    	if(dif(node->left)<=-1){
/*    	{
    		new =node;
    	    printf("**");}*/
    		new = Rotation_LR(node);
    	}
    	else
    	{
    		new = Rotation_LL(node);
    	}
    }
    else if(diff<=-2){
    	if(dif(node->right)>=1){
    	    new = Rotation_RL(node);
    	}
    	else{
    	    new = Rotation_RR(node);
    	}

    }
    else{
    	new=node;
    }

    return(new);
}

//maintaining height
void Balance_tree(AVLTree *T){
	AVLTreeNode *new;
	new = Balance(T->root);
	Balance_height(new,0);
	T->root= new;

}

//input is the root of tree, insert node
void Insert(AVLTreeNode *N,int k, int v)
{
	if(k <= N->key){
		if(N->left==NULL){
			AVLTreeNode *new ;
			new = newAVLTreeNode(k,v);
			N->left=new;
			new->parent=N;
			new->height=new->parent->height + 1;
			}
		else{
			Insert(N->left,k,v);
			}
	}
	else{
		if(N->right==NULL){
			AVLTreeNode *new ;
			new = newAVLTreeNode(k,v);
			N->right=new;
			new->parent=N;
			new->height=new->parent->height + 1;
		}
		else{
			Insert(N->right,k,v);
		}
	}
}

// put the time complexity analysis for InsertNode() here
// insert time complexity is the height, O(log n),balance time complexity is also O(log n),so the final time complexity is O(log n).
int InsertNode(AVLTree *T, int k, int v)
{
//put your code here
	if(T->root==NULL){
	   AVLTreeNode *new ;
	   new = newAVLTreeNode(k,v);
	   T->root=new;
	   T->size++;
	   return 1;
	}
	else {
		if(Search(T,k)==NULL){
		    Insert(T->root,k,v);
		    T->size++;
			Balance_tree(T);
		    return 1;
		}
		else{
			return 0;
		}
	}



//	return 0;
}

//input is the node to be deleted ,output is its immediate_inorder_successor
AVLTreeNode * immediate_inorder_successor(AVLTreeNode *N){
	AVLTreeNode *new =N;
	if(new->left!=NULL){
		immediate_inorder_successor(new->left);
	}
	else{
		return new;
	}
}

// put your time complexity for DeleteNode() here
// because this is delete by key, so the time complexity is find the key logn,balance logn ,O(logn)
int DeleteNode(AVLTree *T, int k)
{
 // put your code here
	if(Search(T,k)==NULL){ // if there's no node
		return 0;
	}
	else{
	    AVLTreeNode *new;
	    new = Search(T,k);
	    if(new->left==NULL){
	    	if(new->right==NULL){  // the node has no children
	    		if(new->parent){
	    		    if(new->parent->left==new){
	    			    new->parent->left=NULL;
	    		    }
	    		    else{
	    			    new->parent->right=NULL;
	    		    }
	    		    free(new);
	    		    Balance_tree(T);
	    		    T->size--;
	    		}
	    		else{ // this is the last node
	    			free(new);
	    //			free(T);
	    		}
	    		return 1;
	    	}
	    	else{  // only has right sub node
	    		new->right->height--;
	    		if(new->parent){
	    		    new->right->parent=new->parent;
	    		    if(new->parent->left==new){
	    			    new->parent->left=new->right;
	    		    }
	    		    else{
	    			    new->parent->right=new->right;
	    		    }
	    		    Balance_tree(T);
	    		    free(new);
	    		}
	    		else{ // if it is root
	    			new->key=new->right->key;
	    			new->value=new->right->value;
	    			new->right=NULL;
	    		}
	    		Balance_tree(T);
	    		T->size--;
	    		return 1;
	    	}
	    }
	    else{
	    	if(new->right==NULL){ //only has left sub node
	    		new->left->height--;
	    		if(new->parent){
	    		    new->left->parent=new->parent;
	    		    if(new->parent->left==new){
	    			    new->parent->left=new->left;
	    		    }
	    		    else{
	    			    new->parent->right=new->left;
	    		    }
	    		    Balance_tree(T);
	    	//	new->parent->left=new->left;
	    		    free(new);
	    		}
	    		else{ // if it is node
	    			new->key=new->left->key;
	    			new->value=new->left->value;
	    			new->left=NULL;
	    	//	free(new->left);
	    		}

	    		T->size--;
	    		return 1;
	    	}
	    	else{ //have both sub nodes
	    		AVLTreeNode *iis=immediate_inorder_successor(new->right); //this is immediate_inorder_successor
	    		new->key=iis->key;
	    		new->value=iis->value;
	    		if(iis->right){
	    			iis->right->height--;
	    			iis->right->parent=iis->parent;
	    		}
	    		if(iis->parent->left==iis){
	    		    iis->parent->left=iis->right;
	    		}
	    		else{
	    			iis->parent->right=iis->right;
	    		}
	    		free(iis);
	    		Balance_tree(T);
	    		T->size--;
	    		return 1;
	    	}
	    }
	}
}


// put your time complexity analysis for Search() here
// the time complexity is the height of the tree,O(log n)
AVLTreeNode *Search(AVLTree *T, int k)
{
  // put your code here
	if(T==NULL){
		return NULL;
	}
	else{
		AVLTreeNode *curr =T->root;
		while(curr&&curr->key!=k){
			if(k<curr->key){
				curr=curr->left;
			}
			else{
				curr=curr->right;
			}
		}
		return curr;

	}

}


//input is the root of Tree , free each node in postorder
void FreeAVL(AVLTreeNode *N){
	if(N!=NULL){
	FreeAVL(N->left);
	FreeAVL(N->right);
	free(N);
	}
}

// put your time complexity analysis for freeAVLTree() here
// the time complexity is the number of nodes ,O(n)
void FreeAVLTree(AVLTree *T)
{
// put your code here
	if(T->root!=NULL){
		FreeAVL(T->root);
	}
	free(T);
}

//input is the root of tree, print in inorder
void InorderPrint(AVLTreeNode *N){
	if(N!=NULL){
		InorderPrint(N->left);
		printf("(%d,%d)",N->key,N->value);
	//	printf("(%d,%d,%d)",N->key,N->value,N->height);
		InorderPrint(N->right);
	}

}
// put your time complexity analysis for PrintAVLTree() here
// time complexity is the number of nodes ,O(n)
void PrintAVLTree(AVLTree *T)
{
 // put your code here
	if(T != NULL){
		InorderPrint(T->root);
	}
}

int main()
{
 //test code will be released soon

	int i,j;
	 AVLTree *tree1, *tree2, *tree3, *tree4;
	 AVLTreeNode *node1;

	 tree1=CreateAVLTree("stdin");
	 PrintAVLTree(tree1);
	 printf("\n");
	 //you need to create the text file file1.txt
	 // to store a set of items with distinct keys
	 tree2=CreateAVLTree("file1.txt");
	 PrintAVLTree(tree2);
	 printf("\n");
	 tree3=CloneAVLTree(tree2);
	 tree4=MergeTwoAVLTrees(tree1,tree2);
	 PrintAVLTree(tree3);
	 printf("\n");
	 printf("the merge of the two tree is:");
	 PrintAVLTree(tree4);
	 printf("\n");
/*	 FreeAVLTree(tree1);
	 FreeAVLTree(tree2);*/
	 FreeAVLTree(tree3);
	 FreeAVLTree(tree4);
	 tree4=newAVLTree();
	 j=InsertNode(tree4, 10, 10);
	 for (i=0; i<15; i++)
	  {
	   j=InsertNode(tree4, i, i);
	    PrintAVLTree(tree4);
	    printf("\n");
	   if (j==0) printf("(%d, %d) already exists/n", i, i);
	  }
	  PrintAVLTree(tree4);
	  printf("\n");
	  node1=Search(tree4,20);
	  if (node1!=NULL)
	    printf("key= %d value= %d\n",node1->key,node1->value);
	  else
	    printf("Key 20 does not exist\n");

	  for (i=17; i>0; i--)
	  {
	    j=DeleteNode(tree4, i);
		if (j==0)
		  printf("Key %d does not exist\n",i);
	    PrintAVLTree(tree4);
	    printf("\n");
	  }
	 FreeAVLTree(tree4);
	 return 0;
}
