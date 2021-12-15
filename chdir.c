
/*  Input dir path from command line and diplay dir contents
		terminal>> ./assign01.out/home
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<dirent.h>

struct dirent *struct_dir;

int main (int argc,char *argv[])
{

	char cur[128];
	int ret, temp;
	DIR *fd;

	printf("current working dir >>> %s \n",getcwd(cur,128));
	//printf("userr enter dir >>> %s\n",argv[1]);
	ret = chdir(argv[1]);

	if (ret == 0)
		printf("A/F changing the current working dir >>> %s \n",getcwd(cur,128));
	else
		printf("chdir Failed !!! \n");
	
	//--------------------------------------------------------------------
	fd = opendir(argv[1]);

	if(fd == NULL)
		perror("opendir Failed !\n");
	else
		printf("opendir Success !\n");

	printf(">>Name<<\t>>i-node<<\t>>Type<< \n");
	while (struct_dir = readdir(fd))
	{
		printf("%-14s\t",struct_dir->d_name);
		printf("%-10lu",struct_dir->d_ino);
		printf("%10d\n",struct_dir->d_type);

	}

	closedir(fd);
	printf("Directory is closed !\n");

	return 0;
}
