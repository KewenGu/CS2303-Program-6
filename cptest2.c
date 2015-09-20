#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/time.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <libgen.h>

// function prototype
struct timeval find_time(struct timeval time1, struct timeval time2);

int copyfile1(char* infilename, char* outfilename);
int copyfile2(char* infilename, char* outfilename);
int copyfile3(char* infilename, char* outfilename, long nbytes);

char* find_path_name(char* sourcename, char* destname);
/** cptest.cpp
 * A file copying program.
 * Derived partially from caesar.cpp by Horstmann and Budd from big C++
 */

/**
   Prints usage instructions.
   @param program_name the name of this program
*/
void usage(char* program_name)
{ 
  printf("Usage: %s infile outfile \nor\nUsage: %s infile outfile outfile \nor\nUsage: %s infile outfile outfile buffer-size\n", program_name, program_name, program_name);
}

/**
   Prints file opening error message
   @param filename the name of the file that could not be opened
*/
void open_file_error(char* filename)
{  
  printf("Error opening file %s\n", filename);
}

/** Main program: copies a file.
    @param argc Number of command-line arguments (including program name).
    @param argv Array of pointers to character arays holding arguments.
    @return 0 if successful, 1 if fail.
*/
int main(int argc, char* argv[])
{ 
  int returnstatus;

  struct timeval time_before;
  struct timeval time_after; 

  int i = 0;
  int j = 0;

  while ((i < argc) && (strcmp(argv[i], "-c") != 0)) {
    i++;
  }

  while ((j < argc) && (strcmp(argv[j], "-b") != 0)) {
    j++;
  }

  int flag;
  struct stat status;
  char* path_name;

  // Call the stat() function to fill in the struct
  flag = stat(argv[argc - 1], &status);

  if ((argc > 3) && (flag == 0) && (S_ISDIR(status.st_mode) == 1) && (i == argc) && (j == argc)) {
    char* infilenames[argc - 2];
    char* outfilename = argv[argc - 1];

    int k;
    for (k = 0; k < (argc - 2); k++) {
      infilenames[k] = argv[k + 1];
    }

    gettimeofday(&time_before, NULL);

    // Perform the copying
    for (k = 0; k < (argc - 2); k++) {
      returnstatus = copyfile3(infilenames[k], outfilename, 9600);
    }
    
    gettimeofday(&time_after, NULL);
  }

  else if (argc != 3 && argc != 4 && argc != 5 && argc != 7) {
    usage(argv[0]); // Must have exactly 2 arguments.
    return 1;
  }

  else if (argc == 3) {
    char* infilename; // Names of files.
    char* outfilename;

    infilename = argv[1];
    outfilename = argv[2];

    gettimeofday(&time_before, NULL);

    // Perform the copying
    returnstatus = copyfile1(infilename, outfilename);
    //returnstatus = copyfile2(infilename, outfilename);
    //returnstatus = copyfile3(infilename, outfilename, 9600);
    gettimeofday(&time_after, NULL);
  }

  else if (argc == 4) {
    char* infilename; // Names of files.
    char* outfilename;
    infilename = argv[1];
    outfilename = argv[2];

    if (i == argc && j == argc) {
      int c = atoi(argv[argc - 1]);

      if (c != 1 && c != 2 && c != 3) {
        printf("Please enter a valid copying method, choose among 1, 2 and 3!\n");
        return 1;
      }

      printf("Copying Method: copyfile%d\n", c);

      gettimeofday(&time_before, NULL);

      // Perform the copying
      if (c == 1) {
        returnstatus = copyfile1(infilename, outfilename);
      }
      else if (c == 2) {
        returnstatus = copyfile2(infilename, outfilename);
      }
      else if (c == 3) {
        returnstatus = copyfile3(infilename, outfilename, 9600);
      }

      gettimeofday(&time_after, NULL);
    }

    else {
      printf("Please follow the input order: ./cptest2 infile outfile copying_method.\n");
      return 1;
    }
  }

  else if (argc == 5) {
    char* infilename; // Names of files.
    char* outfilename;
    int buffersize;
    if (i != argc && j == argc) {
      int c = atoi(argv[i + 1]);
      if (c != 1 && c != 2 && c != 3) {
        printf("Please enter a valid copying method, choose among 1, 2 and 3!\n");
        return 1;
      }
      printf("Copying Method: copyfile%d\n", c);
      int x;
      for (x = i; x < (argc - 2); x++) {
        argv[x] = argv[x + 2];
      }

      infilename = argv[1];
      outfilename = argv[2];

      gettimeofday(&time_before, NULL);

      // Perform the copying
      if (c == 1) {
        returnstatus = copyfile1(infilename, outfilename);
      }
      else if (c == 2) {
        returnstatus = copyfile2(infilename, outfilename);
      }
      else if (c == 3) {
        returnstatus = copyfile3(infilename, outfilename, buffersize);
      }
      else {
        printf("ERROR: Wrong Number for Copying Method, Choose among 1, 2 and 3!\n");
        return 1;
      }

      gettimeofday(&time_after, NULL);
    }

    else if (i == argc && j != argc) {
      buffersize = atoi(argv[j+1]);
      if (buffersize <= 0) {
        printf("Please enter a valid buffer size!\n");
        return 1;
      }

      printf("Buffer Size: %d\n", buffersize);
      int y;
      for (y = j; y < (argc - 2); y++) {
        argv[y] = argv[y + 2];
      }

      infilename = argv[1];
      outfilename = argv[2];

      gettimeofday(&time_before, NULL);

      // Perform the copying
      //returnstatus = copyfile1(infilename, outfilename1);
      //returnstatus = copyfile2(infilename, outfilename1);
      returnstatus = copyfile3(infilename, outfilename, buffersize);

      gettimeofday(&time_after, NULL);
    }

    else {
      char* infilename; // Names of files.
      char* outfilename;
      infilename = argv[1];
      outfilename = argv[2];

      int c = atoi(argv[argc-2]);
      if (c != 1 && c != 2 && c != 3) {
        printf("Please enter a valid copying method, choose among 1, 2 and 3!\n");
        return 1;
      }
      printf("Copying Method: copyfile%d\n", c);

      int buffersize = atoi(argv[argc-1]);
      if (buffersize <= 0) {
        printf("Please enter a valid buffer size!\n");
        return 1;
      }
      printf("Buffer Size: %d\n", buffersize);

      gettimeofday(&time_before, NULL);

      // Perform the copying
      if (c == 1) {
        returnstatus = copyfile1(infilename, outfilename);
      }
      else if (c == 2) {
        returnstatus = copyfile2(infilename, outfilename);
      }
      else if (c == 3) {
        returnstatus = copyfile3(infilename, outfilename, buffersize);
      }

      gettimeofday(&time_after, NULL);
    }
  }

  else if (argc == 7) {
    char* infilename; // Names of files.
    char* outfilename;
    int buffersize;

    if (i != argc && j != argc) {
      int c = atoi(argv[i + 1]);
      if (c != 1 && c != 2 && c != 3) {
        printf("Please enter a valid copying method, choose among 1, 2 and 3!\n");
        return 1;
      }
      printf("Copying Method: copyfile%d\n", c);

      int x;
      for (x = i; x < (argc - 2); x++) {
        argv[x] = argv[x + 2];
      }

      buffersize = atoi(argv[j + 1]);
      if (buffersize <= 0) {
        printf("Please enter a valid buffer size!\n");
        return 1;
      }

      printf("Buffer Size: %d\n", buffersize);
      
      int y;
      for (y = j; y < (argc - 2); y++) {
        argv[y] = argv[y + 2];
      }

      infilename = argv[1];
      outfilename = argv[2];

      gettimeofday(&time_before, NULL);

      // Perform the copying
      if (c == 1) {
        returnstatus = copyfile1(infilename, outfilename);
      }
      else if (c == 2) {
        returnstatus = copyfile2(infilename, outfilename);
      }
      else if (c == 3) {
        returnstatus = copyfile3(infilename, outfilename, buffersize);
      }

      gettimeofday(&time_after, NULL);
    }
    
    else {
      printf("Please input copying method index (1, 2 or 3) after -c, and buffer size after -b.\n");
      return 1;
    }
  }

  struct timeval result = find_time(time_before, time_after);
  double start_time = time_before.tv_sec + ((double)time_before.tv_usec/(double)1000000);
  double end_time = time_after.tv_sec + ((double)time_after.tv_usec/(double)1000000);
  double result_time = result.tv_sec + ((double)result.tv_usec/(double)1000000);

  printf("Start time: %10.6f sec, End time: %10.6f sec\n", start_time, end_time);
  printf("The time used is %.6f sec\n", result_time);
  return returnstatus;
}


/** Find the time difference
 * @param time1 Start time
 * @param time2 End time
 * @return The time differnce
 */
struct timeval find_time(struct timeval time1, struct timeval time2) {
  struct timeval result;
  if (time2.tv_usec < time1.tv_usec) {
    result.tv_sec = time2.tv_sec - time1.tv_sec - 1;
    result.tv_usec = (time2.tv_usec + 1000000) - time1.tv_usec;
  }
  else {
    result.tv_sec = time2.tv_sec - time1.tv_sec;
    result.tv_usec = time2.tv_usec - time1.tv_usec;
  }

  return result;
}

/** Copies one file to another using formatted I/O, one character at a time.
 @param infilename Name of input file
 @param outfilename Name of output file
 @return 0 if successful, 1 if error.
*/
int copyfile1(char* infilename, char* outfilename) {
  FILE* infile; //File handles for source and destination.
  FILE* outfile;
  int intch;  // Character read from input file. must be an int to catch EOF.
  unsigned char ch; // Character stripped down to a byte.
  char* file_path = find_path_name(infilename, outfilename);

  if (strcmp(file_path, outfilename) == 0) {
    infile = fopen(infilename, "r"); // Open the input and output files.
    if (infile == NULL) {
      open_file_error(infilename);
      return 1;
    }

    outfile = fopen(outfilename, "w");
    if (outfile == NULL) {
      open_file_error(outfilename);
      return 1;
    }


    // Read each character from the file, checking for EOF.
    while ((intch = fgetc(infile)) != EOF) {
      ch = (unsigned char) intch; // Convert to one-byte char.
      fputc(ch, outfile); // Write out.
    }
  }

  else {
    infile = fopen(infilename, "r"); // Open the input and output files.
    if (infile == NULL) {
      open_file_error(infilename);
      return 1;
    }

    DIR* current_dir = opendir(outfilename);
    if (current_dir == NULL) {
      perror("ERROR");
      return 1;
    }

    outfile = fopen(file_path, "w");
    if (outfile == NULL) {
      open_file_error(file_path);
      return 1;
    }


    // Read each character from the file, checking for EOF.
    while ((intch = fgetc(infile)) != EOF) {
      ch = (unsigned char) intch; // Convert to one-byte char.
      fputc(ch, outfile); // Write out.
    }

    closedir(current_dir);
  }

  // All done--close the files and return success code.
  fclose(infile);
  fclose(outfile);
  return 0; // Success!
}


/** Copies one file to another using formatted I/O, one character at a time.
 @param infilename Name of input file
 @param outfilename Name of output file
 @return 0 if successful, 1 if error.
*/
int copyfile2(char* infilename, char* outfilename) {
  int fd1, fd2;
  size_t count = sizeof(char);
  void* buf = malloc(sizeof(char) * count);
  char* file_path = find_path_name(infilename, outfilename);

  if (strcmp(file_path, outfilename) == 0) {
    fd1 = open(infilename, O_RDONLY);
    if (fd1 < 0) {
      open_file_error(infilename);
      return 1;
    }

    fd2 = open(outfilename, O_WRONLY | O_TRUNC | O_CREAT);
    if (fd2 < 0) {
      open_file_error(outfilename);
      return 1;
    }

    /* Now read it from the file */
    while(count == sizeof(char)) {
      count = read(fd1, buf, sizeof(char));
      write(fd2, buf, count);
    }
  }

  else {
    fd1 = open(infilename, O_RDONLY);
    if (fd1 < 0) {
      open_file_error(infilename);
      return 1;
    }

    DIR* current_dir = opendir(outfilename);
    if (current_dir == NULL) {
      perror("ERROR");
      return 1;
    }

    fd2 = open(file_path, O_TRUNC | O_CREAT | O_WRONLY);
    if (fd2 < 0) {
      open_file_error(file_path);
      return 1;
    }

    /* Now read it from the file */
    while(count != 0) {
      count = read(fd1, buf, count);
      write(fd2, buf, count);
    }

    closedir(current_dir);
  }

  free(buf);
  close(fd1);
  close(fd2);
  return 0;
}


/** Copies one file to another using formatted I/O, one character at a time.
 @param infilename Name of input file
 @param outfilename Name of output file
 @return 0 if successful, 1 if error.
*/
int copyfile3(char* infilename, char* outfilename, long nbytes) {
  int fd1, fd2;
  size_t count = nbytes;
  void* buf = malloc(sizeof(char) * count);
  char* file_path = find_path_name(infilename, outfilename);

  if (strcmp(file_path, outfilename) == 0) {
    fd1 = open(infilename, O_RDONLY);
    if (fd1 < 0) {
      open_file_error(infilename);
      return 1;
    }

    fd2 = open(outfilename, O_WRONLY | O_TRUNC | O_CREAT);
    if (fd2 < 0) {
      open_file_error(outfilename);
      return 1;
    }

    /* Now read it from the file */
    while(count != 0) {
      count = read(fd1, buf, count);
      write(fd2, buf, count);
    }
  }

  else {
    fd1 = open(infilename, O_RDONLY);
    if (fd1 < 0) {
      open_file_error(infilename);
      return 1;
    }

    DIR* current_dir = opendir(outfilename);
    if (current_dir == NULL) {
      perror("ERROR");
      return 1;
    }

    fd2 = open(file_path, O_TRUNC | O_CREAT | O_WRONLY);
    if (fd2 < 0) {
      open_file_error(file_path);
      return 1;
    }

    /* Now read it from the file */
    while(count != 0) {
      count = read(fd1, buf, count);
      write(fd2, buf, count);
    }

    closedir(current_dir);
  }

  free(buf);
  close(fd1);
  close(fd2);
  return 0;
}

/** Fixes desitination filename if it is specified as a directory.
 * @param sourcename Name of file to copy from
 * @param destname Name to copy to
 * @return File name to copy to, in a dynamically-allocated buffer.
 *        If destname does not already exist, or exists and is a file, then the return value of a copy of the destination.
 *        If the destname is an existing directory, the return value is the name to use when opening the output file for writing.
 *        It is formed by finding the basename of the source file and appending it to the destname (with a slash between them if destname does not already end in one).
 */
char* find_path_name(char* sourcename, char* destname) {
  int result;
  struct stat status;
  char* path_name;

  // Call the stat() function to fill in the struct
  result = stat(destname, &status);

  if (result < 0) {
    return destname;
  }

  if (S_ISREG(status.st_mode)) {
    return destname;
  }

  if (S_ISDIR(status.st_mode)) {
    int len_path_name;

    len_path_name = strlen(destname);
    len_path_name = len_path_name + strlen(basename(sourcename)) + 1;
    path_name = (char*) malloc(sizeof(char)*len_path_name);
    
    strcpy(path_name, destname);
    strcat(path_name, "/");
    strcat(path_name, basename(sourcename));

    return path_name;
  }
}

