/*
 * MyDDList.c
 *
 *  Created on: 2018Äê3ÔÂ14ÈÕ
 *      Author: qy
 */


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

// all the basic data structures and functions are included in this template
// you can add your own auxiliary functions as you like

// data structures representing DLList

// data type for nodes
typedef struct DLListNode {
	int  value;  // value (int) of this list item
	struct DLListNode *prev;
	// pointer previous node in list
	struct DLListNode *next;
	// pointer to next node in list
} DLListNode;

//data type for doubly linked lists
typedef struct DLList{
	int  size;      // count of items in list
	DLListNode *first; // first node in list
	DLListNode *last;  // last node in list
} DLList;

// create a new DLListNode
DLListNode *newDLListNode(int it)
{
	DLListNode *new;
	new = malloc(sizeof(DLListNode));
	assert(new != NULL);
	new->value = it;
	new->prev = new->next = NULL;
	return new;
}

// create a new empty DLList
DLList *newDLList()
{
	struct DLList *L;

	L = malloc(sizeof (struct DLList));
	assert (L != NULL);
	L->size = 0;
	L->first = NULL;
	L->last = NULL;
	return L;
}

// insert a node into a DLList
// for reducing redundency
DLList *insertNode(struct DLList *L,struct DLListNode *new)
{
	if(L->last==NULL){
		L->first=L->last=new;
					 }
    else{
	    L->last->next= new;
		new->prev=L->last;
		L->last =new;

					 }
	L->size++;

	return L;
}


// create a DLList from a text file
// time complexity is the number of input number , O(n).
DLList *CreateDLListFromFileDlist(const char *filename)
{
 // put your code here

	DLList *L;
	DLListNode *new;
	L = newDLList();
	if(filename=="stdin"){   // filename is stdin
		char line[1000];
		while (fgets(line,1000,stdin)!=NULL) {
			if(line[0] =='\r'||line[0] == '\n'){   //an empty line denotes end of input
				return L;
			}
			else{
			int o =atoi(line);
			new = newDLListNode(o);
			L=insertNode(L,new);
			}
		}
	}
	else{       // reading all integers from a text file named filename
	FILE *fp;
	fp = fopen(filename,"r");
	int i,e;
	for(i=0;fscanf(fp,"%d",&e)!=EOF;i++){
	    new = newDLListNode(e);
	    L=insertNode(L,new);
	}
	    fclose(fp);
	}
	return L;
}

// clone a DLList
// put your time complexity analysis for cloneList() here
// time complexity is the length of list u, O(n).
DLList *cloneList(struct DLList *u)
{
 // put your code here
	DLList *L;
	DLListNode *new;
	L = newDLList();  // create a new DLList
	DLListNode *temp = u->first;
	while(temp!=NULL){  //loop of u
		new = newDLListNode(temp->value);
		L=insertNode(L,new);
	    temp=temp->next;
	}
	return L;

}

// judge a node is present in a DLList or not
// be used in the setunion
int isPresent(struct DLList *L, int data)
{
    DLListNode *t = L->first;
    while(t != NULL)
    {
        if( t->value == data )
            return 0;
        t = t->next;
    }
    return 1;
}

// compute the union of two DLLists u and v
//time complexity is length of u multiple length of v £¬O£¨n^2£©
DLList *setUnion(struct DLList *u, struct DLList *v)
{
 // put your code here
	int i;
	DLListNode *new;
	DLList *final =cloneList(u); //create a new DLList and clone u to it
	DLListNode *temp = v->first;
	for(i=0;temp!=NULL;i++){
		if(isPresent(final,temp->value)==1){  // judge if v's node in the final list
			new = newDLListNode(temp->value);
		    final->last->next=new;
		    new->prev=final->last;
		    final->last=new;
		}
		final->size++;
		temp=temp->next;
	}
	return final;
}

// compute the insection of two DLLists u and v
// put your time complexity analysis for intersection() here
//time complexity is length of u multiple length of v , O(n^2)
DLList *setIntersection(struct DLList *u, struct DLList *v)
{
  // put your code here
	DLList *final;
	DLListNode *new;
	int i,j;
	final = newDLList();
	DLListNode *temp1 = u->first;
	DLListNode *temp2 = v->first;
	for(i=0;temp1!=NULL;i++){   // loop of u
		for(j=0;temp2!=NULL;j++){  // loop of v
			if((temp1->value)==(temp2->value)){  // make comparsion of u and v's node
				new = newDLListNode(temp1->value);
				final=insertNode(final,new);
			}
		    temp2=temp2->next;
		}
		temp2=v->first;
	    temp1=temp1->next;
	}
	return(final);

}

// free up all space associated with list
// put your time complexity analysis for freeDLList() here
//time complexity is the length of L ,O(n)
void freeDLList(struct DLList *L)
{
// put your code here
	assert(L!=NULL);
	DLListNode *curr, *prev;
	curr = L->first;
	while(curr != NULL){
		prev = curr;
		curr = curr->next;
		free(prev); //free each node
	}
	free(L); // free list
}


// display items of a DLList
// put your time complexity analysis for printDDList() here
// time complexity is the length of u ,O(n)
void printDLList(struct DLList *u)
{
 // put your code here

	DLListNode *temp = u->first;
    while(temp!=NULL){
    	printf("%d ",temp->value);
    	temp= temp->next;
    }
}


int main()
{
 // put your test code here

 DLList *list1, *list2, *list3, *list4;

 list1=CreateDLListFromFileDlist("File1.txt");
 printDLList(list1);
 printf("\n");

 list2=CreateDLListFromFileDlist("File2.txt");
 printDLList(list2);
 printf("\n");

 list3=setUnion(list1, list2);
 printDLList(list3);
 printf("\n");

 list4=setIntersection(list1, list2);
 printDLList(list4);
 printf("\n");

 freeDLList(list1);
 freeDLList(list2);
 freeDLList(list3);
 freeDLList(list4);

 //printf("please type all the integers of list1\n");

 list1=CreateDLListFromFileDlist("stdin");
 printf("\n");

 //printf("please type all the integers of list2\n");

 list2=CreateDLListFromFileDlist("stdin");
 printf("\n");

 list3=cloneList(list1);
 printDLList(list3);
 printf("\n");

 list4=cloneList(list2);
 printDLList(list4);

 freeDLList(list1);
 freeDLList(list2);
 freeDLList(list3);
 freeDLList(list4);
    return 0;
}

