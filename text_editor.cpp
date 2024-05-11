#include<stdlib.h>
#include<stdio.h>
#include<string.h>


void appendText()
{
	printf("There will be a function to appent text symbols to the end\n");
}

void newLine()
{
	printf("There will be a function to start new line\n");
}

void loadFile()
{
	printf("There will be a function to load the info to a file\n");
}

void saveInfo()
{
	printf("There will be a function to save the info to a file\n");
}

void printInfo()
{
	printf("There will be a function to print the info\n");
}

void insertInfo()
{
	printf("There will be a function to insert the text by line and symbol index\n");
}

void search()
{
	printf("There will be a function to search\n");
}

void cleanConsole()
{
	printf("There will be a function to clean the console\n");
}

void helpInfo()
{
	printf("Command 1: Append text symbols to the end\n");
	printf("Command 2: Start the new line\n");
	printf("Command 3: Use files to loading the information\n");
	printf("Command 4: Use files to saving the information\n");
	printf("Command 5: Print the current text to console\n");
	printf("Command 6: Insert the text by line and symbol index\n");
	printf("Command 7: Search\n");
	printf("Command 8:  Clearing the console\n\n");
}

void commandParser(char *cmd)
{
	int userCommand = atoi(cmd);

	switch (userCommand)
	{
	case 1:
		printf("Executing command 1\n\n");
		appendText();			   
		break;					   
	case 2:						   
		printf("Executing command 2\n\n");
		newLine();				   
		break;					   
	case 3:						   
		printf("Executing command 3\n\n");
		loadFile();				   
		break;					   
	case 4:						   
		printf("Executing command 4\n\n");
		saveInfo();
		break;
	case 5:
		printf("Executing command 5\n\n");
		printInfo();
		break;
	case 6:
		printf("Executing command 6\n\n");
		insertInfo();
		break;
	case 7:
		printf("Executing command 7\n\n");
		search();
		break;
	case 8:
		printf("Executing command 8\n\n");
		cleanConsole();
		break;
	default:
		printf("The command is not implemented. Type '--help' for available commands.\n\n");
		break;
	}
}

int main() {
	char userInput[100];

	printf("Welcome to Text Editor!\n");
	printf("Type '--help' to see the list of commands\n\n");

	while (true)
	{
		printf(">> ");
		fgets(userInput, sizeof(userInput), stdin);

		if (userInput[strlen(userInput) - 1] == '\n')
		{
			userInput[strlen(userInput) - 1] = '\0';			// by chatgpt
		}

		if (strcmp(userInput, "--help") == 0)
		{
			helpInfo();
		}
		else if (strcmp(userInput, "--quit") == 0)
		{
			printf("Thank you for using this editor! Bye!");
			break;
		}
		else 
		{
			commandParser(userInput);
		}

	}

	return 0;
}