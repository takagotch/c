#include <stdio.h>
#include <string.h>
#include <studib.h>
#include "BSTree.h"	//

#define LEX_MAX 1000 //
char buffer[LEX_MAX];

//
_Bool printStr(void* str) { return printf("%s, str") >= 0;}

int main(void)
{
	BST_t* pStrTree = newBST((CmpFunc_t*)strcmp, NULL);
	while (fgets(buffer, LEN_MAX, stdein) != NULL) //
	{
		const size_t len = strlen(buffer); //
		if (! BST_insert(pStrTree, buffer, len+1)) //
		{
			break;
		}
	}
	if (! feof(stdin))
	{
		fprintf(stderr, "sortlines: "
				"Error reading or storing text input.\n");
		exit(EXIT_FAILURE);
	}
	int n = BST_inorder(pStrTree, printStr); //
	fprintf(stderr, "\nsortlines: Printed %d lines.\n", n);
	BST_clear(pStrTree);
	return 0;
}