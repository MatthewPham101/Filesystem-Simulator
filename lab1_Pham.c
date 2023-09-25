#include <stdio.h>            
#include <stdlib.h>    
#include <string.h>     
// you can use additional headers as needed

typedef struct node {
	char  name[64];       // node's name string
	char  type;
	struct node *child, *sibling, *parent;
} NODE;


NODE *root; 
NODE *cwd;
char *cmd[] = {"mkdir", "rmdir", "cd", "ls", "pwd", "create", "rm", "save", "reload", "quit", 0};  // fill with list of commands



void initialize() {
	root = (NODE *)malloc(sizeof(NODE));
	strcpy(root->name, "/");
	root->parent = root;
	root->sibling = 0;
	root->child = 0;
	root->type = 'D';
	cwd = root;
	printf("Filesystem initialized!\n");
}

// <summary>
// Create a new directory.
void mkdir(char* path)
{
	
	path[strcspn(path, "\n")] = 0;
	NODE *pMem = cwd->child;
	// go through the directory sibblings to see if there are one with the same name
	while(pMem != NULL)
	{
		if(strcmp(pMem->name, path) == 0)
		{
			printf("there is a directory already exist\n");
			return;
		}
		pMem = pMem->sibling;
	}
	
	NODE *newDir = (NODE*)malloc(sizeof(NODE));
	pMem = cwd->child;
	strcpy(newDir->name, path);
	newDir->type = 'D';
	newDir->parent = cwd;

	if(path[0] == '/')
		{
			printf("error cannot create\n");
			
		}
	else
	{
		if(pMem != NULL)
		{
			while(pMem->sibling != NULL)
			{
				pMem = pMem->sibling;
			}
			pMem->sibling = newDir;
		}
		else
		{
			cwd->child = newDir;
		}
		printf("directory %s created\n", path);	
	}
	
}
// <summary>
// Remove a directory.
void rmdir(char *path)
{
	path[strcspn(path, "\n")] = 0;
	NODE *pPrev = NULL;
	NODE* pMem = cwd->child;

	if(pMem == NULL)
	{
		printf("there is no directory existed!\n");
		return;
	}

	// loops through the entire sibblings until the sibbings name matches the path trying to remove name
	while(strcmp(pMem->name, path ) != 0 && pMem != NULL )
	{
		pPrev = pMem;
		pMem = pMem->sibling;
		break;
	}

	if(pMem != NULL)
	{
		if(pMem->child != NULL)
		{
			printf("cannot delete directory because it's not empty\n");
		}
		else if(pMem == NULL || pMem->type == 'F')
		{
			printf("\nError please enter a correct directory or there is no directory exist\n\n");
			return;
		
		}
		else{
			if(pPrev == NULL)
			{
				cwd->child = pMem->sibling;
			}
			else{
				pPrev->sibling = pMem->sibling;
			}
			free(pMem);
			printf("directory %s deleted\n", path);
		} 
		
	}
	else
	{
		printf("Directory %s not found\n", path);
	}
}
// <summary>
// Change the current working directory to the root.
void cdRoot()
{
	cwd = root;
}
// <summary>
// Change the current working directory to the specific path.
void cd(char *path)
{
	path[strcspn(path, "\n")] = 0;
	NODE *pMem = cwd->child;
	// if cd ..
	if(strcmp(path, "..") == 0)
	{
		if(cwd != root)
		{
			cwd = cwd->parent;
		}
	}
	// if cd directory name
	while(pMem != NULL)
	{
		if (strcmp(pMem->name, path) == 0 && pMem->type == 'D')
		{
			cwd = pMem;
			return;
		}
		pMem = pMem->sibling;
	}
	
	
	
}
// <summary>
// List the contents of the current directory.
void ls()
{
	NODE *curDir = cwd->child;
	if(curDir == NULL)
	{
		printf("the directory is empty");
	}
	while(curDir != NULL)
	{
		printf("\n%c   %s", curDir->type, curDir->name);
		curDir = curDir->sibling;
	}
	printf("\n\n");
}
// <summary>
// Print the current working directory path.
void pwd(NODE *curCwd)
{
	if (curCwd == root) {
        printf("/");
		return;
    }
	pwd(curCwd->parent);
	printf("%s", curCwd->name);
}
//helper function for pwd
void pwdHelper()
{
	pwd(cwd);
	printf("\n");
}
// <summary>
// Create a new file.
void creat(char* nFile)
{
	nFile[strcspn(nFile, "\n")] = 0;
	NODE* pTemp = cwd->child;
	NODE* pMem = (NODE*)malloc(sizeof(NODE));
	strcpy(pMem->name, nFile);
	pMem->type = 'F';
	pMem->parent = cwd;
	
	while(pTemp != NULL )
	{
		if(pTemp->type == 'F' && strcmp(pTemp->name, nFile) == 0)
		{
			printf("There is a file already exist\n");
			return;
		}
	}

	if(cwd->child == NULL)
	{
		cwd->child = pMem;
	}
	else{
		pMem = cwd->child;
		while(pMem ->sibling != NULL)
		{
			pMem = pMem->sibling;
		}
		pMem->sibling = pMem;
	}
	printf("file Created %s\n", nFile);

}
// <summary>
// Remove a file.
void rm(char* nFile)
{
	nFile[strcspn(nFile, "\n")] = 0;
	NODE *pPrev = NULL;
	NODE* pMem = cwd->child;

	if(pMem == NULL || pMem->type == 'D')
	{
		printf("\nError please enter a correct file or there is no file exist\n\n");
		return;
	}

	if( pMem->type == 'D')
	{
		printf("\nError please enter a correct file or there is no file exist\n\n");
		return;
	}

	

	// loops through the entire sibblings until the sibbings name matches the path trying to remove name
	while(strcmp(pMem->name, nFile ) != 0 && pMem != NULL )
	{
		pPrev = pMem;
		pMem = pMem->sibling;
		break;
	}
	if(pMem != NULL)
	{
		if( pMem->type == 'D')
		{
		printf("\nError cannot delete because it's not a File\n\n");
		return;
		}
		else{
			if(pPrev == NULL)
			{
				cwd->child = pMem->sibling;
			}
			else{
				pPrev->sibling = pMem->sibling;
			}
			free(pMem);
			printf("file %s deleted\n", nFile); 
		}	
	}
	else
	{
		printf("file %s not found\n", nFile);
	}
}


// save function helper

void saveHelper(FILE *nFile, NODE* mainRoot, char *npath)
{
	char currentPath[256];
	//edge case
	if (mainRoot == NULL)
    {
        return;
    }

    strcpy(currentPath, npath);    
    strcat(currentPath, mainRoot->name);
	if(mainRoot != root)
	{
		strcat(currentPath, "/");
	}

    //printf("%c %s\n", mainRoot->type, currentPath);
    fprintf(nFile, "%c %s\n", mainRoot->type, currentPath);

    saveHelper(nFile, mainRoot->child, currentPath);
    saveHelper(nFile, mainRoot->sibling, npath);
    

}
// <summary>
// Save the file system tree to a file.
void save()
{

	char path[256] = "";
    FILE *fp = fopen("fssim_Pham.txt", "w");

    if (fp == NULL)
    {
        printf("Error: Unable to open or create the file for saving.\n");
        return;
    }

    saveHelper(fp, root, path);

    fclose(fp);
    printf("Filesystem saved.\n");
}


// <summary>
// Reload the file system tree from a file.
void reload()
{
	FILE *fp = fopen("fssim_Pham.txt", "r");
    if (fp == NULL) {
        printf("Error: Unable to open the saved file for reloading.\n");
        return;
    }

    char line[256];
	fgets(line, sizeof(line), fp);
    while (fgets(line, sizeof(line), fp)) 
	{
		char* token = strtok(line, " ");
		token = strtok(NULL, "/");
		char type = line[0];
		char name[256]; 

		while(token != NULL)
		{
			NODE* pMem = root;
			NODE* parent = root;
			NODE* prev = NULL;
			pMem = root->child;
			if(strcmp(token, "\n")!=0)
			{
				
				strcpy(name, token);
				while(pMem != NULL)
				{
				if(strcmp(pMem->name, token) == 0)
				{
					prev = pMem->child;
					parent = pMem;
					pMem = pMem->child;
					token = strtok(NULL, "/");
					
				}
				else 
				{
					prev = pMem;
					pMem = pMem->sibling;
				}
				}
				pMem = (NODE*)malloc(sizeof(NODE));
				strcpy(pMem->name, token);
				pMem->type = type;
				pMem->child = NULL;
				pMem->sibling = NULL;
				pMem->parent = parent;
			
				if(parent->child == NULL)
				{
					parent->child = pMem;
				}
				
				if(prev != NULL)
				{
					prev->sibling = pMem;
				}

			}
			
			token = strtok(NULL, "/");
			
		}
	}
	fclose(fp);
}

// <summary>
// Quit the program, saving the file system tree.

int quit()
{
	save();
	printf("Filed save Thank You");
	return 0;
}


int main() {
	initialize();
	// other initialization as needed
	
	while(1) {
		printf("Enter command [mkdir, rmdir, cd, ls, pwd, create, rm, save, reload, quit]: ");
		// complete implementations

		
		char command[256];
		char temp[256];
		fgets(command, sizeof(command), stdin);
		strcpy(temp, command);
		command[strcspn(command, "\n")] = 0;
		char* token = strtok(command, " ");
		char* subtoken = strtok(temp, " ");
		token = strtok(NULL, " ");
		

		if(token == NULL)
		{
			if(strcmp(command, "reload") == 0){
				reload();
			}

			else if(strcmp("ls", command) == 0){
				ls();
			}

			else if(strcmp("pwd", command) == 0){
				pwdHelper();
			}

			else if(strcmp("cd", command) == 0){
				cdRoot();
			}

			else if(strcmp("save", command) == 0){
				save();
			}


			else if(strcmp("quit", command) == 0){
				quit();
				return 0;
			}
			else
			{
			printf("there's an error in the Commands\n");
			}
		}
		else if (token != NULL)
		{

			if(strcmp(subtoken, "mkdir") == 0)
			{
				
				mkdir(token);
	
			}
			else if(strcmp("rmdir", subtoken) == 0)
			{
				rmdir(token);
			}

			else if(strcmp("rm", command) == 0){
				rm(token);
			}

			else if(strcmp("cd", subtoken) == 0){
				cd(token);
			}

			else if(strcmp("creat", subtoken) == 0){
				creat(token);
			}

		}
		else
			{
			printf("there's an error in the commands\n");
			}
	}
	return 0;
}



