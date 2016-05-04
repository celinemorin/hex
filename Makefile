NAME		=	hex

NAMEBASE    =   $(shell basename $(NAME))

CC		=	gcc

FLAGS		=	-Wall

SRCDIR		=	srcs/

OBJDIR		=	objs/

INCDIR		=	includes/

SRCBASE		=	hex.c \
				save.c

INCBASE		=	hex.h \
				save.h

SRCS		=	$(addprefix $(SRCDIR), $(SRCBASE))

INCS		=	$(addprefix $(INCDIR), $(INCBASE))

OBJS		=	$(addprefix $(OBJDIR), $(SRCBASE:.c=.o))

.SILENT:

all:		$(NAME)
	printf "\n\033[38;5;44m  ALL    $(NAMEBASE) is done\033[0m\033[K"
	printf "\n\n"

$(NAME):	$(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS)
	printf "\n\033[38;5;22m  MAKE   $(NAMEBASE)\033[0m\033[K"

$(OBJS):	$(SRCS) $(INCS)
	printf "\n\033[38;5;11m  MAKE   $(NAMEBASE) please wait...\033[0m\033[K"
	mkdir -p $(OBJDIR)
	(cd $(OBJDIR);															\
	$(CC) $(FLAGS) -c $(addprefix ../, $(SRCS))							    \
	-I $(addprefix ../, $(INCDIR)))

clean:
	printf "\n\033[38;5;11m  CLEAN  $(NAMEBASE) please wait...\033[0m\033[K"
	rm -R $(OBJDIR) &> /dev/null 2>&1;										\
	printf "\n\033[38;5;124m  CLEAN  $(NAMEBASE)\033[0m\033[K"
	printf "\n\n"

fclean:		clean
	printf "\r\033[38;5;11m  FCLEAN $(NAMEBASE) please wait...\033[0m\033[K"
	rm $(NAME) &> /dev/null 2>&1;											\
	printf "\n\033[38;5;124m  FCLEAN $(NAMEBASE)\033[0m\033[K"
	printf "\n\n"

re:			fclean all

debug:		CC = cc
debug:		FLAGS += --analyze
debug:		re

.PHONY:		fclean clean re
