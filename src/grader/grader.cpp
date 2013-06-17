#include<boost/filesystem.hpp>
#include<string>
#include<cstdio>
#include<fstream>
#include<sys/wait.h>
using namespace std;
using namespace boost::filesystem;

#define JPOLICY "grant {permission java.io.FilePermission \"%s.in\", \"read\";\
permission java.io.FilePermission \"%s.out\", \"write\";};\n"

int main(int argc, const char *argv[]){
    if(argc!=5){
        fprintf(stderr,"%s","./grader {judge} {file} {task} {lang}\n");
        return 1;
    }
    const char *judge=argv[1];
    //const char *user =argv[2];
	const char *file =argv[2];
    const char *task =argv[3];
    const char *lang =argv[4];
    int r;
    const char *wd = getenv("PWD");
    char jail[250],judgecmd[250],infile[250],outfile[250],data[250],in[250],\
         out[250],inner[250],cmd[250],src[250],ex[250],ex1[250],retf[250],\
         tmp[250],policy[250],judgeb[250];
    //sprintf(jail,"%s/jails/%s_%s",wd,user,task);
    sprintf(jail,"%s/jails/%s",wd,file);
    sprintf(infile,"%s/jail/%s.in",jail,task);
    sprintf(outfile,"%s/%s.out",jail,task);
    sprintf(data,"%s/data/%s/%s.%%d.%%s",wd,task,task);
    sprintf(inner,"%s/jail",jail);
    //sprintf(src,"%s/ans/%s_%s.%s",wd,user,task,lang);
    sprintf(src,"%s/submissions/%s",wd,file);
    sprintf(judgeb,"%s/judges/%s",wd,judge);
    sprintf(judgecmd,"%s/judges/%s %s %s",wd,judge,task,lang);
    sprintf(retf,"%s/ret",jail);
    
    if(!exists("jails"))
        create_directory("jails");

    if (exists(jail)) { // jail exists
        fprintf(stderr,"Jail %s exists.\n",jail);
        return 0;
    }
    
    create_directory(jail);
    if(strcmp(lang,"c")==0){
        sprintf(tmp,"%s/%s",jail,task);
        int pid,s;
        pid=vfork();
        if(pid==0){
            execl("/usr/bin/g++","g++","-xc","-w","-O2",src,"-o",tmp,(char*)0);
        } else {
            waitpid(pid,&s,0);
        }
        sprintf(ex,"%s/%s",jail,task);
        sprintf(ex1,"%s/%s",inner,task);
    } else if(strcmp(lang,"cpp")==0){
        sprintf(tmp,"%s/%s",jail,task);
        int pid,s;
        pid=vfork();
        if(pid==0){
            execl("/usr/bin/g++","g++","-w","-O2",src,"-o",tmp,(char*)0);
        } else {
            waitpid(pid,&s,0);
        }
        sprintf(ex,"%s/%s",jail,task);
        sprintf(ex1,"%s/%s",inner,task);
    } else if(strcmp(lang,"python2")*strcmp(lang,"python3")==0){
        sprintf(tmp,"%s/%s",jail,task);
        copy_file(src,tmp);
        sprintf(ex,"%s/%s",jail,task);
        sprintf(ex1,"%s/%s",inner,task);
    } else if(strcmp(lang,"java")==0){
        sprintf(tmp,"%s/%s.java",jail,task);
        copy_file(src,tmp);
        sprintf(cmd,"cd %s;javac %s.java",jail,task);
        system(cmd);
        sprintf(ex,"%s/%s.class",jail,task);
        sprintf(ex1,"%s/%s.class",inner,task);
        sprintf(policy,"%s/policy",jail);
        FILE *p=fopen(policy,"w");
        fprintf(p,JPOLICY,task,task);
        fclose(p);
    } else {
        remove_all(jail);
        fprintf(stderr,"Unsupported language\n");
        return 1;
    }

    if(!exists(ex)){
        remove_all(jail);
        fprintf(stderr,"Compile error\n");
        printf("c\n");
        return 1;
    }

    for(int i=1;;i++){
        sprintf(in,data,i,"in");
        sprintf(out,data,i,"out");
        if(is_regular_file(in)&&is_regular_file(out)){ // case exists
            create_directory(inner);
            copy_file(in,infile);
            copy_file(out,outfile,copy_option::overwrite_if_exists);
            copy_file(ex,ex1);
						if(strcmp(lang,"java")==0){
							char sclscmd[256]; //SubCLaSs CoMmanD
							sprintf(sclscmd,"cp %s/%s*.class %s/",jail,task,inner);
							system(sclscmd);
						}
            pid_t pid=vfork();
            if(pid==0){
                current_path(inner);
                dup2(2,1);
                execl(judgeb,judge,task,lang,(char*)0);
            } else {
                int s;
                waitpid(pid,&s,0);
                r=WEXITSTATUS(s);
            }
            switch(r){
                case 0: printf("*"); break;
				// return 1 apparently doesn't work
                case 2: printf("x"); break;
                case 3: printf("t"); break;
                case 4: printf("m"); break;
                case 5: printf("e"); break;
                case 6: printf("r"); break;
            }
            remove_all(inner);
        } else break;
    }
    remove_all(jail);
    fprintf(stderr,"\n");
    printf("\n");
    return 0;
}
