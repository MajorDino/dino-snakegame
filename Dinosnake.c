#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

int kbhit (void) {
  struct termios oldt, newt;
  int ch;
  int oldf;
 
  tcgetattr (STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr (STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl (STDIN_FILENO, F_GETFL, 0);
  fcntl (STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
  ch = getchar ();
 
  tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
  fcntl (STDIN_FILENO, F_SETFL, oldf);
 
  if (ch != EOF) {
    ungetc(ch, stdin);
    return 1;
  }
 
  return 0;
}

main () {
	int i, j, velx, vely, x, y, n, corpos[200], resposta, velocidade;
	char key, cenario[22][43];
	do {	
		srand (time (NULL));
		velx = 19;
		vely = 9;
		x = 0;
		y = 0;
		n = 0;
		system ("clear");
		printf ("===========================================\n");
		printf ("|                                         |\n");
		printf ("|                                         |\n");
		printf ("|                                         |\n");
		printf ("|                                         |\n");
		printf ("|                                         |\n");
		printf ("|                                         |\n");
		printf ("|                                         |\n");
		printf ("|                                         |\n");
		printf ("|                  o                      |\n");
		printf ("|                                         |\n");
		printf ("|                                         |\n");
		printf ("|                                         |\n");
		printf ("|                                         |\n");
		printf ("|                                         |\n");
		printf ("|                                         |\n");
		printf ("|                                         |\n");
		printf ("|                                         |\n");
		printf ("|                                         |\n");
		printf ("|                                         |\n");
		printf ("|                                         |\n");
		printf ("===========================================\n");
		printf ("\nPRESS ENTER...\t\t");
		getchar ();
		system ("clear");
		do {
			printf ("\nQual a velocidade?\n[1] Fácil\n[2] Normal\n[3] Difícil\n[4] Brutal\n\nR: ");
			scanf ("%d", &resposta);
		} while (resposta < 1 || resposta > 4);
		if (resposta == 1) velocidade = 400000;
		else if (resposta == 2) velocidade = 200000;
		else if (resposta == 3) velocidade = 100000;
		else velocidade = 50000;
		printf ("\n PRESS ANY KEY...\t\t");
		getchar ();
		
		while (1) {
			for (i = 0; i < 43; i++) {
				cenario[0][i] = '=';
				cenario[21][i] = '=';
			}
			for (i = 1; i <= 20; i++) {
				for (j = 0; j < 43; j++) {
					if (j == 0 || j == 42) {
						cenario[i][j] = '|';
					}
					else {
						cenario[i][j] = ' ';
					}
				}
			}
			if (y == 0 && x == 0) {
			 	do {
					y = rand() % 20;
				} while (y < 1 || y > 20);
				do {
					x = rand() % 41;
				} while (x % 2 == 0 || x < 1 || x > 41);
			}
			else if (vely == y && velx == x) {
				do {
					y = rand() % 20;
				} while (y < 1 || y > 20);
				do {
					x = rand() % 41;
				} while (x % 2 == 0 || x < 1 || x > 41);
				n = n + 2;
			}
			cenario[y][x] = 'X';
			for (i = n; i > 0; i = i - 2) {
				corpos[i-2] = corpos[i-4];
				corpos[i-1] = corpos[i-3];
			}
			corpos[0] = vely;
			corpos[1] = velx;
			
			if (kbhit()) {
				key = getchar ();
			}
			
			if (key == 'w') {
				vely -= 1;
				if (vely <= 0) {
					break;
				}
			}
			else if (key == 'a') {
				velx -= 2;
				if (velx <= 0) {
					break;
				}
			}
			else if (key == 's') {
				vely += 1;
				if (vely >= 21) {
					break;
				}
			}
			else if (key == 'd') {
				velx += 2;
				if (velx >= 42) {
					break;
				}
			}
			else {
				continue;
			}
			
			for (i = 0; i < n; i = i+2) {
				cenario[corpos[i]][corpos[i+1]] = 111;
			}
			if (cenario[vely][velx] != ' ' && cenario[vely][velx] != 'X') {
				break;
			}
			cenario[vely][velx] = 111;
			
			system ("clear");
			for (i = 0; i < 22; i++) {
				if (i == 0 || i == 21) {
					printf("\x1b[32m");
				}
				else {
					printf("\x1b[0m");
				}
				for (j = 0; j < 43; j++) {
					if ((i != 0 && i != 21) && (j == 0 || j == 42)) {
						printf("\x1b[32m%c\x1b[0m", cenario[i][j]);
					}
					else if (y == i && x == j) {
						printf("\x1b[31m%c\x1b[0m", cenario[i][j]);
					}
					else {
						printf("%c", cenario[i][j]);
					}
				}
				printf("\n");
			}
			usleep (velocidade);
		}
		printf ("\x1b[0m\nGAME OVER\n\nRestart?\n[1] Sim  [2] Nao\n\nR: ");
		scanf ("%d", &resposta);
	} while (resposta == 1);
}
