 #include<stdlib.h>
 #include<mysql.h>
#include<stdio.h>
#define host "localhost"
#define user "root"
#define password ""
#define database "judgeonline"
MYSQL my_connection;
typedef struct {
	int solution_id;
	char user_id[30];
	int problem_id,contest_id;
	double time,memory;
	double stime,ntime;
	double run_t,run_m;
	int language,result,num;
}Submits;

static bool dbconnected=false;
inline void mysql_connection()
{
    if(dbconnected)return;
    mysql_init(&my_connection);
    if(mysql_real_connect(&my_connection,host,user,password,database,0,NULL,0))
    {
	dbconnected=true;
	printf("connection success\n");
    }
    else printf("connection faild\n");
}
int main()
{
    mysql_connection();
}
