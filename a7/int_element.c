#include "int_element.h"
#include <stdio.h>
#include "refcount.h"
#include "element.h"
//ct
struct int_element {
  struct element_class *class;
  int val;
  int count;
};

int int_element_get_value(struct int_element *element) {
  return element->val;
}

static void print(struct element *e) {
  struct int_element *ee = e;
  printf("%d", ee->val);
}

static int int_compare(struct int_element *first, struct int_element *second) {
    struct int_element *is_int_a = is_int_element(first);
    struct int_element *is_int_b = is_int_element(second);
    if(is_int_a && is_int_b) {
        if((first->val)<(second->val)) {
            return -1;
        }
        if(second->val == first->val) {
            return 0;
        }
        else{
            return 1;
        }
    } else {
        return -1;
    }
}

static struct element_class int_helper = { print, int_compare};

struct int_element *int_element_new(int value){
    //create new elements
    struct int_element *e = rc_malloc(sizeof(struct int_element), NULL);
    e->val = value;
    e->class = &int_helper;
    return e;
}

int is_int_element(struct element *element){
    return element->class == &int_helper;
}

