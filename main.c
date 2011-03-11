#include <stdio.h>
#include "mysql.h"
#include "errmsg.h"
#include <string.h>

void basicSearch();

int main (int argc, const char * argv[]) {
	MYSQL mysql;
	
	mysql_init(&mysql);
	
	mysql_options(&mysql,MYSQL_READ_DEFAULT_GROUP,"your_prog_name");
	if (!mysql_real_connect(&mysql,"localhost","Nate","Kelly123","FamilyHistory",0,NULL,0))
	{
		printf("Failed to connect to database: Error: %s\n", mysql_error(&mysql));
	}
	
	const char *info;
	info = mysql_get_server_info(&mysql);
	
	printf("server info: %s\r\n",info);

	const char *query = "Select FirstName, LastName, born, died, Cemetery, fatherid, motherid, countryorigin, infoid, spouseid from Person";

	
	MYSQL_STMT *mystatement;
	
	mystatement = mysql_stmt_init(&mysql);	
	
	if(!mystatement)
	{
		printf("mysql_stmt_init failed: %d\r\n",mysql_errno(&mysql));
	}
	
	int statementPrepare = mysql_stmt_prepare(mystatement, query, strlen(query));
	
	if(statementPrepare)
	{
		printf("mysql_stmt_prepare failed: %s\r\n",mysql_error(&mysql));	
	}
	
	MYSQL_RES     *prepare_meta_result;
	
	prepare_meta_result = mysql_stmt_result_metadata(mystatement);
	if (!prepare_meta_result)
	{
		printf(" mysql_stmt_result_metadata() returned no meta information: %s\n", mysql_stmt_error(mystatement));
	}
	
	int column_count= mysql_num_fields(prepare_meta_result);
	printf("Total columns in SELECT statement: %d\n", column_count);
	
	
	if (mysql_stmt_execute(mystatement))
	{
		printf(" mysql_stmt_execute(), failed  %s\n", mysql_stmt_error(mystatement));
	}
	
	char firstname[25];
	char lastname[25];
	MYSQL_TIME born;
	MYSQL_TIME died;
	char cemetary[100];
	int fatherid;
	int motherid;
	char countryorigin[50];
	int infoid;
	int spouseid;
	
	unsigned long length[10];
	my_bool is_null[10];
	my_bool error[10];
	
	MYSQL_BIND bind[10];
	
	memset(bind,0,sizeof(bind));
	
	bind[0].buffer_type = MYSQL_TYPE_STRING;
	bind[0].buffer = (char *)firstname;
	bind[0].buffer_length = 25;
	bind[0].is_null = &is_null[0];
	bind[0].error = &error[0];
	bind[0].length = &length[0];
	
	bind[1].buffer_type = MYSQL_TYPE_STRING;
	bind[1].buffer = (char *)lastname;
	bind[1].buffer_length = 25;
	bind[1].is_null = &is_null[1];
	bind[1].error = &error[1];
	bind[1].length = &length[1];
	
	bind[2].buffer_type = MYSQL_TYPE_DATE;
	bind[2].buffer = (char *)&born;
	bind[2].is_null = &is_null[2];
	bind[2].error = &error[2];
	bind[2].length = &length[2];

	bind[3].buffer_type = MYSQL_TYPE_DATE;
	bind[3].buffer = (char *)&died;
	bind[3].is_null = &is_null[3];
	bind[3].error = &error[3];
	bind[3].length = &length[3];
	
	bind[4].buffer_type = MYSQL_TYPE_STRING;
	bind[4].buffer = (char *)cemetary;
	bind[4].buffer_length = 100;
	bind[4].is_null = &is_null[4];
	bind[4].error = &error[4];
	bind[4].length = &length[4];

	bind[5].buffer_type = MYSQL_TYPE_LONG;
	bind[5].buffer = (char *)&fatherid;
	bind[5].is_null = &is_null[5];
	bind[5].error = &error[5];
	bind[5].length = &length[5];
	
	bind[6].buffer_type = MYSQL_TYPE_LONG;
	bind[6].buffer = (char *)&motherid;
	bind[6].is_null = &is_null[6];
	bind[6].error = &error[6];
	bind[6].length = &length[6];
	
	bind[7].buffer_type = MYSQL_TYPE_STRING;
	bind[7].buffer = (char *)countryorigin;
	bind[7].buffer_length = 50;
	bind[7].is_null = &is_null[7];
	bind[7].error = &error[7];
	bind[7].length = &length[7];
	
	bind[8].buffer_type = MYSQL_TYPE_LONG;
	bind[8].buffer = (char *)&infoid;
	bind[8].is_null = &is_null[8];
	bind[8].error = &error[8];
	bind[8].length = &length[8];

	bind[9].buffer_type = MYSQL_TYPE_LONG;
	bind[9].buffer = (char *)&spouseid;
	bind[9].is_null = &is_null[9];
	bind[9].error = &error[9];
	bind[9].length = &length[9];
	
	printf("binding\r\n");
	if (mysql_stmt_bind_result(mystatement, bind))
	{
		printf("mysql_stmt_bind_result() failed [%d]  %s\n", mysql_stmt_errno(mystatement), mysql_stmt_error(mystatement));
	}

	printf("storing\r\n");
	if (mysql_stmt_store_result(mystatement))
	{
		printf("mysql_stmt_store_result() failed [%d]  %s\n", mysql_stmt_errno(mystatement), mysql_stmt_error(mystatement));
	}
	
	printf("fetching\r\n");
	while(!mysql_stmt_fetch(mystatement))
	{
		printf("FirstName: %s ", is_null[0] ? "null" : firstname);
		printf("LastName: %s ", is_null[1] ? "null" : lastname);
		printf("Born: %02d-%02d-%04d ", is_null[2] ? 0,0,0 : born.month,born.day,born.year);
		printf("Died: %02d-%02d-%04d ", is_null[3] ? 0,0,0 : died.month,died.day,died.year);
		printf("Cemetary: %s ", is_null[4] ? "null" : cemetary);		
		printf("fatherid: %d ", is_null[5] ? 0 : fatherid);		
		printf("motherid: %d ", is_null[6] ? 0 : motherid);		
		printf("Country Origin: %s ", is_null[7] ? "null" : cemetary);		
		printf("infoid: %d ", is_null[8] ? 0 : infoid);
		printf("spouseid: %d ", is_null[9] ? 0 : spouseid);
	}

	mysql_free_result(prepare_meta_result);
	mysql_stmt_close(mystatement);
	mysql_close(&mysql);
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
