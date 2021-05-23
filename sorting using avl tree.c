//AVL TREE WITH COUNT

#include<stdio.h>
#include<stdlib.h>

struct node{
	int key;
	int count;
	int height;
	struct node* left;
	struct node* right;
};

struct node* NewNode(int key){
	struct node* temp = (struct node*)malloc(sizeof(struct node));
	temp->key = key;
	temp->count =1;
	temp->height =0;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}
int Height(struct node* temp){
if(temp == NULL)return -1;
else return temp->height;
}

int GETBALANCE(struct node* temp){
	if(temp == NULL)return 0;
	return (Height(temp->left)-Height(temp->right));
}

struct node* RIGHTROTATE(struct node* temp){
	struct node* left = temp->left;
	struct node* right = left->right;
	left->right=temp;
	temp->left = right;
	
	temp->height = 1+((Height(temp->left)>Height(temp->right))?Height(temp->left):Height(temp->right));
	
	left->height= 1+((Height(left->left)>Height(left->right))?Height(left->left):Height(left->right));
	return left;
}

struct node* LEFTROTATE(struct node* temp){
	struct node* rightnode = temp->right;
	struct node* leftnode = rightnode->left;
	rightnode->left = temp;
	temp->right = leftnode;
	
	temp->height = 1+((Height(temp->left)>Height(temp->right))?Height(temp->left):Height(temp->right));
	rightnode->height = 1+((Height(rightnode->left)>Height(rightnode->right))?Height(rightnode->left):Height(rightnode->right));
	return rightnode;
}
struct node* INSERT(struct node* head,int k){
	if(head == NULL)return NewNode(k);
	else if(head->key > k){
		head->left = INSERT(head->left,k);
	}
	else head->right = INSERT(head->right,k);
	
	head->height = 1+ ((Height(head->left) > Height(head->right))?Height(head->left):Height(head->right));
	
	int bal = GETBALANCE(head);
	
	if(bal > 1 && k  < head->left->key)return RIGHTROTATE(head);
	if(bal < -1 && k > head->right->key)return LEFTROTATE(head);
	if(bal >1 && k > head->left->key){
		head->left = LEFTROTATE(head->left);
		return RIGHTROTATE(head);
	}
	
	if(bal < -1 && k < head->right->key){
		head->right = RIGHTROTATE(head->right);
		return LEFTROTATE(head); 
	}
	
	return head;
}

struct node* SEARCH(struct node* A,int k){
	if (A== NULL)return NULL;
	if(A->key == k)return A;
	if (A->key > k) return SEARCH(A->left,k);
	else return SEARCH(A->right,k);
}
void PRINT(struct node* head){
	if(head == NULL)return;
	PRINT(head->left);
	for(int i =0 ;i<head->count;i++){
	printf("%d ",head->key);}
	PRINT(head->right);
	return;
}

void main(){
	int n,i;
	struct node* head = NULL;
	scanf("%d",&n);
	int* A = (int*)malloc(n*sizeof(int));
	for(i=0;i<n;i++){
		scanf("%d",&A[i]);
		struct node* search = SEARCH(head,A[i]);
		if(search == NULL)head = INSERT(head,A[i]);
		else search->count++;
	}
	PRINT(head);
	printf("\n");
}
