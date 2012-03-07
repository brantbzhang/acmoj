#include<stdlib.h>
#include<mysql.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<limits.h>
#include<sys/types.h>
#include<sys/stst.h>
#include<queue>
#include<pthread.h>
#include<semaphore.h>
using namespace std;

typedef struct {
	int solution_id;
	char user_id[30];
	int problem_id,contest_id;
    //double time,memory;
	double stime,ntime;
	double run_t,run_m;
	int language,result,num;
}Submits;

struct probleminfo
{
    double time,memory;
    bool have;
}pinfo[MAXPROBLEM];

MYSQL my_connection;
queue<Sumits>sumit;
pthread_mutex_t work_mutex,query_mutex;
sem_t bin_sem;
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
    else printf("Database connection failure:%d,%s\n",mysql_errno(&my_connection),mysql_error(&my_connection));
}

inline void stop()
{
    if(dbconnected)mysql_close(&my_connection);
    sem_destroy(&bin_sem);
    exit(EXIT_SUCCESS);
}

inline void update_status(int id,int st)
{
    char sql[300];
    sprintf(sql,"update solution set result=%d where solution_id='%d';",st,id);
    mysql_query(my_connection,sql);
    return;
}

inline void update_result(Submits submit)
{
    update_submit_result();
    if(submit->contest_id!=0)
    {
	update_contest_result();
    }
    return;
}

inline void update_submit_result(Submits submit)
{
    char sql[300];
    sprintf(sql,"update solution set result='%d',time='%d',memory='%d' where solution_id='%d';",submit->result,(int)(submit->run_t*1000),(int)(submit->run_m*1024),submit->solution_id);
    mysql_query(my_connection,sql);
    return;
}

inline void update_contest_result()
{
     
}

inline book check()
{
    
}

inline void create_pthread()
{
    pthrea_t thread[MAxPOSIX];
    for(i=0;i<MAXPOSIX;i++)
    {
	res=pthread_create(&(thread[i]),NULL,thread_work,(void *)NULL);
	if(res!=0)
	{
	    printf("Thread creat failed!\n");
	    exit(EXIT_FAILURE);
	}
    }
}

void *thread_work(void *arg)
{
    Submits submit;
    char cmd[300];
    while(true)
    {
	sem_wait(&bin_sem);
	pthread_mutex_lock(&work_mutex);
	if(q.empty())
	{
	    exit(EXIT_FAILURE);
	}
	submit=q.front();q.pop();
	pthread_mutex_unlock(&work_mutex);
	compile(&submits)&&judger(&submit);
	update_result(submit);
	if(submit->language==3)
	{
	    sprintf(cmd,"rm -rf ./tmp/%d.java ./tmp/%d ./tmp/%d.out",submit->solution_id,submit->solution_id,submit->solution_id);
	}
	else sprintf(cmd,"rm -rf ./tmp/%d.cpp ./tmp/%d ./tmp/%d.out",submit->solution_id,submit->solution_id,submit->solution_id);
	system(cmd);
    }
}

inline bool judger(Submits *submit)
{
    
}

inline bool compile(Submits *submit)
{
    MYSQL_RES *res=NULL;
    MYSQL_ROW row=NULL;
    char sql[300],cmd[300],path[300];
    FILE *file;
    sprintf(sql,"select source from source_code where solution_id='%d';",submit_solution_id);
    pthread_mutex_lock(&query_mutex);
    if(mysql_query(&my_connection,sql))
    {
	printf("%s\n",mysql_error(&my_connection));
	return false;
    }
    res=mysql_use_result(&my_connection);
    pthread_mutex_unlock(&query_mutex);
    row=mysql_fetch_row(res);
    mysql_free_result(res);
    if(submit->language==3)
    {
	sprintf(path,"./tmp/%d.java",submit->solution_id);
	file=fopen(path,"wb");
	fprintf(file,"%s",row[0]);
	fclose(file);
	sprintf(cmd,"dos2unix ./tmp/%d.java",submit->solution_id);
	sprintf(sql,"java ./tmp/%d.java -d ./tmp/%d 2> ./err/%d",submit->solution_id,submit->solution_id,submit->solution_id);
    }
    else
    {
	sprintf(path,"./tmp/%d.cpp",submit->solution_id);
	file=fopen(path,"wd");
	fprintf(file,"%s",row[0]);
	fclose(file);
	sprintf(cmd,"dos2unix ./tmp/%d.cpp",submit->solution_id);
	sprintf(sql,"g++ ./tmp/%d.cpp -o ./tmp/%d -o0 -ansi -w 2> ./err/%d",submit->solution_id,submit->solution_id,submit_solution_id);
    }
    if(system(cmd)==0&&system(sql)==0)	return true;
    submit->result=CE;
    submit->run_t=0;
    submit->run_m=0;
    return false;
}

inline void init()
{
    mysql_connection();
    create_pthread();
    while(!q.empty())q.pop();
    int rs=pthread_mutex_init(&work_mutex,NULL);
    if(rs!=0)
    {
	printf("Work_mutex initialization failed!\n");
	exit(EXIT_FAILURE);
    }
    rs=pthread_mutex_init(&query_mutex,NULL);
    if(rs!=0)
    {
	printf("Query_mutex initialization failed!\n");
	exit(EXIT_FAILURE);
    }
    rs=sem_init(&bin_sem,0,0);
    if(rs!=0)
    {
	printf("Semaphore initialization failed!\n");
	exit(EXIT_FAILURE);
    }
    for(int i=0;i<MAXPROBLEM;i++)
    {
	pinfo[i]->have=false;
    }
}

inline  void get_pinfo(int problem_id)
{
    MYSQL_RES *res;
    MYSQL_ROW sqlrow;
    char sql[300];
    sprintf(sql,"select time_limit,memory_limit from problem where problem_id='%d';",problem_id);
    pthread_mutex_lock(&query_mutex);
    int rs=mysql_query(&my_connection,sql);
    if(rs)
    {
	printf("SELECT error: %s\n",mysql_error(&my_connection));
	exit(EXIT_FAILURE);
    }
    rs=mysql_use_result(&my_connection);
    pthread_mutex_unlock(&query_mutex);
    if((sqlrow=mysql_fetch_row(res))==NULL)
    {
	printf("Don't have problem %d\n",problem_id);
	exit(EXIT_FAILURE);
    }
    sscanf(row[0],"%lf",&pinfo[problem_id]->time);
    sscanf(row[1],"%lf",&pinfo[problem_id]->memory);
    mysql_free_result(res);
}

int main()
{
    int num;
    char sql[300];
    Submits submit;
    MYSQL_RES *res=NULL;
    MYSQL_ROW row=NULL;
    init();
    sprintf(sql,"select solution_id,problem_id,user_id,contest_id,num,stime,ntime,language from solution where result="%d" order by solution_id",WAITING);
    while(true)
    {
	pthread_mutex_lock(&query_mutex);
	if(mysql_query(&my_connection,sql)!=0)
	{
	    printf("%s\n",mysql_error(conn));
	}
	rs=mysql_store_result(&my_connection);
	if(rs)
	{
	    printf("mysql store failed!\n");
	    eixt(EXIT_FAILURE);
	}
	pthread_mutex_unlock(&query_mutex);
	while((row=mysql_fetch_row(res)))
	{
	    sscanf(row[0], "%d", &submit->solution_id);
	    sscanf(row[1], "%d", &submit->problem_id);
	    strcpy(submit->user_id, row[2]);
	    sscanf(row[3], "%d", &submit->contest_id);
	    sscanf(row[4], "%d", &submit->num);
	    sscanf(row[5], "%lf", &submit->stime);
	    sscanf(row[6], "%lf", &submit->ntime);
	    sscanf(row[7], "%d", &submit->language);
	    submit->result=COMPLIERING;
	    update_status(COMPLIERING,submit->solution_id);
	    if(!pinfo[submit->problem_id].have)
	    {
		get_pinfo(submit->problem_id);
	    }
	    pthread_mutex_lock(&work_mutex);
	    sem_post(&bin_sem);
	    q.push(sumit);
	    num=q.size();
	    pthread_mutex_unlock(&work_mutex);
	}
	mysql_free_result(res);
	usleep(300*1000+(num>4?num-4:0)*200*1000);
    }
}
