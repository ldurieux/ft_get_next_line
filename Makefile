NAME		= get_next_line

CCDEFS		= BUFFER_SIZE=5 \

SRCS 		= \
			  main.c \
			  get_next_line.c \
			  get_next_line_utils.c \
			  get_next_line_bonus.c \
			  get_next_line_utils_bonus.c \

ASMSRCS		= \

LIB_NAMES 	= \

LIB_DYN		= \
			  
HEADERS		= \

LIBS		= $(subst lib,-l,$(notdir $(LIB_NAMES)))
LIB_LD		= $(foreach lib,$(LIB_NAMES),-L$(lib))
LIB_PATHS	= $(foreach lib,$(LIB_NAMES),$(lib)/$(notdir $(lib)).a)
LIB_HEADERS	= $(foreach lib,$(LIB_NAMES),-I$(lib)/includes/)

OBJS			= ${SRCS:.c=.o} $(ASMSRCS:.s=.o)
DEPS			= ${SRCS:.c=.d}
CC				= gcc -no-pie
CCDEFSFLGS		= $(foreach def,$(CCDEFS),-D $(def))
CCWFLGS			= -Wall -Wextra -Werror
CCDBGFLGS		= -g -fsanitize=address
CCO1FLGS		= -O1 -march=native
CCO2FLGS		= -O2 -march=native
CCO3FLGS		= -O3 -march=native
DEPSFLAGS		= -MMD -MP
RM				= rm -f
MAKE			= make -C
AR				= ar
ARFLAGS			= rc
NASM			= nasm
NASMFLAGS		= -felf64

.PHONY: all clean fclean re

all : $(NAME)

$(NAME) : $(LIB_PATHS) $(OBJS)
		$(CC) $(CCWFLAGS) $(CCDBGFLGS) -I$(HEADERS) $(LIB_HEADERS) -o $@ $(OBJS) $(LIB_LD) $(LIB_DYN) $(LIBS) -L/usr/lib -lXext -lX11 -lm

$(LIB_PATHS) :
		$(MAKE) $(dir $@)

clean :
		-$(RM) $(OBJS) $(DEPS)

fclean : clean
		$(foreach lib, $(LIB_NAMES), \
			$(MAKE) $(lib) fclean; \
		)
		-$(RM) $(NAME)

re : fclean all

%.o : %.asm Makefile
		$(NASM) $(NASMFLAGS) -o $@ $<

-include $(DEPS)

%.o : %.c Makefile
		$(CC) $(CCWFLAGS) $(CCDBGFLGS) $(DEPSFLAGS) $(CCDEFSFLGS) -I$(HEADERS) $(LIB_HEADERS) -c $< -o $@ $(LIB_LD) $(LIBS)
