#include <iostream>
#include "Hashing.h"
#include <chrono>

using namespace std;
using ns=chrono::milliseconds;
using get_time=chrono::steady_clock;

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

	auto start=get_time::now();
	Hashing DOE;
	int file_num = 0;
	FILE *read_filename = fopen("filename_list.txt", "r");
	char **filename_list_array = (char **)malloc(sizeof(char*)* FILENAME_NUM);
	int i,j;
	Node* pHead;

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

	cout <<" Opened the File Correctly."<<endl;




    {
        {
            for (i = 0; i < file_num; i++)
            {
                {
                    DOE.readFunc(filename_list_array[i], i);
                }
            }
        }
    }

    {

        {
            for (i = 0; i < file_num; i++)
            {

                {
                    DOE.mapperFunc(i);
                }
            }
        }
    }

    DOE.reducerFunc(file_num);

    FILE *fp = fopen("output.txt", "w");

    DOE.writerFunc(fp);



    DOE.hashTablePrintFunc(FILENAME_NUM);

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

    for (i = 0; i < FILENAME_NUM; i++)
    {
        free(filename_list_array[i]);
    }
    free(filename_list_array);

    auto end=get_time::now();
    auto diff=end-start;
    cout<<"Elapsed Time is : "<<chrono::duration_cast<ns>(diff).count()<<" ms"<<endl;
    cout << "\nThe result can be found in output.txt ." << endl;









	return 0;
}
