#include<stdlib.h>
#include<mysql.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<limits.h>
#include<sys/types.h>
#include<sys/stst.h>
#define FIFO_NAME "/tmp/my_fifo"
MYSQL my_connection;
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
    else fprintf(stderr,"Database connection failure:%d,%s\n",mysql_errno(&my_connection),mysql_error(&my_connection));
}
inline void stop()
{
    if(dbconnected)mysql_close(&my_connection);
    exit(1);
}
int main()
{
    pid_t child_pid;
    child_pid=fork();
    if(child_pid==-1)
    {
	perror("fork failed\n");
	exit(EXIT_FAILURE);
    }
    else if(!child_pid)
    {
	execl("./client",NULL,NULL);
    }
    int fifo_fd;
    char sql[300];
    Submits submit;
    MYSQL_RES *res=NULL;
    MYSQL_ROW row=NULL;
    mysql_connection();
    mkfifo(FIFO_name,0777);
    fifo_fd=open(FIFO_NAME,O_RDONLY);
    if(fifo_fd==-1)
    {
	fprintf("stderr,"FIFO failed\n"");
	exit(FAILURE);
    }
    sprintf(sql,"select solution_id,problem_id,user_id,contest_id,num,stime,ntime,language from solution where result="%d" order by solution_id limit 1",WAITING);
    while(true)
    {
	if(mysql_query(&my_connection,sql)!=0)
	{
	    fprintf(stderr,"Mysql failed!\n");
	}
	res=mysql_store_result(&my_connection);
	
	usleep(300*1000);
    }
}
