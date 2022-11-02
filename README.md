## Documentation

On [pipes](http://www.zeitoun.net/articles/communication-par-tuyau/start);

## What is a shell, and how does it work ?
A **Shell** program is divided into three parts:
- [The Parsing](https://github.com/Minishellou/minishell/issues/5);
- [The Executor](https://github.com/Minishellou/minishell/issues/6);
- Other Shell Subsystems;
____

### The Parsing
is traditionally composed of two parts :
 - **The Lexer**, which first will separate the string into **words**, just before it convert them into **tokens** :
	- [The First Pass](https://github.com/Minishellou/minishell/issues/7);
	- [The Envar Expansion](https://github.com/Minishellou/minishell/issues/8);
	- The Second Pass;

 - **The Composer** will... compose an **Execution Chain** and a **Redirection Chain** for the **Executor** to use
