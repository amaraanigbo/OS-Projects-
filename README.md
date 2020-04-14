# Operating Systems CS354 
## Project 1 : Building a UNIX Shell 
##### Amara Anigbo and Max Barrett 
-------------------------------------
### Description of Project 
This project created a UNIX shell in C which has it's own internal commands. 

### How to run Program 
1. In the terminal, use the "cd" command to get to the folder for the project titled "s20cs354p1_anigbobarrett".
2. Once in that directory/folder titled "s20cs354p1_anigbobarrett", type in the "make" command which compiles the file. 
3. After the file compiles, type in the command "./myshell". 
4. Test the internal commands listed in this document. 


###Commands 

1. The available commands are myquit, myclr, myecho, mypause, and mydir.
2. The following external UNIX commands are blocked: clear, exit, pause, echo, and ls. 

| Internal Commands     | Output                                                    | 
| ----------------------|:---------------------------------------------------------:| 
| myquit                | quit the shell                                            | 
| myclr                 | clears the terminal                                       |             
| myecho "comment"      | displays "comment" followed by new line                   |    
| mypause               | pause operation of the shell until "Enter" key is pressed | 
| mydir                 | lists the content of directory                            |  

##### mydir Command 

For the mydir command, to see files in current working directory "mydir ." To see files in the directory above the current working directory type the command 
"mydir .." 

