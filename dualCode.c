#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "math.h"

// enum bool 

struct NODE		
{
	char *name;
	struct NODE *parent, *rchild , *lchild;
};
typedef struct NODE node;

node evenSTACK[' '],oddSTACK[' '], unused[' '];
long int evenTOP = 0;
long int oddTOP = 0;
long int unusedTOP = 0;


int largestlen =0;
int secondLargestlen = 0;	//variable to store the length of the largest string, to avoid calling strlen again and again
char *largest;		//variable storing the largest name
node *hash[' '] = {}; //an array for providing open hashing, i.e. a[length] = ptr to ROOT of the Binary Search Tree containing all the names having same length


//Function to accept input
char *getLine(void) {
	const size_t sizeIncrement = 10; 
	char* buffer = malloc(sizeIncrement); 
	char* currentPosition = buffer; 
	size_t maximumLength = sizeIncrement; 
	size_t length = 0;
	int character;

	if(currentPosition == NULL) { return NULL; }
	
	while(1) {
		character = fgetc(stdin); 
		if(character == '\n') { break; }

		if(++length >= maximumLength) {
			char *newBuffer = realloc(buffer, maximumLength += sizeIncrement);
			if(newBuffer == NULL) { 
				free(buffer);
				return NULL; 
			}
			currentPosition = newBuffer + (currentPosition - buffer);
			buffer = newBuffer;
		}
		*currentPosition++ = character;
	}
	*currentPosition = '\0';
	return buffer; 
}



void saferFree(void **pp) {
	if (pp != NULL && *pp != NULL) {
		free(*pp);
		*pp = NULL; 
	}
}

void PUSH(node *NewNode,node *STACK, long int *TOP){
	TOP++;
	STACK[TOP] = NewNode;
}

void inorder(node *t, int count, node *STACK, long int *TOP)
{
    if(t!=NULL)
    {
        if (t->lchild != NULL)
        	inorder(t->lchild, count);	
        
        if (count > 0)
        	PUSH(t, STACK, TOP);
        
        PUSH(t, unused, unusedTOP);
        // printf("%s\n",t->name);
        count--;
        
        inorder(t->rchild, count);
    }
}

void createHeap(int start, node *STACK, long int TOP){
	int i, level;
	level = 1;
	for (i=start; i > 1; i-=2)
	{
		if (hash[i] != NULL)
			inorder(hash[i],pow(2,level),STACK, TOP);

			
	}
}

int BSTinsert(node *q, node *NewNode){
	int st;
	node *p;
	while(q!=NULL)
    {
        if(strcmp(NewNode->name, q->name) < 0)
        {
            p=q;
            q=q->lchild;
            st=1;
        }
        else if(strcmp(NewNode->name, q->name) > 0)
        {
            p=q;
            q=q->rchild;
            st=2;
        }
        else
        {
            printf("DUPLICATE VALUE");
            return 0;
        }
    }
    if(st==1)
    	p->lchild = NewNode;
    else if(st==2)
    	p->rchild = NewNode;

    NewNode->parent = p;
    return 0;
}

int store(char *name){
    int st=0, len;
    node *NewNode;
    
    NewNode = (node *)malloc(sizeof(node));
    
    if (NewNode == NULL)
		{printf("\n\n**********************\nERROR : No more Memory Available\n*********************\n\n");}

	else{
	    NewNode->name = name;
	    NewNode->lchild = NewNode->rchild = NULL;

	    // The Block of code responsible for keeping track of the Largest and the second Largest names;
	    len = strlen(name); 
	    if (largestlen < len){
	    	
	    	secondLargestlen = largestlen;
	    	largest = name;
	    	largestlen = len;
    	}
	    
	    // If a name of particular length has been seen for the first time 
	    //			then make it the root
	    // Else 
	    //			call the BSTinsert(Root from hash table, NewNode)
	    if(hash[len] == NULL)        
	        hash[len] = NewNode;
	    else	
		    BSTinsert(hash[len], NewNode);   
	}    
    return 0;
}



int main(int argc, char const *argv[])
{
	long int n,i;
	char t;
	
	printf("\nEnter The no of inputs : ");
	n = (int)getLine();
	// t = getchar();
	for (i = 0; i < n; ++i)
		store(getLine());	

	if (secondLargestlen%2 != 0)
	{
		if((hash[secondLargestlen]->lchild != NULL) || (hash[secondLargestlen]->rchild != NULL))
		{
			oddTOP++;
			createHeap(secondLargestlen, oddSTACK, oddTOP ); 
		}
	}	

	return 0;
}