# ls-for-windows
Lists the files in the current directory using the same formatting as the ls command from Unix operating systems.    
To make the output easier to read, the executable lists the filenames in a series of columns, with alphabetical order going down the columns.    
# How to use    
1. Use Visual Studio to build the main.cpp file into a .exe file named "ls.exe" or whatever you prefer.    
2. Add this executable to your PATH environment variable.    
3. Now, you can call the command using the name of the executable without the .exe extension.
# TODO    
1. Add support for command-line arguments like -a and -l.
2. Add the ability to provide a directory as a command-line argument and list the files in that directory instead of the current directory.
