#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "list.h"

void stringToInteger(element_t* out1, element_t in1) {
    int** out = (int**) out1;
    char* in = in1;
    char* end;
    *out = malloc(sizeof(int*));
    **out = strtol(in, &end, 10);
    if (*end) {
        **out = -1;
    }
}

void keepString(element_t* out1, element_t sii, element_t iii) {
    char** out = (char**) out1;
    char* si = (char*) sii;
    int* ii = (int*) iii;
    if(*ii<0) {
        *out = si;
    } else {
        *out = 0;
    }
}

int isNotNegative(element_t num) {
    int* i = (int*) num;
    return *i >= 0;
}

int isNotNull(element_t str) {
    return str != NULL;
}

void stringCutter(element_t* out1, element_t sii, element_t iii) {
    char** out = (char**) out1;
    char* si = (char*) sii;
    int* ii = (int*) iii;
    
    *out = strdup(si);
    
    if (strlen(*out) > *ii) {
        (*out)[*ii] = 0;
    }
}

void printString(element_t str) {
    char* s = (char*) str;
    if(s) {
          printf("%s\n", s);
    } else {
        printf("NULL");
    }
}

void toSingleArray(element_t* out1, element_t av, element_t bv) {
    char** out = (char**) out1;
    char* b = bv;
    *out = realloc(*out, strlen(*out) + strlen(b) + 2);
    if (strlen(*out)) {
        strcat(*out, " ");
    }
    strcat(*out, b);
}


void getlargestint(element_t* out1, element_t av, element_t bv) {
    int** out = (int**) out1;
    int* a = (int*) av;
    int* b = (int*) bv;
    if(*a > *b) {
        **out = *a;
    } else {
        **out = *b;
    }
}

void printInt(element_t numv) {
    int* num = (int*) numv;
    printf("%d\n", *num);
}

int main(int argc, char** argv) {
    // read from the command line.
    struct list* arg_list = list_create();
    for (int i = 1; i < argc; i++) {
        list_append(arg_list, argv[i]);
    }
    
    // create a list of number where -1 represent string
    struct list* i_num_list = list_create();
    list_map1(stringToInteger, i_num_list, arg_list);
    
    // create a list of string where null represent number
    struct list* i_str_list = list_create();
    list_map2(keepString, i_str_list, arg_list, i_num_list);
    
    // use isNotNegative to filter string away.
    // outcome: get a list containing only number
    struct list* filtered_num_list = list_create();
    list_filter(isNotNegative, filtered_num_list, i_num_list);
    
    // use isNotNegative to filter numbers away.
    // outcome: get a list containing only string    
    struct list* filtered_str_list = list_create();
    list_filter(isNotNull, filtered_str_list, i_str_list);
    
    //get a list containing the element with trimed length.
    struct list* truncated_list = list_create();
    list_map2(stringCutter, truncated_list, filtered_str_list, filtered_num_list);
    
    // print out truncated list
    list_foreach(printString, truncated_list);

    
    // concatenate truncated list into a single string.
    // free immidiate!!!
    char* s = malloc(1);
    s[0] = 0;
    list_foldl(toSingleArray, (element_t*) &s, truncated_list);
    printf("%s\n", s);
    free(s);
    
    // get the largest integer.
    int v = -1;
    int* vp = &v;
    list_foldl(getlargestint, (element_t*) &vp, filtered_num_list);
    printf("%d\n", v);


    // please no mem leak......
    list_foreach(free, truncated_list);
    list_foreach(free, i_num_list);
    list_destroy(arg_list);
    list_destroy(i_num_list);
    list_destroy(i_str_list);
    list_destroy(filtered_num_list);
    list_destroy(filtered_str_list);
    list_destroy(truncated_list);
}