final:
	bison -d tamim.y
	flex tamim.l
	gcc tamim.tab.c lex.yy.c
	./a.exe

clean:
	del a.exe tamim.tab.c tamim.tab.h lex.yy.c output.txt