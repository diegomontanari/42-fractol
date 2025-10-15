#STRUCTURE OF MAKEFILE: first variables, then rules.

#STRUCTURE OF A RULE IN MAKEFILE:
# target: prerequisites
#	recipe

#target-> the thing you want to create/do
#prerequisites-> the conditions for the recipe to "shoot" (recipe shoots only is prerequisites are ok)
#recipe-> the list of commands that builds the target

#INSERT A VARIABLE:
# easy, just write $(VAR_NAME)

#CONVENTIONALLY USED NAMES FOR TARGETS:
#all-> to build everything. 
#clean-> to remove temporary files.
#fclean-> to remove everything (including executables) (fullclean)
#re-> to rebuild from scratch. 
#name-> name of the variable you want to create

#ECHO: is a comment that is shown in the terminal while the program is running. Example:
#clean:
#    echo "Cleaning up temporary files..."
#    rm -f *.o
#    echo "Cleaning complete!"

# rm -f -> f means 'force', so if the file does not exist yet an error is not returned

# ar -> stands for archiver (requires at least an option after it)

# rcs -> 
#c creates the archive if it does not exist,
# r replaces or add files in the archive,
# s creates/updates the index for the linker,
# NOTE: The order of rcs is not fixed, but it's a good habit to follow the convention.

# LINKING: To create an executable file, the object files need to be linked (the various parts of the
# code need to be linked together). This is done by the linker. Using an index makes the linking
# process much faster (just like for us humans, an index is useful to quickly find information).

#INFO:
# -c (compile)-> creates the file without linking (only .o)
# -o (output) -> you can choose the output name (ex: gcc ft_1.c -o ft_1.o)
#  if you don't use -o the file will be created with a standard name

NAME = libft.a

SRCS = ft_isdigit.c ft_memset.c ft_strjoin.c ft_strtrim.c ft_isprint.c \
ft_putchar_fd.c ft_strlcat.c ft_substr.c ft_atoi.c ft_itoa.c ft_putendl_fd.c \
ft_strlcpy.c ft_tolower.c ft_bzero.c ft_putnbr_fd.c ft_strlen.c \
ft_toupper.c ft_calloc.c ft_memchr.c ft_putstr_fd.c ft_strmapi.c ft_isalnum.c \
ft_memcmp.c ft_split.c ft_strncmp.c ft_isalpha.c ft_memcpy.c ft_strchr.c\
ft_strnstr.c ft_isascii.c ft_memmove.c ft_strdup.c ft_strrchr.c ft_striteri.c \

BONUS = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
		ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c \

OBJS = ${SRCS:.c=.o}

OBJSBONUS = ${BONUS:.c=.o}

CC		= gcc
RM		= rm -f

CFLAGS = -Wall -Wextra -Werror

.c.o:
		${CC} ${CFLAGS} -c $< -o $@

$(NAME): ${OBJS}
		ar rcs ${NAME} ${OBJS}

bonus:	${OBJSBONUS}
		ar rcs ${NAME} ${OBJSBONUS}

all:	${NAME}

clean:
		${RM} ${OBJS} ${OBJSBONUS}

fclean:	clean
		${RM} ${NAME}

re:		fclean all
