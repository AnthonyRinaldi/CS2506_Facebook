#ifndef LLIST
#define LLIST

struct node
{
	
	char* name;
	char* location;
	int   gender;
	int   age;

	struct friendNode *fr;
	struct node *next;
};

struct friendNode
{
	struct friendNode *nextFriend;
	struct node *user;
};

void addFriend(struct node **q, struct friendNode **f);
void delFriend(struct node **q, struct node **r);
void appendF(struct node **q, struct node **r);
int isFriends(struct node **q, struct node **r);

void append(struct node **, char*, char*, int, int);
void addatbeg(struct node **, char*, char*, int, int);
void addafter(struct node *q, char* n, char* l, int g, int a);
void display(struct node *);
int count(struct node *);
void delete(struct node **, char*);
struct node * find(struct node *q, char* n, char* l, int g, int a);
struct node * findName(struct node *q, char* n);

#endif
