#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order;
	struct RecordType* next; 
};

// Fill out this structure
struct HashType{
	struct RecordType* ptr;
};

// Compute the hash function
int hash(int x, int tableSize){
	return x % tableSize;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

void insertRecord(struct HashType hashTable[], struct RecordType record, int tableSize){
	int index = hash(record.id, tableSize);
	if (hashTable[index].ptr == NULL){
		hashTable[index].ptr = &record;
	}
	else {
		struct RecordType* curr = hashTable[index].ptr; 
		while (curr->next != NULL){
			curr = curr->next;
		}
		curr->next = &record;
	}
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;

	for (i=0;i<hashSz;++i){
		// if index is occupied with any records, print all
		if (pHashArray[i].ptr != NULL){
			printf("Index %d -> ", i);
			struct RecordType* curr = pHashArray[i].ptr;
			while (curr != NULL){
				printf("%d %c %d -> ", curr->id, curr->name, curr->order);
				curr = curr->next;
			}
			printf("NULL\n");
		}
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation
	int hashTableSize = 10; 
	struct HashType* hashTable = (struct HashType*)calloc(hashTableSize, sizeof(struct HashType));
	for (int i = 0; i < recordSz; ++i){
		insertRecord(hashTable, *(pRecords + i), hashTableSize);
	}

	displayRecordsInHash(hashTable, hashTableSize);

	free(pRecords);
	free(hashTable);

	return 0;
}