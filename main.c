#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
typedef unsigned long long ull; // all ints are unsigned long long ints so that it can compute numbers at the maximum value possible with a c program. at least till i learn how to do bigger nums

ull rows = 1;

void split_lines(const char *str, char **lines, int num_rows) {
    int line_index = 0;
    int line_start = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            int line_length = i - line_start;
            lines[line_index] = (char *)malloc((line_length + 1) * sizeof(char));
            strncpy(lines[line_index], &str[line_start], line_length);
            lines[line_index][line_length] = '\0';
            line_index++;
            line_start = i + 1;
        }
    }

    // Handle the last line (without a newline character).
    int line_length = strlen(&str[line_start]);
    lines[line_index] = (char *)malloc((line_length + 1) * sizeof(char));
    strcpy(lines[line_index], &str[line_start]);
}

// counts the line in the string created containing the contents of primeNums.txt
ull countLines(char *string) {
	ull lines = 1, i = 0;
	while (string[i] != '\0') {
		if (string[i] == '\n') {
			lines++;
		}
		i++;
	}
	return lines;
}

char * rFile() { //read the file and returns the contents as a string
	char * buffer;
	ull length;
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

void aFile(char* pNum) { // appends the prime number to the file primeNums.txt
	char*pNumStr;
	ull size = strlen(pNum);
	pNumStr = (char *)malloc(size + 1);
  pNumStr = pNum;

	if (pNumStr != NULL) {
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
	ull tLen = strlen(buf);
	ull lastLineStart = tLen - 2;

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

void free_lines(char **lines, int num_rows) {
    for (int i = 0; i < num_rows; i++) {
        free(lines[i]);
    }
    free(lines);
}

bool primeCheck(ull inputNum) {
	char * primeString = rFile();
  ull num_rows = countLines(primeString);
  char **lines = (char **)malloc(num_rows * sizeof(char *));
  split_lines(primeString, lines, num_rows);
	if (inputNum == 2) return true;
  ull halfInputNum;
  if (inputNum%2==0) halfInputNum=inputNum/2;
  else halfInputNum=(inputNum+1)/2;
  ull x = 0;
	for (ull z = 0; x<halfInputNum; z++) {
    x = strtol(lines[z],NULL,10);
		if (inputNum%x == 0) {  
      /*// need to figure out how to divide each number by the numbers contained in primeNums.txt
		  // currently checking the num against every num between 2 and inputNum. it works but its not very efficient
		  // all non prime numbers are divisible by a prime number. otherwise they wouldn't be prime. 77 is divisble by 11 and 7 so its not prime. 11 and 7 are prime numbers tho. 
		  //any number that can be evenly divided by another number (excluding 1 and itself) is prime. 11 is prime, so is 13, but 15 can be divided by the prime number 5 and 3 so its not prime. 
		  //if its divisible by 7 then it doesnt really matter if its divisble by 14. 
		  // in conclusion All non prime numbers are divisible by at least 2 non-prime numbers. (ifi its divisble by one it has to be divisble )*/
			return false;
			break;
		}
	}
  free_lines(lines, num_rows);
  return true;
}

int main(void) {
	char * primeString = rFile();
	char*arrStr = lastL(primeString); // arrStr is null. heres the problem. fix this. prob need to malloc out mem for it
	char*sknlg; // string to hold part anything not a num from lastline
	//think something is wrong with twodarrayStr() <--- this. if arrStr is null means that twodarrayStr is failing or returning null
	ull lastLine = 2; // makes it work when file is empty. currently starts at 2 and increments up. while arrStr is null tho it wont be super efficient. only able to generate starting at 2. not starting at the last line in the file.
	if (arrStr) {
		lastLine = strtol(arrStr, &sknlg, 10);
		printf("lastLine = %llu\n", lastLine);
	}
	ull num = lastLine;
	ull z = 0;
	while (z <= 1000) {
		bool prime = primeCheck(num);
		if (prime == true && num!=lastLine) {
      ull n = num;
      ull size = 0;
      do {
        n /= 10;
        ++size;
      } while (n != 0);
      char*snum;
	    snum = (char *)malloc(size + 1);
      sprintf(snum, "%llu", num);
			aFile(snum);
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