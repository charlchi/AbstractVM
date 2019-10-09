CC = clang++
NAME = avm
SRC =  $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
#FLAGS = -Wall -Wextra -Werror -std=c++11
FLAGS = -std=c++11 -I include
$(NAME): $(OBJ)
		$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o:%.cpp
		$(CC) $(FLAGS) -c -o $@ $<

all: $(NAME)

clean:
		rm -rf $(OBJ)

fclean: clean
		rm -rf $(NAME) $(OBJ)

re:	fclean $(NAME)

tests:
	@mkdir -p "misc/output"
	@echo "\n\033[1;33m\033[4;33mLaunching unit tests for abstract VM...\n\033[0m"
	@i=1; for d in misc/tests/* ; do \
		echo "$$i - Running test file \"$$d\":" ; \
		ruby $$d ; \
		i=$$(($$i+1)) ; \
		echo "" ; \
	done
	@echo "\033[1;33m\033[4;33mDone.\n\033[0m"