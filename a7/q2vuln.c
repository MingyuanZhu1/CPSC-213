#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

struct str {
	int length;
	char *string; 
};

struct str str1 = {30, "Welcome! Please enter a name\n:"};
struct str str2 = {11, "Good luck, \n"};
struct str str3 = {43, "The secret phrase is \"squeamish ossifrage\"\n"};

void main() {
    char buffer[128];
    print(&str1);
    int x = 256;
    int size = read(0, buffer, x);
    print(&str2);
    write(1, buffer, size);

}

void print(struct str* s) {
     write(1, s->string, s->length);
}

void proof() {
    print(&str3);
}