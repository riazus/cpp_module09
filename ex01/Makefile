NAME		=	RPN

CC			=	c++
INCLUDES	=	includes
CPPFLAGS	=	-MD -g -Wall -Werror -Wextra -std=c++98 -I$(INCLUDES)
RM			=	rm -rf

SRCS		=	RPN.cpp \
				main.cpp

OBJS		=	$(SRCS:%.cpp=%.o)
DEPS		=	$(SRCS:%.cpp=%.d)

all:		$(NAME)

$(NAME):	$(OBJS)
			@$(CC) $(CPPFLAGS) $(OBJS) -o $(NAME)
			@echo "Linked into executable $(NAME)"

.cpp.o:
			@$(CC) $(CPPFLAGS) -c $< -o $(<:.cpp=.o)
			@echo "Compiling $<."

clean:
			@$(RM) $(OBJS)
			@$(RM) $(DEPS)
			@echo "Removed object files." 

fclean:		clean
			@$(RM) $(NAME)
			@echo "Removed executable."

re:			fclean 
			make all

-include $(DEPS)

.PHONY:		fclean, all, re