FILE_NAME = createkn01
OUT_FILE = demo

createkn01:
	gcc -o createkn01 createkn01.c create_knapsack.c
bruteforce:
	gcc -o bruteforce bruteforce.c
dynpro:
	gcc -o dynpro dynpro.c
igreedy:
	gcc -o igreedy igreedy.c

clean:
	rm -rf $(FILE_NAME)
clean-txt:
	rm -rf $(OUT_FILE).txt

