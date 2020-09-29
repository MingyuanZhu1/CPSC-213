#include <stdio.h>
#include "int_element.h"
#include "str_element.h"
#include "element.h"
//ct
/* If the string is numeric, return an int_element. Otherwise return a str_element. */
struct element *parse_string(char *str) {
  char *endp;
  /* strtol returns a pointer to the first non-numeric character in endp.
     If it gets to the end of the string, that character will be the null terminator. */
  int value = strtol(str, &endp, 10);
  if(str[0] != '\0' && endp[0] == '\0') {
    /* String was non-empty and strtol conversion succeeded - integer */
    return (struct element *)int_element_new(value);
  } else {
    return (struct element *)str_element_new(str);
  }
}
//implement compare for all
int compare_both(void *first, void *second) {
  struct element *f = *(struct element **)first;
  struct element *s = *(struct element **)second;
  int* val = f->class->compare(f,s);
  return val;
}

int main(int argc, char **argv) {
  /* TODO: Read elements into a new array using parse_string */
  // int temp = argc - 1;
  struct element **a = malloc((argc - 1) * sizeof(struct element*));
  int i = 0;
  while(i<(argc - 1)) {
    a[i] = parse_string(argv[i+1]);
    i++;
  }
  /* TODO: Sort elements with qsort */
  /* TODO: Print elements, separated by a space */
  qsort(a, (argc - 1), sizeof(struct element*), compare_both);

  printf("Sorted:");
  int j = 0;
  while(j<(argc - 1)) {
    printf(" ");
    a[j]->class->print(a[j]);
    j++;
  }
  
  printf("\n");
  int k = 0;
  while(k<(argc - 1)){
    rc_free_ref(a[k]);
    k++;
  }
  free(a);
}

