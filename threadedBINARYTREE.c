NODEPTR maketree(int x)
{
	NODEPTR p;

	p=getnode();
	p->info=x;
	p->left=NULL;
	p->right=NULL;
	p->rthread=TRUE;
	return(p);
}
void setleft(NODEPTR p,int x)
{
	NODEPTR q;
	if(p==NULL)
		error("void insertion");
	else if(p->left!=NULL)
		error("invalid insertion");
	else{
		q=getnode();
	q->info=x;
	p->left=q;
	q->left=NULL;
	q->right=p;
	q->rthread=TRUE;
}
}
void setright(NODEPTR p,int x)
{
	NODEPTR q,r;
	if(p==NULL)
		error("void insertion");
	else if(!p->rthread)
		error("invalid insertion");
	else{
		q=getnode();
	q->info=x;
	r=p->right;
	p->right=q;
	p->rthread=FALSE;
	q->left=NULL;
	q->right=r;
	q->rthread=TRUE;
	}
}

void intrav4(int tree)
{
	int p,q;
	p=tree;
	do{
		q=0;
		while(p!=0){
			q=p;
			p=node[p].left;
		}
		if(q!=0){
			printf("%d\n",node[q].info);
			p=mode[q].right;
			while(p<0){
				q=-p;
				printf("%d\n",node[q].info);
				p=node[q].right;
			}
		}
	}while(q!=0);
}