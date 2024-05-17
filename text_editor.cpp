#include<stdlib.h>
#include<stdio.h>
#include<string.h>

const int INITIAL_CAPACITY = 100;

char *userText = NULL; // pointer
size_t capacity = 0; //  capacity of the text
size_t length = 0; //  text length


bool file_exists(const char* filename)
{
	FILE* file = nullptr;
	
	errno_t err;
	
	err = fopen_s(&file, filename, "r");

	bool is_exists = false;

	if (err == 0)
	{
		is_exists = true;
		fclose(file);
	}

	return is_exists;
}

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
				capacity = sizeof(enteredText);
			}
			else 
			{
				capacity += sizeof(enteredText);
			}
		}

		char* temp = (char*)realloc(userText, capacity * sizeof(char));

		if (temp != NULL)
		{
			userText = temp;
		}

		if (userText == NULL)
		{
			printf(">>Memory allocation failed.\n");
			free(userText);
			return 1;
		}
	}

	if (enteredText == NULL)
	{
		printf(">>Opps... Entered text is null.\n");
		return 1;
	}

	if (enteredText[0] == '\0')
	{
		printf(">>Opps... Entered text is empty.\n ");
	}

	strcat_s(userText, capacity, enteredText);
	length += textLen;

	printf(">>Text has been appended successfully!:)\n");

	return 0;
}

int toEnterText()
{
	char* userEnterText = NULL;

	userEnterText = (char*)calloc(INITIAL_CAPACITY, sizeof(char));

	if (userEnterText == NULL)
	{
		printf("Memory allocation failed\n");
		return 1;
	}

	fgets(userEnterText, INITIAL_CAPACITY, stdin);

	size_t userEnterTextLen = strlen(userEnterText);

	if (userEnterText[0] == '\0')
	{
		printf(">>Opps... Entered text is empty.\n ");
	}

	if ((userEnterTextLen >= INITIAL_CAPACITY - 1) && (userEnterText[userEnterTextLen - 1] == '\n'))
	{
		char *temp = (char*)realloc(userEnterText, (INITIAL_CAPACITY + userEnterTextLen) * sizeof(char));

		if (temp != NULL)
		{
			userEnterText = temp;
		}

		if (userEnterText == NULL)
		{
			printf("Memory allocation failed\n");
			return 1;
		}

	}

	if (userEnterText[strlen(userEnterText) - 1] == '\n')
	{
		userEnterText[strlen(userEnterText) - 1] = '\0';
	}

	appendText(userEnterText);
	free(userEnterText);
}

void newLine()
{
	printf("*There will be a function to start new line*\n");
	char newLine[] = "\n";
	appendText(newLine);
}

int loadFile(char *fileName)
{
	printf("*There will be a function to load the info to a file*\n");

	FILE* file;

	errno_t err;

	err = fopen_s(&file, fileName, "r");

	if (err != 0)
	{
		printf(">>There no file.\n");
		return 1;
	}

	char *buffer = NULL;
	size_t bufferCapacity = 0;
	size_t bufferLength = 0;

	while (1)
	{
		char fileText[INITIAL_CAPACITY];

		if (fgets(fileText, sizeof(fileText), file) == NULL)
		{
			break;
		}

		size_t fileTextLen = strlen(fileText);
		size_t bufferCapacityNeeded = fileTextLen + bufferLength + 1;

		if (bufferCapacity < bufferCapacityNeeded)
		{
			if (bufferCapacity == 0)
			{
				bufferCapacity = INITIAL_CAPACITY;
			}
			else
			{
				bufferCapacity = bufferCapacity * 2;
			}
		}

		char* tempBuffer = (char*)realloc(buffer, bufferCapacity * sizeof(char));

		if (tempBuffer != NULL)
		{
			buffer = tempBuffer;
		}

		if (buffer == NULL)
		{
			printf(">>Memory allocation for buffer failed.\n");
			free(buffer);
			fclose(file);
			return 1;
		}

		strcpy_s(buffer + bufferLength, bufferCapacity - bufferLength, fileText);
		bufferLength += fileTextLen;
	}

	fclose(file);
	appendText(buffer);
	free(buffer);
	return 0;
}

int saveInfo(char *fileName)
{
	int answer;

	printf("*There will be a function to save the info to a file*\n");

	// TODO: Add a checking for the file existence

	FILE *file;

	errno_t err;		// chat gpt 

	if (file_exists(fileName))
	{
		printf("Do you want to overwrite the file: (1/0)\n");
		scanf_s("%d", &answer);

		if (answer == 1)
		{
			err = fopen_s(&file, fileName, "w");
		}
		else if (answer == 0)
		{
			err = fopen_s(&file, fileName, "a");
		}
		else 
		{
			printf("You can write only 1 or 0... Try again\n");
			return 0;
		}

	}
	else 
	{
		err = fopen_s(&file, fileName, "a");
	}

	if (err != 0)
	{
		printf(">>There is no file.\n");
		return 1;
	}

	if (userText[0] == '\0')
	{
		printf(">>Attention! You have no text to save into the file. It will be an empty file.\n");
	}

	fputs(userText, file);

	printf(">>Text has been saved successfully.\n");
	fclose(file);
	return 0;
}

void printInfo()
{
	printf("*There will be a function to print the info*\n");
	printf("Your text: \n%s\n", userText);
}

/*int insertInfo(char* word, int lineIndex, int charIndex)
{
	printf("*There will be a function to insert the text by line and symbol index*\n");

	length = strlen(userText);
	int substringLen = strlen(word);
	int neededLen = length + substringLen + 1;

	char* temp = (char*)malloc(neededLen * sizeof(char));

	if (temp == NULL)
	{
		printf("Memory allocation failed\n");
		return 1;
	}


	

	return 0;
}*/

int search(char *word)
{
	printf("*There will be a function to search*\n");

	char* currentPosition = userText;
	int lineIndex = 0; 
	int counter = 0;

	

	while ((currentPosition = strstr(currentPosition, word)) != NULL)
	{
		counter++;

		lineIndex = 0;

		for (char* i = userText; i < currentPosition; i++)
		{
			if (*i == '\n')
			{
				lineIndex++;
			}
		}

		int wordIndex = currentPosition - userText;

		printf(" Text is present in this position: %d %d\n", lineIndex, wordIndex);

		currentPosition = currentPosition + strlen(word);
	}

	if (counter == 0)
	{
		printf("No such substring.\n");
	}

	return 0;
}

void cleanConsole()
{
	printf("*There will be a function to clean the console*\n");
	system("cls");
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

int commandParser(char *cmd)
{
	int userCommand = atoi(cmd);

	switch (userCommand)
	{
	case 1:

		printf(">>Executing command 1\n\n");
		printf(">>Enter text to append: ");

		toEnterText();
		break;					   
	case 2:						   
		printf(">>Executing command 2\n\n");
		newLine();				   
		break;					   
	case 3:
		char fileName[INITIAL_CAPACITY];
		printf("Executing command 3\n\n");
		printf("Enter the file name for loading: \n");
		fgets(fileName, sizeof(fileName), stdin);

		if (fileName[strlen(fileName) - 1] == '\n')
		{
			fileName[strlen(fileName) - 1] = '\0';
		}
		
		loadFile(fileName);				   
		break;					   
	case 4:
		char loadFile[INITIAL_CAPACITY];
		printf("Executing command 4\n\n");
		printf("Enter the file name for saving: \n");
		fgets(loadFile, sizeof(loadFile), stdin);

		if (loadFile[strlen(loadFile) - 1] == '\n')
		{
			loadFile[strlen(loadFile) - 1] = '\0';
		}

		saveInfo(loadFile);
		break;
	case 5:
		printf("Executing command 5\n\n");
		printInfo();
		break;
	case 6:
		int lineIndex;
		int wordIndex;
		printf("Executing command 6\n\n");
		printf("Choose line and index: \n");



		//insertInfo();
		break;
	case 7:
		char searchWord[INITIAL_CAPACITY];

		printf("Executing command 7\n\n");
		printf("Enter text to search: \n");
		fgets(searchWord, INITIAL_CAPACITY, stdin);

		if (searchWord[strlen(searchWord) - 1] == '\n')
		{
			searchWord[strlen(searchWord) - 1] = '\0';
		}

		search(searchWord);
		break;
	case 8:
		printf("Executing command 8\n\n");
		cleanConsole();
		break;
	default:
		printf("The command is not implemented. Type '--help' for available commands.\n\n");
		break;
	}

	return 0;
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