#include<iostream>
#include<string>
#include<cstring>
#include <unistd.h>
#include <assert.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>
#include<vector>

using namespace std;

int main(int argc,char **argv)
{
	vector<pid_t> kids;
	
	pid_t pid;
	int myPipe1[2];
	pipe(myPipe1);
	int myPipe2[2];
	pipe(myPipe2);
	
	pid=fork();
	if(pid == 0)
	{
		dup2(myPipe1[1],STDOUT_FILENO);
		close(myPipe1[0]);
		close(myPipe1[1]);
		execvp("./rgen",argv);
		fprintf(stderr, "an error occurred in execvp 1\n");
    	abort ();
	}
	kids.push_back(pid);
	pid=fork();
	if(pid == 0)
	{
		char *pName2=(char *)"ece650-a1.py";
		char *argv2[]=
		{
			(char *)"/usr/bin/python",
			pName2,
			NULL
		};
		
		dup2(myPipe1[0],STDIN_FILENO);
		/*//validate output of rgen
		while(!cin.eof())
		{
			string s;
			getline(cin,s);
			cout<<"From Handler : "<<s<<endl;
		}*/
		close(myPipe1[0]);
		close(myPipe1[1]);
		dup2(myPipe2[1],STDOUT_FILENO);
		close(myPipe2[0]);
		close(myPipe2[1]);
		execv("/usr/bin/python",argv2);
		fprintf(stderr, "an error occurred in execvp 2\n");
    	abort ();	
	}
	kids.push_back(pid);
	pid=fork();
	if(pid == 0)
	{
		char *pName3=(char *)"ece650-a2.cpp";
		char *argv3[]=
		{
			pName3,
			NULL
		};
		
		dup2(myPipe2[0],STDIN_FILENO);
		close(myPipe2[0]);
		close(myPipe2[1]);
		/*//validate output of python
		while(!cin.eof())
		{
			string s;
			getline(cin,s);
			cout<<"From Handler : "<<s<<endl;
		}*/	
		execvp("./ece650-a2",argv3);
		fprintf(stderr, "an error occurred in execvp 3\n");
    	abort ();	
	}
	kids.push_back(pid);

	dup2(myPipe2[1],STDOUT_FILENO);
	close(myPipe2[0]);
	close(myPipe2[1]);
	
	while(!cin.eof())
	{
		
		string sInput;
		getline(cin,sInput);
		if(!cin || sInput == "")
 		{
     		if(cin.eof())
         		//std::cout << "EOF\n";
         		break;
     		else
         		//std::cout << "other failure\n";
         		break;
 		}
 		else
 		{
			cout<<sInput<<endl;
		}
	}	
	
	
	for (unsigned i = 0; i < kids.size(); ++i) {
	    int status;
	    kill(kids[i],SIGTERM);
	    waitpid(kids[i],&status,0);
	    /*while (-1 == waitpid(kids[i], &status, 0));
	    if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
	        cerr << "Process " << i << " (pid " << kids[i] << ") failed" << endl;
	        exit(1);
	    }*/
	}
	
	return 0;
}

