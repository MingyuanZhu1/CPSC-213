#include "str_element.h"
#include <stdio.h>
#include <string.h>
#include "refcount.h"
#include "element.h"
//ct
struct str_element {
  struct element_class *class;
  char *content;
};

char *str_element_get_value(struct str_element *element) {
  return element->content;
}

static void print(struct element *element) {
  struct str_element *se = element;
  printf("%s", se->content);
}

static int str_compare(struct str_element *first, struct str_element *second) {
    struct str_element *is_str_a = is_str_element(first);
    struct str_element *is_str_b = is_str_element(second);
    if(is_str_a && is_str_b) {
        // The strcmp() function takes two strings and returns an integer. 
        // The strcmp() compares two strings character by character.
        int compare = strcmp(first->content,second->content);
        return compare;
    } else {
        return 1;
    }
}
static struct element_class str_helper = { print, str_compare };

static void free_ref_helper(void *p) {
  struct str_element *se = p;
  rc_free_ref(se->content);
}

struct str_element *str_element_new(char* value){
    //create new elements
    struct str_element *e = rc_malloc(sizeof(struct str_element), free_ref_helper);
    e->class = &str_helper;
    //since str length needs 1 space for null at the end
    e->content = rc_malloc((strlen(value)+1), NULL);
    memcpy(e->content, value, strlen(value)+1);
   
    return e;
}

int is_str_element(struct element *e) {
  return e->class == &str_helper;
}





