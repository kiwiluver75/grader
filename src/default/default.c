#include"sandbox.h"
#include"string.h"
#include"stdio.h"
#include"stdlib.h"
#include"sys/wait.h"

#define REAL  1000*10
#define CPU   1000*1
#define MEM   250*1024*1024
#define DISK  1024*1024

int main(int argc, const char* argv[]){
    const char *task=argv[1];
    const char *lang=argv[2];
    sandbox_t s;
    char prog[256];
    const char *c[3];
    long double ti;
    if(strcmp(lang,"cpp")*strcmp(lang,"c")*strcmp(lang,"python2")*strcmp(lang,"python3")==0){
        if(strcmp(lang,"cpp")*strcmp(lang,"c")==0){
            sprintf(prog,"./%s",task);
            c[0]=prog;
        } else if(strcmp(lang,"python2")==0){
            c[0]="/usr/bin/python2";
            c[1]=task;
        } else if(strcmp(lang,"python3")==0){
            c[0]="/usr/bin/python3";
            c[1]=task;
        }
        sandbox_init(&s,c);
        s.task.quota[S_QUOTA_WALLCLOCK]=REAL;
        s.task.quota[S_QUOTA_CPU]=CPU;
        s.task.quota[S_QUOTA_MEMORY]=MEM;
        s.task.quota[S_QUOTA_DISK]=DISK;
        s.task.uid=getuid();
        s.task.gid=getgid();
        FILE *ofp=fopen("../stdout","w");
        s.task.ofd=fileno(ofp);
        FILE *efp=fopen("../stderr","w");
        s.task.efd=fileno(efp);
        result_t* r=sandbox_execute(&s);
        fclose(ofp);
        fclose(efp);
        stat_t st=s.stat;
        ti=st.cpu_info.clock.tv_sec+st.cpu_info.clock.tv_nsec/1.0e9;
        if(*r!=S_RESULT_OK){
            switch(*r){
                case S_RESULT_TL:
                    printf("Wrong: time limit exceeded\n");
                    return 3;
                case S_RESULT_ML:
                    printf("Wrong: memory limit exceeded\n");
                    return 4;
                case S_RESULT_RT:
                    printf("Wrong: runtime error\n");
                    return 5;
                case S_RESULT_AT:
                    printf("Wrong: abnormal termination\n");
                    return 5;
                case S_RESULT_RF:
                    printf("Wrong: restricted function\n");
                    return 6;
            }
        }
    } else if (strcmp(lang,"java")==0) {
        sprintf(prog,"ulimit -t 2;/usr/bin/java -Djava.security.manager -Djava.security.policy=../policy -Xmx%d -Xms%d %s",MEM,MEM,task);
        struct timeval start, end;
        gettimeofday(&start, NULL);
        int res = system(prog);
        gettimeofday(&end, NULL);
        ti=(end.tv_sec-start.tv_sec)+(end.tv_usec - start.tv_usec)/1.0e6;
		/*printf("asdf:%d\n", res);
		printf("%d\n", WIFEXITED(res));
		printf("%d\n", WIFSIGNALED(res));
		printf("%d\n", WEXITSTATUS(res));*/
		if(WEXITSTATUS(res) != EXIT_SUCCESS) {
			printf("Wrong: time limit exceeded\n");
			return 3;
		}
    }

    char resfile[256],corfile[256];
    strcpy(resfile,task);strcat(resfile,".out");
    strcpy(corfile,"../");strcat(corfile,resfile);

    FILE *cor=fopen(corfile,"r");

    bool good=true;
    FILE *res;
    if((res=fopen(resfile,"r"))!=NULL){
        while(!feof(cor)){
			char resc = fgetc(res);
			char corc = fgetc(cor);
            if(resc!=corc){
                good=false;
                //break;
            }
			printf("%c",resc);
        }
		printf("\n");
    } else
        good=false;
    if(good){
        printf("OK %Lf\n",ti);
        return 0; // correct
    } else {
        printf("Wrong: incorrect output\n");
        return 2; // wrong
		// return 1 apparently doesn't work
    }
}
