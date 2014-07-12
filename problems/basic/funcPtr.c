#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (* compareKeys_t) (void *a, void *b);

compareKeys_t compareKeys;

#define MAXSIZE 32


typedef struct __person_t__ {
	char name[MAXSIZE];
	int age;
} person_t;


int compareIntKeys(void *a, void *b)
{
	int *a1, *b1;

	a1 = (int *)a;
	b1 = (int *)b;

	return ((*a1) - (*b1));
}

int compareFloatKeys(void *a, void *b)
{
	float *a1, *b1;

	a1 = (float *)a;
	b1 = (float *)b;

	return ((*a1) - (*b1));
}

int comparePersons(void *a, void *b)
{
	person_t *p1, *p2;
	p1 = (person_t *)a;
	p2 = (person_t *)b;

	return (p1->age - p2->age);
}

typedef struct __compare_fn_t__ {
	compareKeys_t	intCompare;
	compareKeys_t	floatCompare;
	compareKeys_t	personCompare;
} compare_fn_t;

compare_fn_t comparisons;

person_t * createPerson(char *name, int age)
{
	person_t *person = malloc(sizeof(person_t));
	strcpy(person->name, name);
	person->age = age;
	return person;
}

int main()
{
	int i1, i2;
	float f1, f2;
	person_t *p1, *p2;

	comparisons.intCompare = compareIntKeys;
	comparisons.floatCompare = compareFloatKeys;
	comparisons.personCompare = comparePersons;

	i1 = 2;
	i2 = 1;
	if (comparisons.intCompare(&i1, &i2) > 0) {
		printf("%d is greater than %d\n",i1, i2);
	}

	f1 = 2.0;
	f2 = 1.0;
	if (comparisons.floatCompare(&f1, &f2) > 0) {
		printf("%f is greater than %f\n",f1, f2);
	}

	p1 = createPerson("Victor", 12);
	p2 = createPerson("Shalini", 10);
	if (comparisons.personCompare(&p1, &p2) > 0) {
		printf("%s is older than %s\n",p1->name, p2->name);
	}

	return 0;
}