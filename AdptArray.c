#include "AdptArray.h"
#include "AdptArray.h"
#include "book.h"
#include "Person.h"
#include <stdio.h>

typedef struct AdptArray_
{
	int ArrSize;
	PElement *pElemArr;
	DEL_FUNC delFunc;
	COPY_FUNC copyFunc;
	PRINT_FUNC printFunc;
} AdptArray;

PAdptArray CreateAdptArray(COPY_FUNC copyFunc_, DEL_FUNC delFunc_, PRINT_FUNC printFunc_)
{
	PAdptArray pArr = (PAdptArray)malloc(sizeof(struct AdptArray_));
	if (pArr == NULL)
		return NULL;
	pArr->ArrSize = 1;
	pArr->pElemArr = (PElement*)malloc(sizeof(PElement));
	if(pArr->pElemArr == NULL){
		free(pArr);
		return NULL;
	}
	pArr->delFunc = delFunc_;
	pArr->copyFunc = copyFunc_;
	pArr->printFunc = printFunc_;
	for(int i=0;i<pArr->ArrSize;i++){
		pArr->pElemArr[i] = NULL;
	}
	return pArr;
}

void DeleteAdptArray(PAdptArray pArr)
{
	int i;
	if (pArr == NULL)
		return;
	for (i = 0; i < pArr->ArrSize; i++)
	{
		if(pArr->pElemArr[i] != NULL){
			pArr->delFunc((pArr->pElemArr)[i]);
		}
	}
	free(pArr->pElemArr);
	free(pArr);
}

Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElem)
{
	PElement *newpElemArr;
	if (pArr == NULL)
		return FAIL;

	if (pNewElem == NULL)
	{
		return FAIL;
	}

	if (idx < 0)
	{
		return FAIL;
	}

	if (idx > pArr->ArrSize)
	{

		pArr->pElemArr = (PElement*)realloc(pArr->pElemArr,(idx+1)*sizeof(PElement));
		if (pArr->pElemArr == NULL){return FAIL;}

		for(int i = pArr->ArrSize;i <= idx;i++){
			pArr->pElemArr[i] = NULL;
		}

		pArr->ArrSize = idx + 1;

	}

	if(pArr->pElemArr[idx]!=NULL){
		pArr->delFunc(pArr->pElemArr[idx]);
	}

	pArr ->pElemArr[idx] = pArr->copyFunc(pNewElem);

	return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray pArr, int idx)
{
	if (pArr == NULL)
	{
		return NULL;
	}

	if (pArr->pElemArr[idx] == NULL)
	{
		return NULL;
	}

	if (idx >= pArr->ArrSize)
	{
		return NULL;
	}
	
	return pArr->copyFunc(pArr->pElemArr[idx]);
}

int GetAdptArraySize(PAdptArray pArr)
{
	if (pArr->ArrSize < 0)
	{
		return -1;
	}
	return pArr->ArrSize;
}

void PrintDB(PAdptArray pArr)
{
	if (pArr == NULL)
	{
		return;
	}

	for (int i = 0; i < pArr->ArrSize; ++i)
	{
		if (pArr->pElemArr[i] != NULL)
		{
			pArr->printFunc(pArr->pElemArr[i]);
		}
	}
}