#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int * random_gen(int * arr) {
  int rand_file = open("/dev/random", O_RDONLY);
  printf("Generating random numbers:\n");
  int i;
  for(i = 0; i < 10; i++) {
    read(rand_file, &arr[i], sizeof(int));
  }
  close(rand_file);
  return arr;
}

int main() {
  int * a = malloc(10 * sizeof(int));
  random_gen(a);
  int i;
  for(i = 0; i < 10; i++) {
    printf("random %d: %d\n", i, a[i]);
  }

  printf("Writing numbers to file...\n");
  int file = open("text.txt", O_WRONLY);
  printf("Bytes written: %zd\n", write(file, a, 10 * sizeof(int)));
  close(file);

  printf("Reading numbers from file...\n");
  file = open("text.txt", O_RDONLY);
  int * a2 = malloc(10 * sizeof(int));
  read(file, a2, 10 * sizeof(int));
  close(file);

  printf("Verification that written values were the same:\n");
  for(i = 0; i < 10; i++) {
    printf("random %d: %d\n", i, a2[i]);
  }

  free(a);
  free(a2);
  return 0;
}
