#include <iostream>
#include "Hashing.h"
#include <omp.h>

using namespace std;

#define FILENAME_LEN 50
#define FILENAME_NUM 100
#define HASH_TABLE_MAX_SIZE 100000

typedef struct HashTable Node;
struct HashTable
{
	char* Key;
	int Value;
	Node* pNext;
};

Node * hashTableMAIN[FILENAME_NUM + 1][HASH_TABLE_MAX_SIZE];

int main()
{
	Hashing DOE;
	int file_num = 0;
	FILE *read_filename = fopen("filename_list.txt", "r");
	char **filename_list_array = (char **)malloc(sizeof(char*)* FILENAME_NUM);
	int i,j;
	Node* pHead;

#pragma omp parallel for // to fork additional threads to carry out the work enclosed in the construct in parallel
	for (i = 0; i < FILENAME_NUM; i++)
	{
		filename_list_array[i] = (char *)malloc(sizeof(char)* FILENAME_LEN);
	}

	if (read_filename == NULL)
	{
		cout << "open the file incorrectly !";
		return 0;
	}
	while (!feof(read_filename))
	{

		fscanf(read_filename, "%s\n", filename_list_array[file_num]);
		file_num++;
	}
	cout << "The result can be found in output.txt ." << endl;

	omp_set_num_threads(2); //cores
	double time = -omp_get_wtime();
	double time1 = -omp_get_wtime();

#pragma omp parallel private (i)
	{
#pragma omp single nowait //directive identifies a section of code that must be run by a single available thread.
		{
			for (i = 0; i < file_num; i++)
			{
#pragma omp task //when you want to identify a block of code to be executed in parallel with the code outside the task region
				{
					DOE.readFunc(filename_list_array[i], i);
				}
			}
		}
	}
#pragma omp parallel private (i)
	{
#pragma omp single nowait
		{
			for (i = 0; i < file_num; i++)
			{
#pragma omp task
				{
					DOE.mapperFunc(i);
				}
			}
		}
	}
#pragma omp barrier
	DOE.reducerFunc(file_num);
#pragma omp barrier
	FILE *fp = fopen("output.txt", "w");

	DOE.writerFunc(fp);

	DOE.hashTablePrintFunc(FILENAME_NUM);

#pragma omp parallel for
	for (i = 0; i < FILENAME_NUM; i++)
	{
		for (j = 0; j < HASH_TABLE_MAX_SIZE; j++)
		{
			if (hashTableMAIN[i][j])
			{
				pHead = hashTableMAIN[i][j];
				if (pHead)
				{
					free(pHead->Key);
					free(pHead);
				}
			}
		}
	}


	fclose(fp);
	time = time + omp_get_wtime();
	time1 = ((time1 + omp_get_wtime()) * 1000 );
	printf("Elapsed time is %lf in seconds. \n", time);
	printf("Elapsed time is %lf in milliseconds. \n", time1);

	for (i = 0; i < FILENAME_NUM; i++)
	{
		free(filename_list_array[i]);
	}
	free(filename_list_array);

	cout << "THREAD COUNT: (NO OF X's) " << endl;
	#pragma omp parallel
	{
	    cout << "X" << endl;
	}

	return 0;
}
