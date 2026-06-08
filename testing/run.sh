bison -d parser.y
flex scanner.l
clang main.c parser.tab.c lex.yy.c -o main

echo "3 + 4" | ./main
