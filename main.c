/*
 * This program prints the list of unused headers in C project.
 * It gets the path to the C project as input.
 * Prints the list of unused header file in stdout.
 * 
 *	To run the program: 
 * 					>gcc -o test main.c
 * 					>./test <path_to_C_Project>
 * 
 * 
 * Author: X.JOE CLAIMENT RAJA
 * 
 * 
 * 
 * 
 * /



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <dirent.h>
int filecheck(char *a1,char *headertocheck,char *makefiletocheck)
{
	int flag=-1;
	FILE* fp;		//File pointer
	char s[250];
	for(int i=0;i<=strlen(a1);i++)
		s[i]=*(a1+i);
	
	strcat(a1,"/");
	strcat(a1,makefiletocheck);
	fp=fopen(a1,"r");			// Open the Makefile in the Project Directory
	char *str;					// Buffer to read the contents of Makefile
	str=malloc(sizeof(char)*255);// Dynamic memory allocation to buffer
	if(fp)
	{
		while(fscanf(fp,"%s ",str)!=EOF) //Input the contents of file string by string to the buffer
		{
			if(strstr(str,headertocheck)) // If the buffer has the Header file
			{	flag=1;
				break;
			}
			else
			{
				flag=0;
			}
		}
		fclose(fp);		// close the file opened
	}
	
	strcpy(a1,s);
	free(str);			//Free the buffer
	if(flag==1)
		return 1;		//Return 1 if the file has header
	else
		return 0;		//Return 0 if the file does not have header
}
int main(int argc, char **argv)
{
	printf("The unused headers:\n");
	char *path;   
	path=*(argv+1);   // Path stores the <path_to_C_Project>
	DIR *d;
	d=opendir(path);
	struct dirent* dir;
	if(d)			// If directory exists
	{
	while((dir=readdir(d))!=NULL)
		{
			path=*(argv+1);
			if(dir->d_type==DT_REG)  //If content of the directory is file
			{
				 if(strstr(dir->d_name,".h"))	//If the file is a header file or file with extension *.h
				{
					if(filecheck(path,dir->d_name,"Makefile")!=1) // If the header file is not present in the Makefile
						printf("%s\n",dir->d_name);					// then the header file is unused header and it is printed.
				}
					
			}
			
		}
	closedir(d); 	// Close the Directory
	}
	return 0;
}
