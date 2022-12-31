## SOURCES.MK ##

## SRC ##

SOURCES		+=                                		\
		src/minishell.c                          	\


## SRC/LIBFT ##

SOURCES		+=                                		\
		src/libft/ft_lexer_split.c               	\
		src/libft/ft_memcmp.c                    	\
		src/libft/ft_memcpy.c                    	\
		src/libft/ft_calloc.c                    	\
		src/libft/ft_putendl_fd.c                	\
		src/libft/ft_strnstr.c                   	\
		src/libft/ft_isalpha.c                   	\
		src/libft/ft_strtrim.c                   	\
		src/libft/ft_memmove.c                   	\
		src/libft/ft_isalnum.c                   	\
		src/libft/ft_strcmp.c                    	\
		src/libft/ft_isdigit.c                   	\
		src/libft/ft_isprint.c                   	\
		src/libft/ft_tolower.c                   	\
		src/libft/ft_toupper.c                   	\
		src/libft/ft_strncmp.c                   	\
		src/libft/ft_strlen.c                    	\
		src/libft/ft_putstr_fd.c                 	\
		src/libft/ft_bzero.c                     	\
		src/libft/ft_memset.c                    	\
		src/libft/ft_substr.c                    	\
		src/libft/ft_strmapi.c                   	\
		src/libft/ft_strchr.c                    	\
		src/libft/ft_atoi.c                      	\
		src/libft/ft_isascii.c                   	\
		src/libft/ft_itoa.c                      	\
		src/libft/ft_putchar_fd.c                	\
		src/libft/ft_strjoin.c                   	\
		src/libft/ft_split.c                     	\
		src/libft/ft_strlcat.c                   	\
		src/libft/ft_putnbr_fd.c                 	\
		src/libft/ft_memchr.c                    	\
		src/libft/ft_strrchr.c                   	\
		src/libft/ft_striteri.c                  	\
		src/libft/ft_strdup.c                    	\
		src/libft/ft_strlcpy.c                   	\


## SRC/NODE_MANAGER ##

SOURCES		+=                                		\
		src/node_manager/env_node_manager.c      	\
		src/node_manager/create_exec_node.c      	\
		src/node_manager/create_node.c           	\
		src/node_manager/chain_utils.c           	\


## SRC/INIT ##

SOURCES		+=                                		\
		src/init/init_global.c                   	\


## SRC/PARSING ##

SOURCES		+=                                		\
		src/parsing/token_parse.c                	\
		src/parsing/state_utils.c                	\


## SRC/COMPOSER ##

SOURCES		+=                                		\
		src/composer/composer.c                  	\
		src/composer/composer_utils.c            	\


## SRC/GARBAGE_CTR ##

SOURCES		+=                                		\
		src/garbage_ctr/garbage.c                	\


## SRC/LEXER ##

SOURCES		+=                                		\
		src/lexer/lexer_output_manager.c         	\
		src/lexer/chain_checker.c                	\
		src/lexer/line_parsing_process.c         	\
		src/lexer/char_manipulation.c            	\
		src/lexer/redir_utils.c                  	\
		src/lexer/redir_handler.c                	\
		src/lexer/check_char.c                   	\


