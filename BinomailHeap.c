#include "stdio.h"
#include "stdlib.h"

struct BinomialNode{
	int key;
	char data;
	int degree;
	struct BinomialNode* p;
	struct BinomialNode* child;
	struct BinomialNode* sibling;
};

struct BinomialHeap{
	struct BinomialNode* head;
};

struct BinomialNode* Make_Binomial_Node(int k);
struct BinomialHeap* Make_Binomial_Heap();
struct BinomialNode* Binomial_Heap_Minimum(struct BinomialHeap* H);
void Binomial_Link (struct BinomialNode* y, struct BinomialNode* z);
struct BinomialNode* Binomial_Heap_Merge (struct BinomialHeap* H1, struct BinomialHeap* H2);
struct BinomialNode* Binomial_Heap_Union(struct BinomialHeap* H1, struct BinomialHeap* H2);
void Binomial_Heap_Insert(struct BinomialHeap* H, struct BinomialNode* x);
struct BinomialNode* Binomial_Heap_Extract_Min(struct BinomialHeap* H);
struct BinomialNode* Binomial_Heap_Reverse(struct BinomialNode* x);
void Binomial_Heap_Decrease_Key (struct BinomialHeap* H, struct BinomialNode* x, int k);
void Binomial_Heap_Delete (struct BinomialHeap* H, struct BinomialNode* x);

int main(){
	FILE* input;
	FILE* output;
	input = fopen("input.txt", "r");
	output = fopen("output.txt", "w");
	int k;
	char s[3];
	struct BinomialHeap* H = (struct BinomialHeap* )malloc(sizeof(struct BinomialHeap));
	H = Make_Binomial_Heap();
	struct BinomialNode* x = (struct BinomialNode* )malloc(sizeof(struct BinomialNode));
	while(1){
		if (feof(input)) break;
		fscanf(input, "%s", &s);
		switch (s[0]){
			case 'I':{
				fscanf(input, "%d", &k);
				x = Make_Binomial_Node(k);
				Binomial_Heap_Insert(H,x);
				fprintf(output, "%d is successfully inserted\nThe head is %d\n\n", x->key, H->head->key);
				break;
			}
			case'M':{
				if(H->head == NULL){
					fprintf(output, "\nError: Cannot show minimum\nThe Binomial heap is EMPTY\n");
					break;
				}
				x = Binomial_Heap_Minimum(H);
				fprintf(output, "Minimum is %d\n", x->key);
				break;
 				}
			case 'E':{
				if(H->head == NULL){
					fprintf(output, "\nError: Cannot extract anything\nThe Binomial heap is EMPTY\n");
					break;
				}
				x = Binomial_Heap_Extract_Min(H);
				fprintf(output, "%d is extracted\n", x->key);
				if (H->head) {
					fprintf(output, "The head is %d\n\n", H->head->key);
				}
				break;
			}
		}
	}
	fclose(input);
	fclose(output);
	printf("\nSuccess!\nResults are in the file output.txt\n");
	return 0;
}

struct BinomialNode* Make_Binomial_Node(int k){
	struct BinomialNode* x = (struct BinomialNode* )malloc(sizeof(struct BinomialNode));
	x->child = NULL;
	x->degree = 0;
	x->key = k;
	x->data = 0;
	x->p = NULL;
	x->sibling = NULL;
	return x;
}

struct BinomialHeap* Make_Binomial_Heap(){
	struct BinomialHeap* H = (struct BinomialHeap* )malloc(sizeof(struct BinomialHeap));
	H -> head = NULL;
	return H;
}

struct BinomialNode* Binomial_Heap_Minimum(struct BinomialHeap* H){
	struct BinomialNode* x = (struct BinomialNode* )malloc(sizeof(struct BinomialNode));
	struct BinomialNode* y = (struct BinomialNode* )malloc(sizeof(struct BinomialNode));
	struct BinomialNode* z = (struct BinomialNode* )malloc(sizeof(struct BinomialNode));
	x = H->head;
	y = NULL;
	z = NULL;
	int min = 2147483647;
	while (x){
		if (x->key < min){
			min = x->key;
			y = x;
		}
		z = x->sibling;
		x = z;
	}
	return y;
}

void Binomial_Link (struct BinomialNode* y, struct BinomialNode* z){
	y->p = z;
	y->sibling = z->child;
	z->child = y;
	z->degree++;
}

struct BinomialNode* Binomial_Heap_Merge (struct BinomialHeap* H1, struct BinomialHeap* H2){
	struct BinomialHeap* H = (struct BinomialHeap* )malloc(sizeof(struct BinomialHeap));
	struct BinomialNode* x = (struct BinomialNode* )malloc(sizeof(struct BinomialNode));
	struct BinomialNode* y = (struct BinomialNode* )malloc(sizeof(struct BinomialNode));
	struct BinomialNode* z = (struct BinomialNode* )malloc(sizeof(struct BinomialNode));
	struct BinomialNode* buf = (struct BinomialNode* )malloc(sizeof(struct BinomialNode));
	H = Make_Binomial_Heap();
	x = H1->head;
	y = H2->head;
	z = NULL;
	buf = NULL;
	if (x&&y){
	   if (x->degree <= y->degree){
		  z = x;
		  buf = x->sibling;
		  x = buf;
		  } else {
		  z = y;
		  buf = y->sibling;
		  y = buf;
		  }
	} else if (y) {
	  	   z = y;
	  	   buf = y->sibling;
		   y = buf;
	} else if (x){
	  	   z = x;
	  	   buf = x->sibling;
		   x = buf;
	}
	H->head=z;	//óñòàíàâëèâàåì ãîëîâó ñïèñêà
	while (x && y){
		if (x->degree <= y->degree){
			z->sibling = x; //z óêàçûâàåò íà x
			buf = x->sibling;
			x = buf; //äâèæåíèå ïî x
		} else {
			z->sibling = y; //z óêàçûâàåò íà y
			buf = y->sibling;
			y = buf; //äâèæåíèå ïî y
		}
		buf=z->sibling;
		z=buf; //äâèæåíèå ïî z
	}
	if (x){
		z->sibling = x;
	} else if (y){
		z->sibling = y;
	}
	return H->head;
}

struct BinomialNode* Binomial_Heap_Union(struct BinomialHeap* H1, struct BinomialHeap* H2){
	struct BinomialHeap* H = (struct BinomialHeap* )malloc(sizeof(struct BinomialHeap));
	H = Make_Binomial_Heap();
	H->head = Binomial_Heap_Merge(H1, H2);
	struct BinomialNode* prev_x = (struct BinomialNode* )malloc(sizeof(struct BinomialNode));
	struct BinomialNode* x = (struct BinomialNode* )malloc(sizeof(struct BinomialNode));
	struct BinomialNode* next_x = (struct BinomialNode* )malloc(sizeof(struct BinomialNode));
	if(H->head == NULL){
		return NULL;
	}
	prev_x = NULL;
	x = H->head;
	next_x = x->sibling;
	while (next_x){
		if ((x->degree != next_x->degree) || ((next_x->sibling != NULL) && next_x->sibling->degree == x->degree)){
			prev_x = x;	
			x = next_x;
		} else if (x->key <= next_x->key){ //äâà êîðíÿ ñ ðàâíûìè ñòåïåíÿìè, íî x.key<=next_x.key
		  	   x->sibling = next_x->sibling; //óäàëåíèå next_x èç ñïèñêà êîðíåé
			   Binomial_Link(next_x,x); //äåëàåì next_x ðåá¸íêîì x
		} else {
		  	if (prev_x == NULL){ //äâà êîðíÿ ñ ðàâíûìè ñòåïåíÿìè, íî x-êîðåíü
				H->head = next_x; ////óäàëåíèå x èç ñïèñêà êîðíåé ïóò¸ì óäàëåíèÿ åãî èç ãîëîâû ñïèñêà
		    }else{ //äâà êîðíÿ ñ ðàâíûìè ñòåïåíÿìè, íî next_x.key<x.key
		  		prev_x->sibling = next_x; //óäàëåíèå x èç ñïèñêà êîðíåé
		    }
			Binomial_Link(x,next_x); //äåëàåì x ðåá¸íêîì next_x
			x = next_x; //âîçðàùàåìñÿ ê ñïèñêó êîðíåé
		}
		next_x = x->sibling;
	}
	return H->head;
}

void Binomial_Heap_Insert(struct BinomialHeap* H, struct BinomialNode* x){
	struct BinomialHeap* H_ = (struct BinomialHeap* )malloc(sizeof(struct BinomialHeap));
	H_->head = x;
	H->head = Binomial_Heap_Union(H, H_);
}

struct BinomialNode* Binomial_Heap_Extract_Min(struct BinomialHeap* H){
	struct BinomialNode* x = (struct BinomialNode* )malloc(sizeof(struct BinomialNode));
	struct BinomialNode* y = (struct BinomialNode* )malloc(sizeof(struct BinomialNode));
	struct BinomialNode* z = (struct BinomialNode* )malloc(sizeof(struct BinomialNode));
	struct BinomialNode* prev_x = (struct BinomialNode* )malloc(sizeof(struct BinomialNode));
	struct BinomialNode* prev_y = (struct BinomialNode* )malloc(sizeof(struct BinomialNode));
	x = H->head;
	prev_x = NULL;
	y = NULL;
	prev_y = NULL;
	z = NULL;
	int min = 2147483647;
	while (x){
		if (x->key < min){
			prev_y = prev_x;
			min = x->key;
			y = x;
		}
		prev_x = x;
		z = x->sibling;
		x = z; //òåïåðü x óêàçûâàåò íà ñîñåäà ñïðàâà
	}
	if (prev_y){
		prev_y->sibling = y->sibling; //óäàëåíèå y èç ñïèñêà êîðíåé
	}else{
		H->head = y->sibling; //óäàëåíèå y èç ñïèñêà êîðíåé ïóò¸ì óäàëåíèÿ èç ãîëîâû ñïèñêà
	}
	struct BinomialHeap* H_ = (struct BinomialHeap* )malloc(sizeof(struct BinomialHeap));
	H_ = Make_Binomial_Heap();
	H_->head = Binomial_Heap_Reverse(y->child);
	H->head = Binomial_Heap_Union(H, H_);
	return y;
}

struct BinomialNode* Binomial_Heap_Reverse(struct BinomialNode* x){
	struct BinomialNode* prev_x = (struct BinomialNode* )malloc(sizeof(struct BinomialNode));
	struct BinomialNode* next_x = (struct BinomialNode* )malloc(sizeof(struct BinomialNode));
	prev_x = NULL;
	next_x = NULL;
	while(x){ //ïðîöåäóðà ïåðåâîðà÷èâàíèÿ ñïèñêà
		x->p = NULL; //î÷èùàåì ðîäèòåëüñêîå ïîëå
		next_x = x->sibling;
		x->sibling = prev_x;
		prev_x = x;
		x = next_x;
	}
	return prev_x;
}

void Binomial_Heap_Decrease_Key (struct BinomialHeap* H, struct BinomialNode* x, int k){
	if (k > x->key){
		printf("Error! New value is bigger than current");
	}else{
		  x->key = k;
		  struct BinomialNode* y = x;
		  struct BinomialNode* z = y->p;
		  while ((z != NULL) && (y->key < z->key)){
		  		int buf = y->key;
				y->key = z->key;
				z->key = buf;
				y = z;
				z = y->p;
		 }
	}
}

void Binomial_Heap_Delete (struct BinomialHeap* H, struct BinomialNode* x){
	Binomial_Heap_Decrease_Key (H, x, -2147483647);
	struct BinomialNode* y = Binomial_Heap_Extract_Min(H);
}
