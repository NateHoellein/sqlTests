#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SqlConnector.h"

void basicSearch();

int main (int argc, const char * argv[]) {

	Person person;
	memset(&person,0,sizeof(Person));
	getPersonById("2", &person);
	
	printf("FirstName: %s \n", person.FirstName);
	printf("LastName: %s \n", person.LastName);
	printf("Born: %02d-%02d-%04d \n", person.born.tm_mon,person.born.tm_mday,person.born.tm_year);
	printf("Died: %02d-%02d-%04d \n", person.died.tm_mon,person.died.tm_mday,person.died.tm_year);
	printf("Cemetary: %s \n", person.Cemetary);		
	printf("fatherid: %d \n", person.fatherId);		
	printf("motherid: %d \n", person.motherId);		
	printf("Country Origin: %s \n", person.countryOrigin);		
	printf("infoid: %d \n", person.infoId);
	printf("spouseid: %d \n", person.spouseId);
	printf("\r\n");
	
    return 0;
}

void basicSearch()
{
	//	int insertResult = 0;
	
	//	insertResult = mysql_query(&mysql,"Select * from Person");
	
	//	printf("selected (%d) rows",insertResult);
	
	//	MYSQL_RES *result = mysql_store_result(&mysql);
	//	int numfields = 0;
	//	if(result)
	//	{
	//		numfields = mysql_num_fields(result);
	//		printf("Number of Fields %d\r\n",numfields);
	//		MYSQL_ROW row;
	//		while((row = mysql_fetch_row(result)))
	//		{
	//			for(int i = 0; i < numfields; i++)
	//			{
	//				printf("[%s] ",row[i] ? row[i] : "NULL");
	//			}
	//		}	
	//	}
	//	else
	//	{
	//		if(mysql_error(&mysql))
	//		{
	//			printf("Error: %s\r\n",mysql_error(&mysql));
	//		}
	//	}
	//
}
