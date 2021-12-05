Team members:  David Shawver, Jason Bachman, and Matt Caterino

How to run program:

All project files should be placed in the same folder and the following command should be run using a machine with the 
g++ compiler.  g++ ClosureMap.cpp main.cpp -o prog

The program can be run with 0, 1, or 2 command line arguments.

         1.  Zero command line arguments -- user will enter all data and output will be printed to terminal. 
            ./prog
         2.  One command line argument -- user enters the path to the input file and output will be printed to terminal. 
            ./prog {input file path}

         3.  Three command line arguments -- user enters input filename and output filepath and output will be printed \n;
         both the terminal and to the file path that is entered.
            ./prog {input file path} {output file path}
            e.g.  "./prog ./example.txt ./outfile.txt"  would run the example input file that we have provided and output 
            the candidate keys to outfile.txt in the current folder location

For reading from file, the program takes text files from a specific format.  If this format is not followed, it will not read 
the data properly.  On the first line there are two integers, with one space in between each other.  

 {number of attributes in the relation 'R'} {total number of functional dependencies provided}

 The next line will have the list of attributes for relation R for which the candidate key is being determined.  
 Each attribute must be separated by a space.

 The last set of lines are for the functional depdenencies.  Attributes on the LHS and the RHS must be separated by a space.
 There must be an arrow -> separating the LHS from the RHS.  There must be a space before and after the arrow.