#include "/home/dmitrii/eclipse-workspace/sabotage/src/funcSab.c"
#include <gtest/gtest.h>





TEST(are__equal,empty)
{
	struct list list1={NULL,MAX};
	struct list list2={NULL,MAX};
	ASSERT_EQ(0,are_eq(list1,list2));
	del(&list1);
	del(&list2);

}
TEST(are__equal2,empty_and_nott)
{
	struct list list1={NULL,MAX};
	struct list list2={NULL,MAX};
	add_to_list(5,&list1);
	ASSERT_EQ(1,are_eq(list1,list2));

	del(&list1);
	del(&list2);
}


TEST(adding1,pos)
{
	struct list list1={NULL,MAX};
	struct list list2={NULL,MAX};
	add_to_list(5,&list1);
	add_to_list(6,&list1);
	add_to_list(7,&list1);
	add_to_list(8,&list1);

	add_to_list(5,&list2);
	add_to_list(6,&list2);
	add_to_list(7,&list2);
	add_to_list(8,&list2);

	ASSERT_EQ(0,are_eq(list1,list2));

	del(&list1);
	del(&list2);
}


TEST(creat,pos)
{
	        struct list list1={NULL,MAX};




			add_to_list(5,&list1);
			add_to_list(6,&list1);
			add_to_list(7,&list1);
			add_to_list(8,&list1);


			FILE *myfile;
			myfile = fopen ("/home/dmitrii/eclipse-workspace/sabotage/tests_num.txt", "r");
			struct list *list2=get_cities_list(4,myfile);
			fclose(myfile);
			ASSERT_EQ(0,are_eq(list1,*list2));
			del(&list1);
			del(list2);
			free(list2);
}



TEST(delling,pos)
{
	struct list list1={NULL,MAX};
	struct list list2={NULL,MAX};
	add_to_list(5,&list1);
	add_to_list(6,&list1);
	add_to_list(7,&list1);
	add_to_list(8,&list1);

	add_to_list(5,&list2);
	add_to_list(7,&list2);

	add_to_list(8,&list2);

	del_from_list((&list1)->head->next,&list1);


	ASSERT_EQ(0,are_eq(list1,list2));


	del(&list1);
	del(&list2);
}





TEST(cleeean,pos)
{

	struct list list1={NULL,MAX};
		struct list list2={NULL,MAX};
		add_to_list(5,&list1);
		add_to_list(6,&list1);
		add_to_list(7,&list1);
		add_to_list(8,&list1);

		list1.head->amount_ways=2;
		list1.head->next->next->next->amount_ways=2;
		clean(&list1);
		add_to_list(5,&list2);

		add_to_list(8,&list2);

		ASSERT_EQ(0,are_eq(list1,list2));

		del(&list1);
		del(&list2);



}


TEST(seaaarching,pos)
{

	struct list list1={NULL,MAX};

		add_to_list(5,&list1);
		add_to_list(6,&list1);
		add_to_list(7,&list1);
		add_to_list(8,&list1);
		add_to_list(9,&list1);
			add_to_list(10,&list1);
		int i=search(7,list1,5);


		ASSERT_EQ(1,i);

		del(&list1);




}

TEST(seaaarching2,pos)
{

	struct list list1={NULL,MAX};

		add_to_list(5,&list1);
		add_to_list(6,&list1);
		add_to_list(7,&list1);
		add_to_list(8,&list1);
		add_to_list(9,&list1);
			add_to_list(10,&list1);
		int i=search(4,list1,2);


		ASSERT_EQ(-1,i);

		del(&list1);




}

TEST(in_listt,pos)
{

	struct list list1={NULL,MAX};

		add_to_list(5,&list1);
		add_to_list(6,&list1);
		add_to_list(7,&list1);
		add_to_list(8,&list1);
		add_to_list(9,&list1);
			add_to_list(10,&list1);
		int i=in_list(4,&list1);


		ASSERT_EQ(6,i);

		del(&list1);



}

TEST(writtinginarr,pos)
{
	int exp[4]={2,0,3,-1};
	int act[4]={2,0,-1,-1};

	write_in_arr(act,3);
	for(int i=0;i<4;i++)
	{
		ASSERT_EQ(act[i],exp[i]);
	}


}


TEST(deletingfromarr,pos)
{
	int act[6]={-1,-1,-1,-1,-1,-1};
	int exp[6]={-1,1,-1,-1,-1,1};

	struct list list1={NULL,MAX};
	add_to_list(5,&list1);
			add_to_list(6,&list1);
			add_to_list(7,&list1);
			add_to_list(8,&list1);
	struct element_city *pt=(list1.head->next->next);
	pt->amount_ways=2;


	pt->ways[0]=1;
	pt->ways[1]=5;

	del_from_ar(act,list1,2);
	for(int i=0;i<6;i++)
	{
		ASSERT_EQ(exp[i],act[i]);
	}


	del(&list1);
}


TEST(occure,pos)
{


	int cities_am=8;


	int ways_am=3;

	int lengths[ways_am]={1,5,3};
	struct list ways[ways_am];

	FILE *myfile;
	myfile = fopen ("/home/dmitrii/eclipse-workspace/sabotage/src/country2.txt", "r");
	struct list *cities=get_cities_list(cities_am,myfile);

	for(int i=0;i<ways_am;i++)
		{
		      get_cities_list_ar(lengths[i],myfile,&ways[i]);

		}
	fclose(myfile);


	int ans[8]={1,0,0,2,1,1,1,3};
	calculating_occurrences(ways,ways_am,cities);

	struct element_city *pr=cities->head;
		for(int i=0;i<cities_am;i++)
		{
			//print_ar(pr->ways);
			ASSERT_EQ(ans[i],pr->amount_ways);

			pr=pr->next;
		}
		del(cities);

		del(&ways[2]);

		del(&ways[0]);
		del(&ways[1]);



		free(cities);
}


TEST(workteesting,pos)
{

	int lengths[4]={2,2,2,2};
	int act=work_testing(8,4,lengths,"/home/dmitrii/eclipse-workspace/sabotage/src/for_test1.txt");
	ASSERT_EQ(3,act);
}

TEST(workteesting2,pos)
{

	int lengths[7]={4,1,2,4,5,6,6};
	int act=work_testing(9,7,lengths,"/home/dmitrii/eclipse-workspace/sabotage/src/for_test2.txt");
	ASSERT_EQ(2,act);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
