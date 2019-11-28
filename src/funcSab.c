#include "funcSab.h"

void print_list(struct list ths)
{
	printf("\n");
	struct element_city *pointer;
	pointer=ths.head;
	// for -> while/dowhile & remove if
	/*
	for(;;)
	{
	if(pointer->next==NULL)
	{
		printf("%d\n",pointer->name);
		return;
	}
	else
	{
		printf("%d >>> ",pointer->name);
		pointer=pointer->next;
	}
	}
	*/
	while(pointer->next!=nullptr)
	{
		printf("%d >>> ",pointer->name);
	    pointer=pointer->next;
	}
	printf("%d\n",pointer->name);
}

void work()
{


	int cities_am;
	printf("cities amount:\n");
	scanf("%d",&cities_am);

	int ways_am;
	printf("ways amount:\n");
	scanf("%d",&ways_am);
	int lengths[ways_am];
	struct list ways[ways_am];
	for(int i=0;i<ways_am;i++)
	{
		printf("way %d length:\n",i+1);
		scanf("%d",&lengths[i]);
	}
	FILE *myfile;
	myfile = fopen ("/home/dmitrii/eclipse-workspace/sabotage/src/country.txt", "r");
	struct list *cities=get_cities_list(cities_am,myfile);

	for(int i=0;i<ways_am;i++)
		{
		      get_cities_list_ar(lengths[i],myfile,&ways[i]);

		}
	fclose(myfile);


	print_list(*cities);
	for(int i=0;i<ways_am;i++)
			{
		         print_list(ways[i]);


			}


	calculating_occurrences(ways,ways_am,cities);
	struct element_city *pr=cities->head;
	for(int i=0;i<cities_am;i++)
	{
		//print_ar(pr->ways);
		printf("city %d occur:%d\n",pr->name,pr->amount_ways);

		pr=pr->next;
	}


	int ways_it[ways_am];
	int taken[cities_am];
	for(int i=0;i<ways_am;i++)
	{
		ways_it[i]=-1;
	}
	for(int i=0;i<cities_am;i++)
		{
			taken[i]=0;
		}
	print_list(*cities);


	int ans[MAX];
	for(int ii=0;ii<MAX;ii++)
	{
		ans[ii]=-1;
	}

	int answer=core(ways_it,*cities,cities_am,ways_am,taken,ans);
	printf("\nanswer:%d\n",answer);

	int w=0;
	while((ans[w]!=-1)&&(w<MAX))
	{
		printf("%d  ",in_list(ans[w],cities));
		w++;
	}

	del(cities);
	free(cities);
	for(int o=0;o<ways_am;o++)
	{
		del(&ways[o]);
	}

}
void add_to_list(int knew,struct list *ext)
{
	struct element_city *new_el=(struct element_city *)malloc(sizeof(struct element_city));
	new_el->amount_ways=0;
	memset(new_el->ways,-1,MAX);
	/*for(int i=0;i<MAX;i++)
	{
		new_el->ways[i]=-1;
	}*/
	// can use memset
	new_el->name=knew;
	new_el->next=ext->head;
	ext->head=new_el;
}

struct list *get_cities_list(int ammount,FILE *myfile)
{

	struct list *cities=(struct list *)malloc(sizeof(struct list));
	cities->head=nullptr;
	cities->max_size=MAX;
	int name;
	for(int i=0;i<ammount;i++)
	{
		fscanf(myfile,"%d",&name);
		add_to_list(name,cities);
	}

	return cities;
}

void get_cities_list_ar(int ammount,FILE *myfile,struct list *cities)
{


	cities->head=nullptr;
	cities->max_size=MAX;
	int name;
	for(int i=0;i<ammount;i++)
	{
		fscanf(myfile,"%d",&name);
		add_to_list(name,cities);
	}


}
void print_ar(int ar[])
{
	int i=0;
	while(ar[i]!=-1)
	{
		printf("%d",ar[i]);
		i++;
	}
}
void calculating_occurrences(struct list ways[],int ammount, struct list *cities)
{
	if (cities->head==nullptr)
	{
		return;
	}

	struct element_city *pr=cities->head;
	while(pr!=nullptr)
	{
		int rec_value=pr->name;
		int occurents=0;
		for(int i=0;i<ammount;i++)
		{
			if(search(rec_value,ways[i],i)!=-1)
			{
				occurents++;
				write_in_arr(pr->ways,i);
			}
		}

		pr->amount_ways+=occurents;
		pr=pr->next;
	}

}

int search(int value,struct list ths,int amm)
{

	if(ths.head==nullptr)
	{
		return -1;
	}
	struct element_city *pr=ths.head;
	if (pr->name==value)
	{
		return 1;
	}
	while(pr->next!=nullptr)
	{
		pr=pr->next;
		if (pr->name==value)
			{
				return 1;
			}
	}
	return -1;
}
void write_in_arr(int ar[],int value)
{
	for(int i=0;i<MAX;i++)
	{
		if(ar[i]==-1)
		{
			ar[i]=value;
			return;
		}
	}
	printf("memory overload");
	return;
}
void del_from_list(struct element_city *previous,struct list *act)
{
	struct element_city *for_del=previous->next;

         previous->next=for_del->next;


	for_del->next=nullptr;
	free(for_del);
}

struct list del_fr(struct list act,int number)
{
	struct element_city *pr=act.head;
	for(int i=0;i<number;i++)
		pr=pr->next;
	del_from_list(pr,&act);
	return act;

}
void clean(struct list *act)
{
	struct element_city *pr=act->head;
	while(pr->next!=nullptr)
	{
		if(pr->next->amount_ways==0)
		{
			del_from_list(pr,act);
		}
		else
		{
			pr=pr->next;
		}
	}
}

int core(int ways_orig[],struct list cities,int city_number,int ways_number,int taken_cities_orig[], int ans_orig[])
{
	int min=MAX;

	int ways[ways_number+1];

	int ans[MAX];
	for(int y=0;y<MAX;y++)
	{
		ans[y]=ans_orig[y];
	}
	for(int e=0;e<ways_number;e++)
		ways[e]=ways_orig[e];


	ways[ways_number]=0;
	int taken_cities[city_number];
	for(int e=0;e<city_number;e++)
		taken_cities[e]=taken_cities_orig[e];

		for(int e=0;e<ways_number;e++)
			ways[e]=ways_orig[e];
	for(int i=0;i<city_number;i++)
	{
		if (taken_cities[i])
		{
			//printf("\n  tt %d  ",i);
			continue;
		}

		del_from_ar(ways,cities,i);

		int k=0;
		int p=0;
		int c=MAX;

		while(ways[k]!=0)
		{

			if(ways[k]==-1)
			{
				p=1;
				break;
			}
			k++;
		}
		if(p)
		{
			//printf("\n%d  cccc %d  ",i,min);
			//for(int e=0;e<ways_number;e++)
			//		printf("%d",ways[e]);
			taken_cities[i]=1;
			c=core(ways,cities,city_number,ways_number,taken_cities,ans);
			for(int e=0;e<city_number;e++)
					taken_cities[e]=taken_cities_orig[e];

			if (c+1<min)
			{
				min=c+1;

				for(int ii=0;ii<MAX;ii++)
				{
					ans_orig[ii]=ans[ii];
				}
				for(int tt=0;tt<MAX;tt++)
				{
					if(ans_orig[tt]==-1)
					{
						ans_orig[tt]=i;
						break;
					}
				}
			}
			for(int e=0;e<ways_number;e++)
					ways[e]=ways_orig[e];

		}
		else
		{
			//printf("\n%d  aaaa %d  ",i,min);
			ans_orig[0]=i;
			for(int ii=1;ii<MAX;ii++)
			{
				ans_orig[ii]=-1;
			}
			int w=0;
			while((ans_orig[w]!=-1)&&(w<MAX))
				{
					//printf("%d lol  ",ans_orig[w]);
					w++;
				}
			return 1;
		}

	}
	//printf("\n  bbbb %d",min);
	return min;
}


/*
int fact(int m)
{

	int s=1;
	for(int n=m;n>0;n--)
		s*=n;
	return s;

}
int c(int ft,int sn)
{
	return fact(ft)/(fact(sn)*fact(ft-sn));

}

*/

void del_from_ar(int ar[],struct list act,int number)
{
	struct element_city *pr=act.head;
	for(int i=0;i<number;i++)
		pr=pr->next;

	int ammount=pr->amount_ways;


	for(int j=0;j<ammount;j++)
		ar[pr->ways[j]]=1;
}


int are_eq(struct list list1, struct list list2)
{

	struct element_city *pr1=list1.head;
	struct element_city *pr2=list2.head;
	if (((pr1==nullptr)&&(pr2==nullptr))||((pr1!=nullptr)&&(pr2!=nullptr)))
	{

		if ((pr1==nullptr)&&(pr2==nullptr))
		{
			return 0;
		}
	}
	else
	{
		return 1;
	}
	int res=0;
	while ((pr1->next!=nullptr)&&(pr1->next!=nullptr))
	{
		if (pr1->next->name!=pr2->next->name)
		{
			++res;
		}
	pr1=pr1->next;
	pr2=pr2->next;

	}
if (res>0)
	res=1;
return res;


}

int in_list(int num, struct list *ths)
{


 	struct element_city *pt=ths->head;
 	for(int i=0;i<num;i++)
 		pt=pt->next;
 	return pt->name;

}

void del(struct list* ext)
{

	struct element_city* pt=ext->head;
	while (pt!=nullptr)
	{
		struct element_city* temp_pt=ext->head;
	    temp_pt=pt->next;
	    free(pt);
	    pt=temp_pt;
	}
    ext->head=nullptr;

}


int work_testing(int cities_am,int ways_am,int lengths[],char*adress)
{




	struct list ways[ways_am];

	FILE *myfile;
	myfile = fopen (adress, "r");
	struct list *cities=get_cities_list(cities_am,myfile);

	for(int i=0;i<ways_am;i++)
		{
		      get_cities_list_ar(lengths[i],myfile,&ways[i]);

		}
	fclose(myfile);


	/*
	print_list(*cities);
	for(int i=0;i<ways_am;i++)
			{
		         print_list(ways[i]);


			}

	*/

	calculating_occurrences(ways,ways_am,cities);
	/*
	struct element_city *pr=cities->head;
	for(int i=0;i<cities_am;i++)
	{
		//print_ar(pr->ways);
		printf("city %d occur:%d\n",pr->name,pr->ammount_ways);

		pr=pr->next;
	}

    */

	int ways_it[ways_am];
	int taken[cities_am];
	for(int i=0;i<ways_am;i++)
	{
		ways_it[i]=-1;
	}
	for(int i=0;i<cities_am;i++)
		{
			taken[i]=0;
		}
	//print_list(*cities);


	int ans[MAX];
	for(int ii=0;ii<MAX;ii++)
	{
		ans[ii]=-1;
	}

	int answer=core(ways_it,*cities,cities_am,ways_am,taken,ans);
	/*
	printf("\nanswer:%d\n",answer);

	int w=0;
	while((ans[w]!=-1)&&(w<MAX))
	{
		printf("%d  ",in_list(ans[w],cities));
		w++;
	}

    */
	for(int o=0;o<answer;o++)
	{
		printf("%d ",ans[o]);
		printf("\n");
	}
	del(cities);
	free(cities);
	for(int o=0;o<ways_am;o++)
	{
		del(&ways[o]);
	}
	return answer;

}
