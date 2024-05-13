#include<stdlib.h>
#include<stdio.h>
#include<string.h>

const int INITIAL_CAPACITY = 100;

char *userText = NULL; // pointer
size_t capacity = 0; //  capacity of the text
size_t length = 0; //  text length


int appendText(char *enteredText)
{
	size_t textLen = strlen(enteredText);
	size_t capacityNeeded = length + textLen + 1;

	if (capacityNeeded > capacity)
	{
		while (capacity < capacityNeeded)
		{
			if (capacity == 0) 
			{
				capacity = INITIAL_CAPACITY;
			}
			else 
			{
				capacity = capacity * 2;
			}
		}

		userText = (char*)realloc(userText, capacity * sizeof(char));
		if (userText == NULL)
		{
			printf("Memory allocation failed.\n");
			return 1;
		}
	}

	if (enteredText == NULL)
	{
		printf("Opps... Entered text is null.\n");
		return 1;
	}

	if (enteredText[0] == '\0')
	{
		printf("Opps... Entered text is empty.\n ");
	}

	strcat_s(userText, capacityNeeded, enteredText);
	length += textLen;

	return 0;
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
	printf("Your text: \n%s\n", userText);
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
	system("clear");
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
		char userText[INITIAL_CAPACITY];
		printf("Executing command 1\n\n");
		printf("Enter text to append: ");
		fgets(userText, sizeof(userText), stdin);

		if (userText[strlen(userText) - 1] == '\n')
		{
			userText[strlen(userText) - 1] = '\0';
		}

		appendText(userText);			   
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

	printf("Welcome to Text Editor!\n");
	printf("Type '--help' to see the list of commands\n\n");

	userText = (char*)calloc(INITIAL_CAPACITY, sizeof(char));

	if (userText == NULL)
	{
		printf("Memory allocation failed\n");
		return 1;
	}
	capacity = INITIAL_CAPACITY;


	char userInput[10];
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

	free(userText);
	return 0;
}