Bob Marley's Minishell Backlog
======================

Our **Minishell** program is divided into three parts:
- #5 ;
- #6 ;
- **Other Shell Subsystems** ;

## The Parsing
is traditionally composed of two parts :
 - #10, which first will separate the string into **words** and *tokenize* them :
	- #9 ;
	- #13 ;

 - #17, will... compose an **Execution Chain** and a **Redirection Chain** for the **Executor** to use and
   - #18 ;

## The Execution
covers these topics :
- #11;

- #14;
 	- #12 ;
	- #16 ;

- #19 ;

## Other Shell Subsystems

- #8;

The **Envar expansion** will revolute around one `get_envar(char *envar_name);` which will be used to create various utils regarding specific needs of different parts of this project.

-----