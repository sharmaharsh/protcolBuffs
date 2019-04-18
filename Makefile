all: main proboc_pic32

main: lexer parser
	g++ -Wno-unused-function -Wall -Werror -Wextra -pedantic -std=c++14 lex.yy.c proboparser.tab.cpp proboc.cpp proboc_main.cpp -lfl -o proboc -lgflags

proboc_pic32: lexer parser
	g++ -DPIC32 -Wno-unused-function -Wall -Werror -Wextra -pedantic -std=c++14 lex.yy.c proboparser.tab.cpp proboc_pic32.cpp proboc_main.cpp -lfl -o proboc_pic32 -lgflags


lexer: proboparser.l
	flex proboparser.l

parser: proboparser.ypp
	bison -d proboparser.ypp

clean: 
	@rm proboparser.tab.cpp proboparser.tab.hpp lex.yy.c proboc || true
