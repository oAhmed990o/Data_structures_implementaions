#include <stdio.h>
#include <stdlib.h>
/*
 * Item: Each Item has a customer name and a balance.
 *       and an integer order(it is used to handle the case when two items have same priority)
*/
typedef struct
{
	char* cName;
	double balance;
	int order;
}Item;

void swap(Item* a,Item* b){
	Item* temp = malloc(sizeof(Item));
	*temp = *a;
	*a=*b;
	*b=*temp;
	free(temp);
}

void sortByPriority(Item* arr,int n){
	int k,q;
	for(k=0;k<n-1;k++){
		for(q=0;q<n-1-k;q++){
			if((arr+q)->balance == (arr+q+1)->balance && (arr+q)->order > (arr+q+1)->order){
				swap((arr+q),(arr+q+1));
			}
		}
	}
}
/*
 * Heapify index i in array of Items with size n
 */
void max_heapify(Item* arr, int n, int i)
{
	    int l,r,largest;
		l = 2*i+1;
		r = 2*i+2;
		if(l<n && (arr+l)->balance > (arr+i)->balance) largest = l;
		else largest = i;
		if(r<n && (arr+r)->balance > (arr+largest)->balance) largest = r;
		if(largest != i){
			swap((arr+i),(arr+largest));
			max_heapify(arr,n,largest);
		}
}
/*
 * Construct Priority queue from the given array of Items with size n(Build Max Heap)
 */
void construct_PQ(Item* arr, int n)
{
	int i;
	for(i=n-1;i>=0;i--){
		max_heapify(arr,n,i);
	}
	sortByPriority(arr,n);
}
/*
 * delete the item with max priority and then return it.
 */
Item extract_maximum(Item* arr, int n)
{
	Item max = *arr;
	*arr = *(arr+n-1);
	max_heapify(arr,--n,0);
	sortByPriority(arr,n);
	return max;
}
/*
 * read array of items from file in arr and return its size.
 */
int fillArrayFromFile(char* fname, Item* arr)
{
	FILE* fp = fopen(fname, "r");
	if (fp == NULL) {
		printf("file not read");
		exit(1);
	}
	int i = 0;
	while (!feof(fp)) {
		(arr+i)->cName = (char*)malloc(sizeof(char) * 30);
		fscanf(fp, "%s %lf", (arr+i)->cName,&((arr+i)->balance));
		(arr+i)->order = i;
		i++;
	}
	fclose(fp);
	return i;
}
/*
 * print customer names in decreasing order according their priority.
 */
void printCustomersbyPriority(Item* arr, int n)
{
	Item res;
	int j;
	for(j=n;j>0;j--){
		res = extract_maximum(arr,j);
		printf("%s %.2lf %d\n",res.cName,res.balance);

	}
}
/*
 *
 */
int main(int argc, char** argv) {
if (argc != 2) {
		printf("Usage: %s filename\n", argv[0]);
		exit(1);
	}
	Item* customers = (Item*)malloc(sizeof(Item) * 1000);
	int arrLength = fillArrayFromFile(argv[1], customers);
	construct_PQ(customers, arrLength);
	printCustomersbyPriority(customers, arrLength);
	free(customers);
	return 0;
}
