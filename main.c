#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int random_gen() {
  int rand_file = open("/dev/random", O_RDONLY);
  int i;
  int random_int = read(rand_file, &i, sizeof(int));
  close(rand_file);
  return i;
}

int main() {
  int a[10];
  int i;
  printf("Generating random numbers:\n");
  for(i = 0; i < 10; i++) {
    a[i] = random_gen();
    printf("random %d: %d\n", i, a[i]);
  }

  printf("Writing numbers to file...\n");
  int file = open("text.txt", O_WRONLY);
  printf("Bytes written: %zd\n", write(file, a, 10 * sizeof(int)));
  close(file);

  printf("Reading numbers from file...\n");
  file = open("text.txt", O_RDONLY);
  int a2[10];
  read(file, a2, 10 * sizeof(int));
  close(file);

  printf("Verification that written values were the same:\n");
  for(i = 0; i < 10; i++) {
    printf("random %d: %d\n", i, a2[i]);
  }

  return 0;
}
