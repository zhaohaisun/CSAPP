/*
 * CS:APP Binary Bomb (Autolab version)
 *
 * Copyright (c) 2004, R. Bryant and D. O'Hallaron, All rights reserved.
 * May not be used, modified, or copied without permission.
 */ 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "phases.h"
#include "support.h"

/* Global bomb ID */
int bomb_id = 241;

/* 
 * phase1a.c - The user's input must match the specified string 
 */
void phase_1(char *input)
{
#if defined(PROBLEM)
    if (strings_not_equal(input, "And they have no disregard for human life.") != 0)
	explode_bomb();
#elif defined(SOLUTION)
    printf("And they have no disregard for human life.\n"); 
#else
    invalid_phase("1a");
#endif    
}

/* 
 * phase2b.c - To defeat this stage the user must enter the geometric
 * sequence starting at 1, with a factor of 2 between each number
 */
void phase_2(char *input)
{
#if defined(PROBLEM)
    int i;
    int numbers[6];
    
    read_six_numbers(input, numbers);
    
    if (numbers[0] != 1)
	explode_bomb();

    for(i = 1; i < 6; i++) {
	if (numbers[i] != numbers[i-1] * 2)
	    explode_bomb();
    }
#elif defined(SOLUTION)
    printf("1 2 4 8 16 32\n");
#else
    invalid_phase("2b");
#endif
}
/* 
 * phase3a.c - A long switch statement that the compiler should implement
 * with a jump table. The user has to enter both an index into the table 
 * and a value stored there.
 */
void phase_3(char *input)
{
#if defined(PROBLEM)
    int index, val, x = 0;
    int numScanned = 0;

    numScanned = sscanf(input, "%d %d", &index, &val);

    if (numScanned < 2)
	explode_bomb();

    switch(index) {
    case 0:
	x = 922;
	break;
    case 1:
	x = 813;
	break;
    case 2:
	x = 523;
	break;
    case 3:
	x = 771;
	break;
    case 4:
	x = 341;
	break;
    case 5:
	x = 415;
	break;
    case 6:
	x = 208;
	break;
    case 7:
	x = 489;
	break;
    default:
	explode_bomb();
    }

    if (x != val)
	explode_bomb();
#elif defined(SOLUTION)
    printf("4 341\n");
#else
    invalid_phase("3a");
#endif
}
/* 
 * phase4c.c - A recursive function to sort out.  
 *
 *          0, if n=0
 * F(n,b) = b, if n=1, 
 *          b + F(n-1, b) + F(n-2, b), if n>1
 * 
 * For a randomly chosen n, student must enter matching F(n, b) and b.
 */

int func4(int n, int base) {
    if (n <= 0) {
	return 0;
    }
    if (n == 1) {
	return base;
    }
    return base + func4(n-1, base) + func4(n-2, base);
}

void phase_4(char *input) {
#if defined(PROBLEM)
    int n, base, val, result, numScanned;

    numScanned = sscanf(input, "%d %d", &val, &base);
    if ((numScanned != 2) || (base < 2) || (base > 4)) {
	explode_bomb();
    }

    n = 8;
    result = func4(n, base);

    if (result != val) {
	explode_bomb();
    }
#elif defined(SOLUTION)
    printf("%d %d %s\n", func4(8, 3), 3, SECRET_PHRASE);
#else
    invalid_phase("4c");
#endif
}

/* 
 * phase5c.c - This stage requires the user to enter 6 unique numbers that 
 * are used as offsets into the integer array.  The sum of the six numbers
 * indexed by the offsets must equal a particular sum.             
 */
void phase_5(char *input)
{
#if defined(PROBLEM)
    static int array[] = {
	2,
	10,
	6,
	1,
	12,
	16,
	9,
	3,
	4,
	7,
	14,
	5,
	11,
	8,
	15,
	13,
    };
    int i, sum;
    int length;

    length = string_length(input);
    if (length != 6)
      explode_bomb();

    sum = 0;
    for (i = 0; i < 6; i++)
      sum += array[ (input[i] & 0x0f) ];

    if (sum != 48)
      explode_bomb();
#elif defined(SOLUTION)
    printf(";:37>1\n");
#else
    invalid_phase("5c");
#endif
}

/* 
 * phase6b.c - The user has to enter the permutation vector that
 * sorts a list in ascending order. The catch here is that the 
 * code inverts the permutation and checks for descending order.
 */
listNode node6 = {308, 6, NULL};
listNode node5 = {763, 5, &node6};
listNode node4 = {536, 4, &node5};
listNode node3 = {612, 3, &node4};
listNode node2 = {678, 2, &node3};
listNode node1 = {900, 1, &node2};

#if defined(SOLUTION)
/* Sort list in ascending order */
listNode *fun6(listNode *start)
{
    listNode *head = start;
    listNode *p, *q, *r;

    head = start;
    p = start->next;
    head->next = NULL;

    while (p != NULL) {
	r = head;
	q = head;

	while ((r != NULL) && (r->value > p->value)) {
	    q = r;
	    r = r->next;
	}

	if (q != r)
	    q->next = p;
	else
	    head = p;

	q = p->next;
	p->next = r;

	p = q;
    }

    return head;
}
#endif

void phase_6(char *input)
{
#if defined(PROBLEM)
    listNode *start = &node1;
    listNode *p;
    int indices[6];
    listNode *pointers[6];
    int i, j;

    read_six_numbers(input, indices);

    /* Check the range of the indices and whether or not any repeat */
    for (i = 0; i < 6; i++) {
	if ((indices[i] < 1) || (indices[i] > 6))
	    explode_bomb();
	
	for (j = i + 1; j < 6; j++) {
	    if (indices[i] == indices[j])
		explode_bomb();
	}
    }

    /* Reverse the permutation */
    for (i = 0; i < 6; i++) {
	indices[i] = 7 - indices[i];
    }

    /* Rearrange the list according to the user input */
    for (i = 0; i < 6; i++) {
	p = start;
	for (j = 1; j < indices[i]; j++)
	    p = p -> next;
	pointers[i] = p;
    }

    start = pointers[0];
    p = start;

    for (i = 1; i < 6; i++) {
	p->next = pointers[i];
	p = p->next;
    }
    p->next = NULL;

    /* Now see if the list is sorted in descending order*/
    p = start;
    for (i = 0; i < 5; i++) {
	if (p->value < p->next->value)
	    explode_bomb();
	
	p = p->next;
    }
#elif defined(SOLUTION)
    listNode *start = &node1;
    listNode *p;

    /* sort */
    start = fun6(start);

    /* emit the (inverted) node indices of the sorted list */
    p = start;
    while (p) {
	printf("%d ", 7 - p->index);
	p = p->next;
    }
    printf("\n");
#else
    invalid_phase("6b");
#endif
}



/* 
 * phase7.c - The infamous secret stage! 
 * The user has to find leaf value given path in a binary tree.
 */

typedef struct treeNodeStruct
{
    int value;
    struct treeNodeStruct *left, *right;
} treeNode;

/* balanced binary tree containing randomly chosen values */
treeNode n48 = {1001, NULL, NULL};
treeNode n46 = {47, NULL, NULL};
treeNode n43 = {20, NULL, NULL};
treeNode n42 = {7, NULL, NULL};
treeNode n44 = {35, NULL, NULL};
treeNode n47 = {99, NULL, NULL};
treeNode n41 = {1, NULL, NULL};
treeNode n45 = {40, NULL, NULL};
treeNode n34 = {107, &n47, &n48};
treeNode n31 = {6, &n41, &n42};
treeNode n33 = {45, &n45, &n46};
treeNode n32 = {22, &n43, &n44};
treeNode n22 = {50, &n33, &n34};
treeNode n21 = {8, &n31, &n32};
treeNode n1 = {36, &n21, &n22};

/* 
 * Searches for a node in a binary tree and returns path value.
 * 0 bit denotes left branch, 1 bit denotes right branch
 * Example: the path to leaf value "35" is left, then right,
 * then right, and thus the path value is 110(base 2) = 6.
 */

int fun7(treeNode* node, int val)
{
    if (node == NULL) 
	return -1;
  
    if (val < node->value) 
	return fun7(node->left, val) << 1;
    else if (val == node->value) 
	return 0;
    else 
	return (fun7(node->right, val) << 1) + 1;
}
     
void secret_phase()
{

#if defined(PROBLEM)
    char *input = read_line();
    int target = atoi(input);
    int path;

    /* Make sure target is in the right range */
    if ((target < 1) || (target > 1001))
	explode_bomb();

    /* Determine the path to the given target */
    path = fun7(&n1, target);

    /* Compare the retrieved path to a random path */
    if (path != 3)
	explode_bomb();
  
    printf("Wow! You've defused the secret stage!\n");

    phase_defused();
#elif defined(SOLUTION)
    int path = 3;
    treeNode *node = &n1;
    
    node = (path    & 0x1) ? node->right : node->left;
    node = (path>>1 & 0x1) ? node->right : node->left;
    node = (path>>2 & 0x1) ? node->right : node->left;
    printf("%d\n", node->value);
#else
    invalid_phase("7");
#endif
}


