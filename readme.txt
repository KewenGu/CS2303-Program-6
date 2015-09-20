Programmer: Kewen Gu
Username: kgu
Doxygen Documentation URL: http://users.wpi.edu/~kgu/cs2303assig6/
-------------------------------------------------------------------------------
Description:
This assignment consists of two main programs. The first program, cptest, can copy one file to another file under a different name (renaming the file). or can copy a file to another directory with the same name. There are three copying methods. User can customize which copy method to use. User can also customize the buffer size for the third copying method. The second program, cptest2, can do the exactly same thing as cptest. However, It's able to set the copying method and buffer size with the command-line options. In addition, it's also able to copy multiple files into another directory.

-------------------------------------------------------------------------------
Instruction:
"make": complies all the files.

"./cptest infile outfile": runs the program cptest. Copys infile to outfile, where outfile can be either a file name or a directory name. The input order matters.

"./cptest infile outfile copy_method": runs the program cptest. Copys infile to outfile using the specified copy method, where outfile can be either a file name or a directory name. The input order matters.

"./cptest infile outfile copy_method buffer_size": runs the program cptest. Copys infile to outfile using the specified copy method, where outfile can be either a file name or a directory name. If the using the third copy method, using the specified buffer size. The input order matters.

"./cptest2 infile outfile command_line_option1 command1 command_line_option2 command2": runs the program cptest2. Copys infile to outfile, where outfile can be either a file name or a directory name. Can use "-c" and "-b" command-line options to specify the copy method and buffer size respectively. The order of infile+outfile block, command_line_option1+command1 block and command_line_option2+command2 block can be arbitrary.

"./cptest2 infile1 infile2 infile3 infile4 infile5 ...(all infiles) outfile_directory": runs the program cptest2. Copys all the infiles to the outfile directory. The rightmost input should be the outfile directory, and all the inputs before the rightmost are the infile names. The input order matters.

"make clean": clean all the .o files and executable files.

"make docs": generate the Doxygen documentation, can be viewed via URL: http://users.wpi.edu/~kgu/cs2303assig6/.

-------------------------------------------------------------------------------
Discussion:
Comparing the three copy methods, if using the right buffer size (8000 to 1200 at optimum), the third copy method is the fastest. However, the second copy method is the slowest, which is equivalent to the third copy method using buffer size 1. The overall performance of three copy method is about 0.1sec for copyfile1, 18sec for copyfile2 and 0.04sec for copyfile3.
