#define HASHTABLE_SIZE 10

typedef struct lineNode
{
    char *line;
    struct lineNode *next;
}
lineNode;


typedef struct character
{
    char *name;
    int line_count;
    lineNode *lines;
    struct character *next;
}
character;
