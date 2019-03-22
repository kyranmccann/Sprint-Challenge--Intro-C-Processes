#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>


/**
 * Main
 */
int main(int argc, char **argv)
{
  char *directory;
  DIR *d;
  struct dirent *dir;
  struct stat buffer;

  // Parse command line
  if (argc > 1)
  {
    directory = argv[1];
  }
  else if (argc == 1)
  {
    directory = ".";
  }
  else
  {
    fprintf(stderr, "too many arguments");
    exit(1);
  }

  // Open directory
  d = opendir(directory);
  if (d == NULL)
  {
    fprintf(stderr, "What? I don't see that\n");
    exit(2);
  }

  // Repeatedly read and print entries
  while((dir = readdir(d)) != NULL)
  {
    char path[4096];

    snprintf(path, sizeof(path), "%s%s", directory, dir-> d_name);
    printf("%s\n", dir -> d_name);

    if(stat(path, &buffer) < 0)
    {
      fprintf(stderr, "something wrong in stat");
      exit(3);
    };

    printf("%s\n", dir -> d_name);
    printf("%ld %s\n", buffer.st_size, dir -> d_name);
  }

  // Close directory
  closedir(d);
  return 0;
}
