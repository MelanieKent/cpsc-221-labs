all : lists

linked_list.o : linked_list.cpp linked_list.h
	clang++ -std=c++14 -g -O0 -Wall -Wextra -pedantic -c linked_list.cpp -o linked_list.o

lists.o : lists.cpp linked_list.h
	clang++ -std=c++14 -g -O0 -Wall -Wextra -pedantic -c lists.cpp -o lists.o

lists : lists.o linked_list.o
	clang++ -std=c++14 -Wall -g lists.o linked_list.o -o lists

clean :
	rm -f linked_list.o lists.o lists

