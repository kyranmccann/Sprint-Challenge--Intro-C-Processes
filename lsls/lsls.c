#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>

int print_out(char *directory, int levels) {
  struct dirent *dir;
  struct stat buffer;
  //arbitrary reasonably-sized buffer
  char path[4096];

  // Open directory
  DIR *d = opendir(directory);
  if (d == NULL)
  {
    fprintf(stderr, "Whoops\n");
    exit(1);
  }

  // Repeatedly read and print entries
  while((dir = readdir(d)) != NULL)
  {
    snprintf(path,sizeof(path), "%s/%s", directory, dir->d_name);

    if(stat(path, &buffer) < 0)
    {
      fprintf(stderr, "something wrong in stat");
      exit(1);
    }
    else
    {
      if(buffer.st_mode&S_IFDIR)
      {
        if(levels > 1)
        {
          printf("<DIR> %s\n", dir->d_name);
          print_out(path, levels-1);
        }
        else
        {
          printf("       <DIR> %s\n", dir->d_name);
        }
      }
      else
      {
        if (levels > 1)
        {
          printf("%ld %s\n", buffer.st_size, dir->d_name);
        }
        else
        {
          printf("       %ld %s\n", buffer.st_size, dir->d_name);
        }
      }
    }
  }

  // Close directory
  closedir(d);
  return 0;
}

/**
 * Main
 */
int main(int argc, char **argv)
{
  char *directory;

  // Parse command line
  if (argc == 2)
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

  print_out(directory, 2);
}
