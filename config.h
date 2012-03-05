#define WAITING 0
#define COMPLIERING 10
#define RUNNING 9
#define CE 8
#define WA 5
#define TLE 3
#define OLE 7
#define RE 6
#define PE 2
#define AC 1
#define SYSTEM_ERR 11
#define MLE 4
#define RF 12 
#define STATUS_SIG 7
#define STATUS_AC 8
#define host "localhost"
#define user "root"
#define password ""
#define database "judgeonline"
typedef struct {
	int solution_id;
	char user_id[30];
	int problem_id,contest_id;
	double time,memory;
	double stime,ntime;
	double run_t,run_m;
	int language,result,num;
}Submits;
