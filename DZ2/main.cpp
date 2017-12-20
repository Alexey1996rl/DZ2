#include <iostream>
#include <sys\stat.h>
#include <string.h>
#include <time.h>
using namespace std;

int work_with_file(char *file_name, char *mode)
{
	struct stat buffer;
	FILE *file;
	file = fopen(file_name, "r+");
	if (file == NULL)
	{
		cout << "File not found!" << endl;
		return -1;
	}
	fstat(fileno(file), &buffer);
	cout << "sizeoffile:" << buffer.st_size << endl;
	char *b = (char*)malloc(buffer.st_size * sizeof(char));
	for (int i = 0; i < buffer.st_size; i++)
	{
		if (!strcmp(mode, "null"))
			sprintf(&b[i], "%d", 0);
		else if (!strcmp(mode, "rand"))
			sprintf(&b[i], "%d", rand() % 10);
	}
	fprintf(file, "%s", b);
	free(b);
	fclose(file);
	remove(file_name);
	return 0;
}

int main(int argc, char *argv[])
{
	srand(time(NULL));
	if (argc < 1)
	{
		cout << "Not enough arguments!" << endl;
		return -1;
	}
	for (int i = 0; i < atoi(argv[3]); i++) work_with_file(argv[1], argv[2]);
	return 0;
}
