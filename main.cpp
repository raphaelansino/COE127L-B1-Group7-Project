#include <iostream>
#include <omp.h>
#include <stdlib.h>
#include "HashTable.h"

using namespace std;

#define FILENAME_LEN 50
#define FILENAME_NUM 100
#define HASH_TABLE_MAX_SIZE 100000
#define MAX_LINE_SIZE 100000

char text[FILENAME_NUM][MAX_LINE_SIZE * 50];
int hash_size[FILENAME_NUM];
typedef struct HashTable Node;

int main()
{
	int file_num = 0;
	FILE *read_filename = fopen("filename_list.txt", "r");
	char **filename_list_array = (char **)malloc(sizeof(char*)* FILENAME_NUM);
	int i,j;
	Node* pHead;

#pragma omp parallel for
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
		cout << "The result can be found in output.txt .";

	omp_set_num_threads(8);
double time = -omp_get_wtime();
}