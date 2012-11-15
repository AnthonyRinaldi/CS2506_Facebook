#ifndef LLIST
#define LLIST

struct node
{
	
	char* name;
	char* location;
	int   gender;
	int   age;

	struct friendNode *friend;
	struct node *next;
};

struct friendNode
{
	struct friendNode *nextFriend;
	struct node *user;
};

void append(struct node **, char*, char*, int, int);
void addatbeg(struct node **, char*, char*, int, int);
void addafter(struct node *q, char* n, char* l, int g, int a);
void display(struct node *);
int count(struct node *);
void delete(struct node **, char*, char*, int, int);
struct node * find(struct node *q, char* n, char* l, int g, int a);
struct node * findName(struct node *q, char* n);

#endif
