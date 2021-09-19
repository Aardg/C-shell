# C-shell

## How to complile and run code
* run __make__ on terminal
* run ./mhl

## Explanation of each file 


1. ### headers.c
    - This file has all the header files that were needed for the shell

1. myfunction.h 
    - A header file that has all my user defines functions and a coupl eof variables that were used throughout the shell
1. ### main.c
    - calls the actual looping function in **prompt.c**

1. ### prompt.c
    - On first call finds the home directory
    - Contains the main loop that takes input
    - Tokenizes all commands and breaks into their components (tokenizes with **;** and then with **" "** and **\t**)
    - Passes the tokenized commands to the **excommand.h**

    - Also outputs when a bg process ends

1. ### excommand.c
    - Recieves tokenized commands
    - Determines the command given to it and then calls their related functions.
    - **pwd** and **exit()** were implemented in this file itself

1. ### bg_file.c
    - Executes the files with **&** at the end in the background
    - Uses fork and execvp to do this

1. ### cd_file.c
    - Executes cd
    - I have handled
        - .
        - ..
        - ~ (home directory)
        - no argument (to home directory)
        - \- (previous directory)

1. ### echo_file.c
    - Executes echo command as per the specification of the assignment

1. ### pinfo_file.c
    - Executes pinfo command


1. ### repeat_file.c
    - executes repeat command

1. ### sys_file.c
    - Executes all other commands that were not implemented by me.
    - Uses execvp() and fork() again

1. ### throwerr.c 
    - used to give errors.


