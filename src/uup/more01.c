//
// Created by 孟伸 on 2021/12/11.
//
#include <stdio.h>
#include <stdlib.h>
#define PAGELEN 24
#define LINELEN 512

void do_more(FILE *);

int main(int args, char *argc[]) {
	FILE *fp;
	if (args == 1) {
		do_more(fp);
	} else {
		while (--args) {
			if ((fp = fopen(*++argc, "r")) != NULL) {
				do_more(fp);
				fclose(fp);
			} else {
				exit(1);
			}
		}
	}
	return 0;
}

void do_more(FILE *fp) {
	char line[LINELEN];
	int num_of_line = 0;
	int see_more(), replay;
	while (fgets(line, LINELEN, fp)) {
		if (num_of_line == PAGELEN) {
			replay = see_more();
			if (replay == 0) break;
			num_of_line -= replay;
		}

		if (fputs(line, stdout) == EOF) exit(1);
		num_of_line++;
	}
}

int see_more() {
	int c;
	printf("\033[7m more? \033[0m");
	while ((c = getchar()) != EOF) {
		if (c == 'q') return 0;
		if (c == ' ') return PAGELEN;
		if (c == '\n') return 1;
	}
	return 0;
}