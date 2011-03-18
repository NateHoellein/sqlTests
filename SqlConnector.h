#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define FIRSTNAMESIZE  25
#define LASTNAMESIZE  25
#define CEMETARY 100
#define COUNTRYORIGIN 50

typedef struct family_person {
	char FirstName[FIRSTNAMESIZE];
	char LastName[LASTNAMESIZE];
	struct tm born;
	struct tm died;
	char Cemetary[CEMETARY];
	int fatherId;
	int motherId;
	char countryOrigin[COUNTRYORIGIN];
	int infoId;
	int spouseId;
} Person;

void getPersonById(const char *personId, Person *person);
int insertPerson(Person *person);