#include <stdlib.h>
#include <stdio.h>

/* List data structure, and functions to be implemented.
 * These dummy versions make all tests fail -- your job
 * is to fix them.
 */
struct node {
    int data;
    struct node * next;
};

int checkOrder(struct node * h) {
    if( h== NULL) {
        return 0;
    }
    struct node *temp = h;
    int val = temp->data;
    temp = temp ->next;
    while(temp != NULL) {
        if(temp->data < val) {
            return 0;
        }
        temp = temp->next;
    }
    return 1;
}

int equal(struct node * h1, struct node * h2) {
    if((h1== NULL) && (h2 == NULL)) {
        return 1;
    }
    else if( h1 == NULL || h2 == NULL) {
        return 0;
    }
    while(h1!= NULL && h2 != NULL) {
        if(h1-> data != h2-> data) {
            return 0;
        }
        h1= h1->next;
        h2= h2->next;
    }
   if(h1 != NULL || h2!= NULL) {
    return 0;
   }
    return 1;

}

struct node * removeMin(struct node * h) {
    if(h== NULL) {
        return h;
    }
    int minIndex = 0;
    int index = 0;
    int min = h->data;
    struct node *temp = h->next;
    while(temp != NULL) {
        index++;
        if(temp->data < min) {
            min = temp->data;
            minIndex = index;

        }
        temp = temp -> next;
    }
    temp =h;
    if(minIndex == 0) {
        struct node *t = h;
        h = temp->next;
        free(t);
        return h;
    }
    int i = 0;
    for(i = 0; i < minIndex - 1; i++) {
        temp = temp -> next;
    }
    struct node *t = temp->next;
    temp -> next = temp->next->next;
    free(t);
    return h;
}


/*******************************************************/


struct node * makeList(int *, int);
void printList(struct node *);

int main() {
    int task1_1[4] = {-4, 2, 19, 25};
    int task1_2[5] = {0, 3, 7, -1, 10};
    int task2_1[8] = {22, 19, 10, 105, -1, 62, 88, 12};
    int task2_2[8] = {22, 19, 11, 105, -1, 62, 88, 12};
    int task2_3[8] = {22, 19, 10, 105, -1, 62, 88, 10};
    int task2_4[3] = {22, 19, 10};
    int task3_1[5] = {18, -2, -5, 20, 10};
    int task3_min[4] = {18, -2, 20, 10};
    int task3_2[5] = {-18, 18, -2, 20, 10};
    int task3_3[5] = {18, -2, 20, 10, -3};
    int task3_4[1] = {99};

    struct node * empty = NULL;
    struct node * list1, *list2;

    int x = -1;
    struct node * rmin;

    /* Task 1 tests */
    printf("\n*** Task 1 tests ***\n\n");
    printf("Test #1 (in order): ");
    x = checkOrder(makeList(task1_1, 4));
    if (x == 1) printf("PASS\n");
    else printf("FAIL\n");

    printf("Test #2 (not in order): ");
    x = checkOrder(makeList(task1_2, 5));
    if (x == 0) printf("PASS\n");
    else printf("FAIL\n");

    printf("Test #3 (empty): ");
    x = checkOrder(empty);
    if (x == 0) printf("PASS\n");
    else printf("FAIL\n");

    /* Task 2 tests */
    printf("\n\n*** Task 2 tests ***\n\n");
    list1 = makeList(task2_1, 8);
    list2 = makeList(task2_1, 8);
    printf("Test #1 (equal): ");
    x = equal(list1, list2);
    if (x == 1) printf("PASS\n");
    else printf("FAIL\n");

    printf("Test #2 (not equal): ");
    list2 = makeList(task2_2, 8);
    x = equal(list1, list2);
    if (x == 0) printf("PASS\n");
    else printf("FAIL\n");

    printf("Test #3 (not equal): ");
    list2 = makeList(task2_3, 8);
    x = equal(list1, list2);
    if (x == 0) printf("PASS\n");
    else printf("FAIL\n");

    printf("Test #4 (not equal, different lengths): ");
    list2 = makeList(task2_4, 0);
    x = equal(list1, list2);
    if (x == 0) printf("PASS\n");
    else printf("FAIL\n");

    printf("Test #5 (one is empty): ");
    x = equal(list1, empty);
    if (x == 0) printf("PASS\n");
    else printf("FAIL\n");

    printf("Test #6 (one is empty): ");
    x = equal(empty, list1);
    if (x == 0) printf("PASS\n");
    else printf("FAIL\n");

    printf("Test #7 (both empty): ");
    x = equal(empty, empty);
    if (x == 1) printf("PASS\n");
    else printf("FAIL\n");

    printf("\n\n***Task 3 tests***\n\n");
    list1 = makeList(task3_min, 4);

    rmin = removeMin(makeList(task3_1, 5));
    printf("Test #1 (middle): ");
    if (equal(rmin, list1) == 1) printf("PASS\n");
    else printf("FAIL\n");

    rmin = removeMin(makeList(task3_2, 5));
    printf("Test #2 (first): ");
    if (equal(rmin, list1) == 1) printf("PASS\n");
    else printf("FAIL\n");

    rmin = removeMin(makeList(task3_3, 5));
    printf("Test #3 (last): ");
    if (equal(rmin, list1) == 1) printf("PASS\n");
    else printf("FAIL\n");

    rmin = removeMin(makeList(task3_4, 1));
    printf("Test #4 (one element): ");
    if (!rmin) printf("PASS\n");
    else printf("FAIL\n");

    rmin = removeMin(empty);
    printf("Test #5 (empty): ");
    if (!rmin) printf("PASS\n");
    else printf("FAIL\n");

    printf("\n");

    return EXIT_SUCCESS;


}

struct node * makeList(int * data, int n) {

    struct node *p, *prev, *h;
    int i;

    prev = NULL;
    h = NULL;
    if (data == NULL) return h;

    for (i=0; i<n; i++) {
        p = (struct node *) malloc(sizeof(struct node));
        p->data = data[i];
        p->next = NULL;

        if (prev) prev->next = p;
        else h = p;

        prev = p;
    }
    return h;
}

void printList(struct node *h) {
    printf("(");
    for (; h; h = h->next) printf(" %d", h->data);
    printf(" )");
}




