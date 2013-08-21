#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "math.h"

typedef enum BOOL{FALSE,TRUE} bool;

struct NODE		
{
	char *name;
	struct NODE *rchild , *lchild;
};
typedef struct NODE node;

/*node *evenSTACK, *oddSTACK, *unusedSTACK;
/*long int evenTOP = 0;
long int oddTOP = 0;
long int unusedTOP = 0;*/
node* unusedTOP;
node* evenTOP;
node* oddTOP;

int MAXnameLength = 50;
int oddCOUNT = 0;
int evenCOUNT = 0;



int largestlen =0;
int secondLargestlen = 0;	//variable to store the length of the largest string, to avoid calling strlen again and again
char *largest;		//variable storing the largest name
node *hash[50] = {}; //an array for providing open hashing, i.e. a[length] = ptr to ROOT of the Binary Search Tree containing all the names having same length


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
			if (length > MAXnameLength)
				{printf("\n\n *******SORRY only 50 alphabets allowed*****\n\n\tPlease repeat that last input");}
			else{
				char *newBuffer = realloc(buffer, maximumLength += sizeIncrement);
				if(newBuffer == NULL) { 
					free(buffer);
					return NULL; 
				}
				currentPosition = newBuffer + (currentPosition - buffer);
				buffer = newBuffer;
			}	
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

void PUSH(node *member, node *TOP){
	TOP++;
	TOP = member;
}

void inorder(node *t, size_t count, node *stackTOP)
{
    if(t!=NULL)
    {
        if (t->lchild != NULL)
        	inorder(t->lchild, count, stackTOP);	
        
        if (count > 0){
        	PUSH(t, stackTOP);
        	count--;
        }	
        else
        	PUSH(t, unusedTOP);
        // printf("%s\n",t->name);
        
        
        inorder(t->rchild, count, stackTOP);
    }
}

void makeODDheap(bool option){
	size_t i, oddLEVEL,evenLEVEL,oddREMAINING,evenREMAINING,expectedCOUNT;
	node *prevTOP;

	oddLEVEL = evenLEVEL = 1;
	if (option)
	{
		for (i=secondLargestlen; i > 1; i--)
		{
			prevTOP = oddTOP;
			if (hash[i] != NULL){
				if (i%2==0)					
					{inorder(hash[i],0,unusedTOP);}
				else
					{inorder(hash[i],(pow(i,oddLEVEL)+oddREMAINING),oddTOP);}	
				oddREMAINING = oddTOP - prevTOP;
				oddLEVEL++;				
			}			
		}
	}
	else{
		for(i = secondLargestlen; i > 1; i--)
		{
			if (hash[i] != NULL){		
				if (i%2 == 0)
				{
					prevTOP = evenTOP;
					expectedCOUNT = pow(i,evenLEVEL);
					inorder(hash[i],(expectedCOUNT+evenREMAINING),evenTOP);
					evenREMAINING = expectedCOUNT -(evenTOP - prevTOP);
				}
				else
				{
					prevTOP = oddTOP;
					expectedCOUNT = pow(i,oddLEVEL);
					inorder(hash[i],(expectedCOUNT+oddREMAINING),oddTOP);
					oddREMAINING = expectedCOUNT -(oddTOP - prevTOP);
				}
			}
		}
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
	    if(len%2 == 0)
	    	{evenCOUNT++;}
	    else
	    	{oddCOUNT++;}

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

/*
Hello There, Let's embark on this journey to figure out my Stupid code. I have added comments wherever necessary. 
*/

int main(int argc, char const *argv[])
{
	int n,i;
	char t;
	node* looper;
	/*The usual input stuff..:P*/
	printf("\nEnter The no of inputs : ");
	scanf("%d",&n);
	t=getchar(); //fflush does not works everywhere
	for (i = 0; i < n; i++)
		store(getLine());	//Yeah.. Go to store() directly, getLine() is just for taking input in a safer manner
	/*
	If sencond largest name is of odd length and it has one or more children
		then just create an ODD MAX heap
	Else create ODD MAXheap and an even MAXheap along with the usual 
	*/
	if (secondLargestlen%2 != 0) 
	{
		if((hash[secondLargestlen]->lchild != NULL) || (hash[secondLargestlen]->rchild != NULL))
		{
			/*
			The reason to use a STACK to represent a tree here is that I am using SEQUENTIAL representation of Trees.
				Refer to Page no 265 of "Data Structures using C, 2nd edition" by "Yedidyah Langsman, Aaron M Tanenbuam".
				P.S: I know u already know it...Just being polite here, no offence.
			*/
			node* unusedSTACK = (node*)malloc((((50/100)*oddCOUNT)+evenCOUNT)*sizeof(node));	//Unused Part is 50% of the toatal no odd inputs added to even inputs
			unusedTOP = unusedSTACK;	//initializing TOP
			node* oddSTACK = (node*)malloc(sizeof(node) * oddCOUNT);
			oddTOP = oddSTACK;
			makeODDheap(1);
			printf("\n\n***********ODD TREE***********\n\n");
			for(looper = oddSTACK; looper <= oddTOP ; looper++){
				printf("%s\n", looper->name);
			}
			printf("\n\n************UNUSED**********\n\n");
			for(looper = unusedSTACK; looper <= unusedTOP ; looper++){
				printf("%s\n", looper->name);
			}
		}
		else
		{
			node* unusedSTACK = (node*)malloc(((60/100)*n)*sizeof(node));
			unusedTOP = unusedSTACK;
			node* oddSTACK = (node*)malloc(sizeof(node) * oddCOUNT);
			oddTOP = oddSTACK;
			node* evenSTACK =  (node*)malloc(sizeof(node) * evenCOUNT);
			makeODDheap(1);		
		}
	}
	return 0;
}