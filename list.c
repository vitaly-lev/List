/*

	<Lion>		15.05.2019
	

	Queue messages of a given length, in which messages are sorted by priority. 
	New messages must be added according to priority. 
	If the queue is complete, then to add a new high priority message, 
	the lowest priority message must be deleted. 
	Use the list to organize the queue.

	The lower the number, the higher the priority


*/
#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#include "limits.h"


#define MAX_LIST_NUMBER	20	//Max number of List

int num_list = 0; //number elements in list


typedef struct Unit {
	int value;
	struct Unit* next;
} Unit;



void push(Unit** head, int data) {
Unit* tmp;
	tmp =  (Unit*)malloc(sizeof(Unit));
	tmp->value = (int)data;
	tmp->next = (*head);
	(*head) = tmp;
}

int pop(Unit** head) {
	Unit* prev = NULL;
	int val;
	if (head == NULL) {
		exit(-1);
	}
	prev = (*head);
	val = prev->value;
	(*head) = (*head)->next;
	free(prev);
	return val;
}

Unit* getNth(Unit* head, int n) {
	int counter = 0;
	while (counter < n && head) {
		head = head->next;
		counter++;
	}
	return head;
}

Unit* getLast(Unit* head) {
	if (head == NULL) {
		return NULL;
	}
	while (head->next) {
		head = head->next;
	}
	return head;
}

void pushBack(Unit* head, int value) {
	Unit* last = getLast(head);
	Unit* tmp = (Unit*)malloc(sizeof(Unit));
	tmp->value = (int)value;
	tmp->next = NULL;
	last->next = tmp;
	num_list++;
}



/*
	Delete last element of List
*/

int popBack(Unit** head) {
	Unit* pFwd = NULL;  //current Unit
	Unit* pBwd = NULL;  //previous Unit
	
	//Get NULL
	if (!head) {
		exit(-1);
	}

	//empty List
	if (!(*head)) {
		exit(-1);
	}

	pFwd = *head;
	while (pFwd->next) {
		pBwd = pFwd;
		pFwd = pFwd->next;
	}

	if (pBwd == NULL) {
		free(*head);
		*head = NULL;
		num_list = 0;
	}
	else {
		free(pFwd->next);
		pBwd->next = NULL;
		num_list--;
	}
}


/*
	Insert to n place new value
*/
void insert(Unit* head, unsigned n, int val) {
	unsigned i = 0;
	Unit* tmp = NULL;
	
	// Find the desired item. If you are out of the list, then exit the loop,
	// the error will not be thrown away, it will be inserted at the end
	while (i < n-1 && head->next) {
		head = head->next;
		i++;
	}
	tmp = (Unit*)malloc(sizeof(Unit));
	tmp->value = (int)val;
	// If this is not the last element, then next we jump to the next Unit
	if (head->next) {
		tmp->next = head->next;
		//else to NULL
	}
	else {
		tmp->next = NULL;
	}
	head->next = tmp;
	num_list++;
}


/*
	Delete Unit from List
*/

int deleteNth(Unit** head, int n) {
	if (n == 0) {
		return pop(head);
	}
	else {
		Unit* prev = getNth(*head, n - 1);
		Unit * elm = prev->next;
		int val = elm->value;

		prev->next = elm->next;
		free(elm);
		num_list--;
		return val;
	}
}



/*
	Delete List
*/
void deleteList(Unit** head) {
	Unit* prev = NULL;
	while ((*head)->next) {
		prev = (*head);
		(*head) = (*head)->next;
		free(prev);
	}
	free(*head);
	num_list = 0;
}


/*
	Create List from Array
*/

void fromArray(Unit** head, int* arr, size_t size) {
	size_t i = size - 1;
	if (arr == NULL || size == 0) {
		return;
	}
	do {
		push(head, arr[i]);
	} while (i-- != 0);
	num_list = size;
}


/*
	Create Array from List
*/
int* toArray(const Unit* head) {
	int leng = sizeof(head);
	int* values = (int*)malloc(leng * sizeof(int));
	while (head) {
		values[--leng] = head->value;
		head = head->next;
	}
	return values;
}

/*
	Print List
*/

void printLinkedList(const Unit* head) {
	while (head) {
		printf("%d ", head->value);
		head = head->next;
	}
	printf("\n");
}



void merge(Unit* a, Unit* b, Unit** c) {
	Unit tmp;
	*c = NULL;
	if (a == NULL) {
		*c = b;
		return;
	}
	if (b == NULL) {
		*c = a;
		return;
	}
	if (a->value < b->value) {
		*c = a;
		a = a->next;
	}
	else {
		*c = b;
		b = b->next;
	}
	tmp.next = *c;
	while (a && b) {
		if (a->value < b->value) {
			(*c)->next = a;
			a = a->next;
		}
		else {
			(*c)->next = b;
			b = b->next;
		}
		(*c) = (*c)->next;
	}
	if (a) {
		while (a) {
			(*c)->next = a;
			(*c) = (*c)->next;
			a = a->next;
		}
	}
	if (b) {
		while (b) {
			(*c)->next = b;
			(*c) = (*c)->next;
			b = b->next;
		}
	}
	*c = tmp.next;
}


/*
	Find the middle ща List
*/

void split(Unit* src, Unit** low, Unit** high) {
	Unit* fast = NULL;
	Unit* slow = NULL;

	if (src == NULL || src->next == NULL) {
		(*low) = src;
		(*high) = NULL;
		return;
	}

	slow = src;
	fast = src->next;

	while (fast != NULL) {
		fast = fast->next;
		if (fast != NULL) {
			fast = fast->next;
			slow = slow->next;
		}
	}

	(*low) = src;
	(*high) = slow->next;
	slow->next = NULL;
}


/*
	Sort List
*/

void mergeSort(Unit** head) {
	Unit* low = NULL;
	Unit* high = NULL;
	if ((*head == NULL) || ((*head)->next == NULL)) {
		return;
	}
	split(*head, &low, &high);
	mergeSort(&low);
	mergeSort(&high);
	merge(low, high, head);
}

int main(void) {

int	number;
Unit* head = NULL;
int arr[] = { 3,7,34,2,11,8,5,4,2,1};
	
	fromArray(&head, arr, 10);
	
	printf("Non Sorted List:");
	printLinkedList(head);

	mergeSort(&head);
	printf("Sorted     List:");
	printLinkedList(head);

	printf("Number of elements in List = %i\n\n", num_list);

	number = 4;
	
	while (number != 0)
	{
		scanf_s("%i", &number);
		if (num_list < MAX_LIST_NUMBER) {
			pushBack(head, number);
		}
		else
		{
			popBack(&head);
			pushBack(head, number);
		}


		printf("Non Sorted List:");
		printLinkedList(head);
		mergeSort(&head);
		printf("Sorted     List:");
		printLinkedList(head);
		printf("Number of elements in List = %i\n\n", num_list);
	}

	deleteList(&head);

	return(0);
}
