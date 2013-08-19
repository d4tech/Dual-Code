#include "stdio.h"
#include "string.h"
#include "stdlib.h"

struct NODE		
{
	char *name;
	struct NODE *rchild , *lchild;
};
typedef struct NODE node;

int largestlen, secondLargestlen;	//variable to store the length of the largest string, to avoid calling strlen again and again
char *largest;		//variable storing the largest name
node *hash[' '] = {}; //an array for providing open hashing, i.e. a[length] = ptr to ROOT of the Binary Search Tree containing all the names having same length

largestlen = secondLargestlen = 0;

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



void inorder(node *t, int count)
{
    if(t!=NULL and count > 0)
    {
        inorder(t->lchild, count);
        printf("%s\n",t->name);
        count--;
        inorder(t->rchild, count);
    }
}
/*node *smallest(node *first,node *second){
	char *name1 = first->name;
	char *name2 = second->name;
	int i,temp;
	if (strlen(name1)==strlen(name2))
	{
		for (i = 0; i < strlen(name1); i++)
		{
			temp = strcmp(*(name1 + i),*(name2 + i));
			if (temp < 0)
			{
				return first;
			}
			if (temp > 0)
			{
				return second;
			}
		}
	}
	
	return NULL;

}
*/

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

int store(char *name)
{
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
	int n,i;
	char t;
	char *name;
	
	printf("\nEnter The no of inputs : ");
	scanf("%d",&n);
	
	for (i = 0; i < n; ++i)
	{
		store(getLine());	
	}

	return 0;
}