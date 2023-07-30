// why is there a buffer overflow. there shouldnt be one. im nulling out and freeing all my pointers. gah
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int rows = 1;

// counts the line in the string created containing the contents of primeNums.txt
int countLines(char *string) {
	int lines = 1, i = 0;
	while (string[i] != '\0') {
		if (string[i] == '\n') {
			lines++;
		}
		i++;
	}
	return lines;
}

bool primeCheck(int inputNum) {
	int np = 0; // if anything but 0 then num is not prime. if 0 then prime
	if (inputNum == 2) return true;
	for (int x = 2; x < inputNum; x++) {
		if (inputNum%x != 0) {  // need to figure out how to divide each number by the numbers contained in primeNums.txt
		  // currently checking the num against every num between 2 and inputNum. it works but its not very efficient
		  // all non prime numbers are divisible by a prime number. otherwise they wouldn't be prime. 77 is divisble by 11 and 7 so its not prime. 11 and 7 are prime numbers tho. 
		  //any number that can be evenly divided by another number (excluding 1 and itself) is prime. 11 is prime, so is 13, but 15 can be divided by the prime number 5 and 3 so its not prime. 
		  //if its divisible by 7 then it doesnt really matter if its divisble by 14. 
		  // in conclusion All non prime numbers are divisible by at least 2 non-prime numbers. (ifi its divisble by one it has to be divisble )
			if (inputNum == x + 1 && np == 0) {
				return true;
			}
		}
		else if (inputNum%x == 0) {
			return false;
			np++; // probably unnecessary. leaving in for now as way to check wether its working and as a backup to make sure doesnt spit out prime in the end bc input num == x + 1
			break;
		}
	}
	//return false
}

char * rFile() { //read the file and returns the contents as a string
	char * buffer;
	long length;
	FILE * f = fopen("primeNums.txt", "rb");

	if (f) {
		fseek(f, 0, SEEK_END);
		length = ftell(f);
		fseek(f, 0, SEEK_SET);
		buffer = (char*)malloc(length + 1);
		if (buffer) {
			fread(buffer, 1, length, f);
			buffer[length] = '\0';
		}
		fclose(f);
		strcat(buffer, "\0");
		return buffer;
	}
}

void aFile(int pNum) { // appends the prime number to the file primeNums.txt
	char*pNumStr;
	int size = snprintf(NULL, 0, "%d\n", pNum);
	pNumStr = (char *)malloc(size + 1);

	if (pNumStr != NULL) {
		sprintf(pNumStr, "%d", pNum);
		FILE *f = fopen("primeNums.txt", "a+");
		if (f != NULL) {
			fprintf(f, "%s\n", pNumStr);
			fclose(f);
		}
		else {
			printf("Error opening the file.\n");
		}
		if (pNumStr) {
			free(pNumStr);
			pNumStr = NULL;
		}
	}
	else {
		printf("Memory allocation failed.\n");
	}
}

char* lastL(char* buf) {
	int tLen = strlen(buf);
	int lastLineStart = tLen - 2;

	// Move the lastLineStart back until we find the start of the last line.
	while (lastLineStart > 0 && buf[lastLineStart] != '\n') {
		lastLineStart--;
	}

	// Allocate memory for the last line and copy it.
	char* lastLine = (char*)malloc(tLen - lastLineStart);
	if (lastLine != NULL) {
		strcpy(lastLine, &buf[lastLineStart + 1]); // Skip the '\n' character and copy the last line.
	}
	return lastLine;
}

int main(void) {
	char * primeString = rFile();
	char*arrStr = lastL(primeString); // arrStr is null. heres the problem. fix this. prob need to malloc out mem for it
	char*sknlg; // string to hold part anything not a num from lastline
	//think something is wrong with twodarrayStr() <--- this. if arrStr is null means that twodarrayStr is failing or returning null
	int lastLine = 2; // makes it work when file is empty. currently starts at 2 and increments up. while arrStr is null tho it wont be super efficient. only able to generate starting at 2. not starting at the last line in the file.
	if (arrStr) { // arrStr is null so it will never let lastline equal the actual last line
		lastLine = strtol(arrStr, &sknlg, 10); // for some reason lastLine is always 50. cant figure out why
		printf("lastLine = %i\n", lastLine);
	}
	int num = lastLine; // num always starts at 0. probly not actually returning last line(or returning an empty field as is the last line)
	int z = 0;
	while (z <= 10001) {
		bool prime = primeCheck(num);
		if (prime == true&&num!=lastLine) {
			aFile(num);
		}
		num++;
		z++;
	}
	if (primeString) {
		free(primeString);
		primeString = NULL;
	}
	free(arrStr);
	return 0;
}
