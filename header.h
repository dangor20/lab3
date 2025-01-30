typedef struct elem{
    long long inf;
    struct elem * link;
}Elem;

void queue_create(long long num);

void queue_push(long long num);

void queue_pop();

void queue_clear();

void get_queue(char *);

void write_row(char *, int);

void selection_sort();