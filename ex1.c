#include<stdio.h>
#include<stdlib.h>
struct node{
	int d;
	struct node *nxt;
};
int i;
struct node *head=NULL;
/*ADD ELEMENTS TO LIST*/
struct node *built123(struct node *x,int data)
{

	if(x==NULL){
		x=malloc(sizeof(struct node));
		x->d=data;
		x->nxt=NULL;
		return x;
	}
	else
		x->nxt=built123(x->nxt,data);
	
	return x;
	
}
/*PRINT LIST*/
void printlist(struct node *hea)
{
	if(hea!=NULL)
	{
		printf("o=%d\n",hea->d);
		printlist(hea->nxt);
	}
}
/*LENGTH OF LIST*/
int len(struct node *p)
{
	int count=0;
//	while(p!=NULL){
//		count++;
//		p=p->nxt;
	struct node *current;
	for (current = p; current != NULL; current = current->nxt) {	
		count++;
	}
	return count;
}
/*CALLING LENGTH*/
void LengthTest() {
	struct node* myList =head;
	int length = len(myList);
	printf("%d",length);
}
/*PUSH A NODE TO LIST*/
struct node *Push(struct node *headRef, int data)
{
	if(headRef==NULL){
		headRef=built123(headRef,1);
		return headRef;
	}
	struct node* newNode = malloc(sizeof(struct node));
	newNode->d = data;
	newNode->nxt = headRef;
	headRef = newNode;
        return headRef;
}
/*COUNT TH OCCURENCE*/
int count(struct node *x,int d)
{
	int countd=0;
	while(x!=NULL){
                if(d==x->d)
                        countd++;
                x=x->nxt;
        }
	return countd;
}
/*GET NTH*/
int g=1;
int getnth1(struct node *x,int p)
{
	int nth;
	if(x!=NULL){		
		if(g!=p){
			g++;
			nth=getnth1(x->nxt,p);
		}
		else 
			nth=x->d;
	return nth;
	
	}
}
int getnth(struct node *x,int p)
{
	int nth=getnth1(x,p);
	g=0;
	return nth;
}
/*DELETE LIST*/
struct node *deletelist(struct node **x)
{
	struct node *p=*x;
	if(p->nxt!=NULL)
		p->nxt=deletelist(&(p->nxt));
	else
		return NULL;
	*x=NULL;
	return NULL;

}
/*Build — Special Case + Tail Pointer*/
struct node* BuildWithSpecialCase() {
	struct node* h= NULL;
	struct node* tail;
	int i;
	h=Push(h, 1);
	tail = h;
	for (i=2; i<6; i++) {
	//tail=Push(tail, i); // add node at tail->next
	tail->nxt=built123(tail->nxt,i);
	tail = tail->nxt;
	}
	return h;
}
/*Build — Temporary Dummy Node*/
struct node* BuildWithDummyNode() {
	struct node dummy;
	struct node* tail = &dummy; // Start the tail at the dummy.
	int i;
	dummy.nxt = NULL;
	for (i=1; i<6; i++) {
		tail->nxt=built123(tail->nxt,i);
		tail = tail->nxt;
	}
	return(dummy.nxt);
}
/*Build — Local References*/
struct node* BuildWithLocalRef() {
	struct node* x = NULL;
	struct node** lastPtrRef= &x;
	int i;
	for (i=1; i<9; i++) {
		*lastPtrRef=built123(*lastPtrRef, i);
		lastPtrRef= &((*lastPtrRef)->nxt);
	}
	return x;
}
/*POP*/
int pop(struct node** x)
{
	struct node *cop=*x;
	int k=cop->d;
	*x=cop->nxt;	
	return k;
}
/*INSERT Nth*/
void insertnth(struct node **x,int pos,int dat)
{
	struct node *cop=*x;
	int i=0;
	if(pos==0)
	{
		cop=Push(cop,dat);
		*x=cop;
	}
	else{
		i++;
		while(cop!=NULL){
			if(pos==i){
				struct node *new=malloc(sizeof(struct node));
				new->d=dat;
				new->nxt=cop->nxt;
				cop->nxt=new;
				break;
			}
			else{
				cop=cop->nxt;
				i++;
			}
		}
	}
}
/*SORTED INSERT*/
struct node1{
	int dat;
	struct node1 *left;
	struct node1 *right;
	};
struct node1 *addtree(struct node1 *root,int da)
{
//	printf("\nd==%d",da);
        if(root==NULL){
		root=malloc(sizeof(struct node1));
		root->dat=da;
		root->right=root->left=NULL;
	}
	else if(da>root->dat)
		root->right=addtree(root->right,da);
	else if(da<root->dat)
		root->left=addtree(root->left,da);
	else
		root->left=addtree(root->left,da);
		;
	return root;
}
struct node *printlist1(struct node1 *hea,struct node *cc)
{	struct node *cop=cc;
        if(hea!=NULL&&cc!=NULL)
        {	cc=printlist1(hea->left,cc);
                cc->d=hea->dat;
		cc=cc->nxt;
                cc=printlist1(hea->right,cc);
		if(cc!=NULL)
			return cc;
        }
	return cop;
}
struct node *newnode(int d)
{
	struct node *ret=malloc(sizeof(struct node));
	ret->d=d;
	ret->nxt=NULL;
	return ret;
}
void sortins(struct node **h,struct node *newnode)
{
     if(newnode!=NULL){	
	newnode->nxt=*h;
	*h=newnode;
//	printf("%d  %d",newnode->d,newnode->nxt->d);
/*	hr=Push(hr,nw);
	*h=hr;*/
	}
     else{
	newnode=*h;
	}
	struct node *q=newnode;
//	printf("q=%d",q->d);
	struct node1 *root=NULL;
	while(q!=NULL){
		root=addtree(root,q->d);
		q=q->nxt;
	}
	printlist1(root,newnode);
}
/*INSERT SORT*/
void insertsort(struct node **h)
{
	sortins(h,NULL);
}
/*APPEND */
void append(struct node *x,struct node *y)
{
	while(x->nxt!=NULL){
		x=x->nxt;
	}
	x->nxt=y;
}
/*FRONT AND BACK SPLIT*/
void frontandbacksplit(struct node *h,struct node **front,struct node **back)
{
	int l=len(h)/2+len(h)%2;
	if(len(h)>=2)
	{
		int c=1;
		*front=h;
		while(c!=l){	
			h=h->nxt;
			c++;
		}
		*back=h->nxt;
		h->nxt=NULL;
	
	}
/*	else if(l==1){
		*frontNULL;
		*back=NULL;}printlist(*back);}*/
}
/*REMOVE DUPLICATE*/
void removedups(struct node *h)

{
	while(h!=NULL&&h->nxt!=NULL){
		if(h->d==h->nxt->d)
			h->nxt=h->nxt->nxt;
		else
			h=h->nxt;
	}
}
/*MOVE NODE*/
void movenode(struct node **h,struct node **h1)
{
	struct node *cop=*h;
	struct node *cop1=*h1;
	*h1=cop1->nxt;
	cop1->nxt=cop;
	*h=cop1;
}
/*ALTERNATING SPLIT*/
void alternatingsplit(struct node *h,struct node **aref,struct node **bref)
{
	struct node *a=malloc(sizeof(struct node));
	struct node *b=malloc(sizeof(struct node));
	*aref=a;
	*bref=b;
	while(h!=NULL){
		a->d=h->d;
		h=h->nxt;
		b->d=h->d;
		h=h->nxt;
		if(h!=NULL){
		a->nxt=malloc(sizeof(struct node));
		b->nxt=malloc(sizeof(struct node));
		a=a->nxt;a->nxt=NULL;
		b=b->nxt;b->nxt=NULL;}
	}
	
}
/*SHUFFLE MERGE*/
struct node *shufflemerge(struct node *a,struct node *b)
{
	struct node *ret=malloc(sizeof(struct node));
	struct node *retst=ret;
		while(a!=NULL||b!=NULL){
			if(a!=NULL)
				ret->d=a->d;
			if(b!=NULL){
				ret->nxt=malloc(sizeof(struct node));
                        	ret=ret->nxt;
				ret->d=b->d;
			}
			if(a!=NULL)
				a=a->nxt;
			if(b!=NULL)
				b=b->nxt;
			if(a!=NULL){
                                ret->nxt=malloc(sizeof(struct node));
                                ret=ret->nxt;
				ret->nxt=NULL;
				}

		}
	return retst;
}
/*SORTED MERGE*/
struct node *sortedmerge(struct node *a,struct node *b)
{
	struct node *ret=shufflemerge(a,b);
	sortins(&ret,NULL);
	return ret;
}
/*MERGE SORT*/
void MergeSort(struct node** headRef) {
	struct node* head = *headRef;
	struct node* a;
	struct node* b;
	if ((head == NULL) || (head->nxt == NULL)) {
		return;
	}
	frontandbacksplit(head, &a, &b);
	MergeSort(&a); 
	MergeSort(&b);
	*headRef= sortedmerge(a, b);
}
/*SORTED INTERSECT*/
struct node *sortedintersect(struct node *a,struct node *b)
{
	struct node *ret=malloc(sizeof(struct node));
	struct node *retst=ret;
	while(a!=NULL){
		ret->d=a->d;
		a=a->nxt;
		if(a!=NULL||b!=NULL){
			ret->nxt=malloc(sizeof(struct node));
			ret=ret->nxt;
		}
	}
	while(b!=NULL){
                ret->d=b->d;
                b=b->nxt;
                if(b!=NULL){
                        ret->nxt=malloc(sizeof(struct node));
                        ret=ret->nxt;
                }
        }
	return retst;
}
/*REVERSE*/
void reverse(struct node **h)
{
	struct node *cop=*h;
	int st[len(cop)],i=0;
	while(cop!=NULL){
		st[i]=cop->d;
		i++;
		cop=cop->nxt;
	}
	i--;
	cop=*h;	
	while(i>=0){
		cop->d=st[i];
		cop=cop->nxt;
		i--;
	}
}
/*RECURSIVE REVERSE*/
struct node *rev1(struct node *cop,struct node *c)
{
	struct node *h;
	if(cop->nxt==NULL){
		cop->nxt=c;
		return cop;
	}
	h=rev1(cop->nxt,cop);
	cop->nxt=c;
	return h;
}
void recreverse(struct node **h)
{
	struct node *cop=*h;
	*h=rev1(cop,NULL);
}
/*RECURSIVE REVERSE2*/
void recursivereverse(struct node **h)
{
	struct node *cop=*h;
	struct node *next=cop->nxt;
	if(cop==NULL) return;
	if(next==NULL){
		*h=cop;
		return;
	}
	recursivereverse(&(cop->nxt));
	next->nxt=cop;
	*h=cop->nxt;
	cop->nxt=NULL;
	return;
}
main()
{
	struct node *head1=NULL;
	head=BuildWithLocalRef();
	int i=5;
	while(i<12)
	{
		head1=built123(head1,i);
		i=i+1;
	}
//	printlist(head1);
//	recursivereverse(&head1);
//	printf("\n");
	printf("%d",count(head1,7));
//	struct node *aref=NULL;
//	struct node *bref=NULL;
//	printlist(head);
//	printf("\n");
//	alternatingsplit(head,&aref,&bref);
//	head=NULL;
//	printlist(head1);
//	head=shufflemerge(head,head1);
//	printlist(aref);
//	printf("\n");
//	printlist(head1);
//	printf("\n");
//	movenode(&(head->nxt->nxt),&(head1->nxt->nxt));
//	struct node *front=NULL;
//	struct node *back=NULL;
//	frontandbacksplit(head1,&front,&back);
//	append(head,head1);
//	mergesort(&head);
//	printlist(head1);
//	insertnth(&head,0,11);
//	insertsort(&head1);
//	head=NULL;
//	sortins(&head,newnode(82));
//	sortins(&head,newnode(2));
//	sortins(&head,newnode(111));
//	removedups(head1);
//	printf("pop=%d\n",pop(&head));
//	printf("pop=%d\n",pop(&head));
//	head=BuildWithDummyNode();
//	head=BuildWithSpecialCase();
//	head=built123(head,5);
//	head=built123(head,6);
//	head=Push(head,3);
//	head=Push(head,2);
//	head=Push(head,1);
//	deletelist(&head);
//	printf("getnth=%d\n",getnth(head1,0));
//	printf("getnth=%d\n",getnth(head,1));
//	printf("getnth=%d\n",getnth(head,2));
//	printf("count=%d\n",count(head,3));
//	printlist(bref);
//	printlist(head1);
//	printlist(front);
//	printf("\n");
//	printlist(head);
//	printf("len=%d\n",len(head));
}
