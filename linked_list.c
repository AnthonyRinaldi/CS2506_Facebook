#include <stdio.h>
#include <stdlib.h>

struct node
{
	int data;
	struct node *next;
};

void append(struct node **, int);
void addatbeg(struct node **, int);
void addafter(struct node *, int, int);
void display(struct node *);
int count(struct node *);
void delete(struct node **, int);
struct node * find(struct node *, int);


int main()
{
	struct node *p;
	p = NULL;  //Empty linked list

	printf("\n Number of elements in the linked list = %d\n", count(p));
	append(&p, 1);
	append(&p, 2);
	append(&p, 3);
	display(p);

/*
	addatbeg(&p, 999);
	addatbeg(&p, 888);
	addatbeg(&p, 777);
	display(p);
	printf("\n The new count is %d\n", count(p));
*/

/*
	addafter(p, 1, 5);
	addafter(p, 1, 6);
	addafter(p, 6, 7);
	display(p);
*/

/*
	delete(&p, 888);
	delete(&p, 1);
	delete(&p, 6);
	display(p);
	printf("\n The final count is %d\n", count(p));
*/

	return 0;
}


//Adds a node at the end of the linked list
void append(struct node **q, int num)
{
	struct node *temp, *r;
	temp = *q;

	if(*q == NULL) //If the list is empty, creat first node
	{
		temp = (struct node *)malloc(sizeof(struct node));
		temp->data = num;
		temp->next = NULL;
		*q = temp;
	}
	else
	{
		//Go to the last node
		while(temp->next != NULL)
			temp = temp->next;

		//Add node at the end
		r = (struct node *)malloc(sizeof(struct node));
		r->data = num;
		r->next = NULL;
		temp->next = r;
	}
}


//Adds a node at the beginning of the linked list
void addatbeg(struct node **q, int num)
{
	struct node *temp;

	//add a new node
	temp = (struct node *)malloc(sizeof(struct node));
	temp->data = num;
	temp->next = *q;
	*q = temp;
}


//Adds a node after the specified node
void addafter(struct node *q, int num, int data)
{
	struct node *temp, *r;

	temp = find(q, num);
	if(temp != NULL)
	{
		r = (struct node *)malloc(sizeof(struct node));
		r->data = data;
		r->next = temp->next;
		temp->next = r;
	}
	else
	{
		printf("\n %d is not a part of the linked list\n", data);
	}
}

void display(struct node *q)
{
	struct node *d;
	d=q;
	printf("\n");
	while(q != NULL)
	{
		printf(" %d ->", q->data);
		q = q->next;
	}
	printf(" NULL\n");

        printf("\n");
        while(d != NULL)
        {
                printf("%p ->", d);
                d = d->next;
        }
        printf(" NULL\n");

}

int count(struct node *q)
{
	int c = 0;
	
	//traverse the entire linked list
	while(q != NULL)
	{
		q = q->next;
		c++;
	}
	return c;
}

struct node * find(struct node *q, int num)
{
	if(q == NULL)
	{
		printf("\n The list is empty\n");
		return q;
	}

	while(q->data != num)
	{
		q = q->next;
		if(q == NULL)
		{
			printf("\n The given number is not in the list\n");
			return q;
		}
	}
	return q;
}

void delete(struct node **q, int num)
{
	struct node *temp, *old;
	temp = *q;

	while(temp != NULL)
	{
		if(temp->data == num)
		{
			//if the node to delete is the first node
			if(temp == *q)
			{
				*q = temp->next;
				temp->next = NULL;
				free(temp);
				return;
			}
			else
			{
				old->next = temp->next;
				temp->next = NULL;
				free(temp);
				return;
			}		
		}
		else
		{
			old = temp;
			temp = temp->next;
		}
	}
	
	printf("\n %d is not a part of the linked list\n", num);
}
