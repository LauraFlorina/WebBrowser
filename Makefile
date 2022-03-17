build:
	gcc -g -Wall stiva/stiva_f.c coada/coada_f.c utils/utils.c pagina_web.c tab.c browser.c tema2.c -o tema2
clean:
	rm -rf tema2
