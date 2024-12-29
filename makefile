final:
	bison -d compiler.y
	flex compiler.l
	gcc compiler.tab.c lex.yy.c
	./a.exe

clean:
	del a.exe compiler.tab.c compiler.tab.h lex.yy.c output.txt