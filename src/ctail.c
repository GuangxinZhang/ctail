/*
 ============================================================================
 Name        : ctail.c
 Author      : guangxinzhang@outlook.com
 Version     : 0.1
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

#define FILE_LINE_LEN 1024

long offset = 0;

int32_t c_tail(const char *file);
long file_length(char *file);

long file_length(char *file) {
	long len;
	FILE *fp = fopen(file, "r");
	if (!fp) {
		printf("cant open file, file: %s\n", file);
		return -2;
	}
	fseek(fp, 0, SEEK_SET);
	fseek(fp, 0, SEEK_END);
	len = ftell(fp);
	fclose(fp);
	return len;
}

int32_t c_tail(const char *file) {
	if (!file)
		return -1;
	FILE *fp = fopen(file, "r");
	if (!fp) {
		printf("cant open file, file: %s\n", file);
		return -2;
	}

	fseek(fp, offset, SEEK_SET);
	printf("len: %ld\n", offset);
	char text[FILE_LINE_LEN];

	uint32_t len;
	while (!feof(fp)) {
		memset(text, 0x0, FILE_LINE_LEN);
		fgets(text, FILE_LINE_LEN, fp);
		len = strlen(text);
		if (len == 0 || text[len - 1] != '\n')
			continue;
		text[len - 1] = 0;
		offset += len;
		printf("%s\n", text);
	}

	fclose(fp);

	return 0;
}
int main(int argc, char *argv[]) {
	char *file;
	int position = -1;
	if (argc == 2) {
		file = argv[1];
	} else if (argc == 3) {
		file = argv[1];
		position = atoi(argv[2]);
	} else {
		printf("Usage: exe file_name\n");
		exit(-1);
	}
	if (position == 0) {
		offset = 0;
	} else if (position == -1) {
		offset = file_length(file);
	}

	while (1) {
		// 如果读取长度超过文件长度，则重置offset为当前文本新的长度
		if (offset > file_length(file)) {
			offset = file_length(file);
		}
		c_tail(argv[1]);
		sleep(1);
	}
	return 0;
}
