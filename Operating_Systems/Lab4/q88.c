#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	char src[256];
	strcpy(src, "/home/student/Desktop/160905320/Lab4/q1.c");
	src[strlen(src)-1] = '\0';

	int src_fd = open(src, O_RDONLY);
	if(src_fd < 0) {
		printf("Error opening source file!\n");
		return 1;
	}

	int bytes_read;
	char c;
	int words = 0, chars = 0, lines = 0;
	while((bytes_read = read(src_fd, &c, sizeof(char))) != 0) {
		++chars;
		if(c == '\n') {
			++lines;
			++words;
		} else if(c == ' ') {
			++words;
		}
	}

	printf("Characters : %d\n", chars);
	printf("Words : %d\n", words);
	printf("Lines : %d\n", lines);

	close(src_fd);
}
	
