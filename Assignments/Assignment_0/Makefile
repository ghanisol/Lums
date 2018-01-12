php:	php.l php.y
	bison -d php.y
	flex php.l
	gcc -g -o $@ php.tab.c lex.yy.c -lfl

clean:
	-rm php.tab.h php php.tab.c lex.yy.c output_file.dot output.gif