#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <time.h>

main () {
	int i, j, velx, vely, x, y, n, corpos[200], resposta;
	char key, cenario[22][43];
	do {
		velx = 19;
		vely = 9;
		x = 0;
		y = 0;
		n = 0;
		system("cls");
		printf("===========================================\n");
		printf("|                                         |\n");
		printf("|                                         |\n");
		printf("|                                         |\n");
		printf("|                                         |\n");
		printf("|                                         |\n");
		printf("|                                         |\n");
		printf("|                                         |\n");
		printf("|                                         |\n");
		printf("|                  þ                      |\n");
		printf("|                                         |\n");
		printf("|                                         |\n");
		printf("|                                         |\n");
		printf("|                                         |\n");
		printf("|                                         |\n");
		printf("|                                         |\n");
		printf("|                                         |\n");
		printf("|                                         |\n");
		printf("|                                         |\n");
		printf("|                                         |\n");
		printf("|                                         |\n");
		printf("===========================================\n");
		printf("\nPRESS 'W', 'A', 'S' or 'D'...\n");
		
		while (1 > 0) {
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
				key = getch();
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
				cenario[corpos[i]][corpos[i+1]] = 254;
			}
			if (cenario[vely][velx] != ' ' && cenario[vely][velx] != 'X') {
				break;
			}
			cenario[vely][velx] = 254;
			
			system("cls");
			for (i = 0; i < 22; i++) {
				if (i == 0 || i == 21) {
					printf("\x1b[32m");
				}
				else {
					printf("\x1b[0m");
				}
				for (j = 0; j < 43; j++) {
					if ((i != 0 && i != 21) && j == 0 || j == 42) {
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
		}
		printf("\x1b[0m\nGAME OVER\n\nRestart?\n[1] Sim  [2] Nao\n\nR: ");
		scanf("%d", &resposta);
	} while (resposta == 1);
}
