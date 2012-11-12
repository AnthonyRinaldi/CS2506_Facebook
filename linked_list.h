#ifndef LLIST
#define LLIST

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

#endif
