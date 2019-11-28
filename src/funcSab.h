#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdarg.h>
#include <string.h>
#define MAX 1000

struct element_city
{
	int name;
	struct element_city *next;
	struct element_city *prev;
	int amount_ways;
	int ways[MAX];
};

struct list
{
struct element_city *head;
int max_size;
};


void print_list(struct list);

void del_from_list(struct element_city *,struct list *);
void add_to_list(int ,struct list *);

struct list *get_cities_list(int,FILE *);
void calculating_occurrences(struct list [],int , struct list *);
int search(int ,struct list ,int );
void write_in_arr(int [],int );
void clean(struct list *);
int fact(int );
int c(int ft,int sn);
int core(int [],struct list ,int ,int ,int [],int []);
void del_from_ar(int [],struct list ,int );

void work();
void print_ar();
int in_list(int , struct list *);
void del(struct list*);

void get_cities_list_ar(int ,FILE *,struct list *);
int work_testing(int ,int ,int[] ,char*);
int are_eq(struct list , struct list );
