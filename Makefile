

CC = clang++
FLAGS = -std=c++11
NAME = abstract_vm
FILE = main.cpp OperandFactory.cpp AbstractVM.cpp 


all : $(NAME)

$(NAME) :
	@$(CC) $(FLAGS) $(FILE) -o $(NAME)

clean :

fclean : clean
	@rm -rf $(NAME)

re : fclean all

