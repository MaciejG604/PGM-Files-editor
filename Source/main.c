#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <string.h>
#define szansa 15

struct obraz
{
	char nazwa[20];
	char rodzaj[2];
	int szarosc;
	int szerokosc;
	int wysokosc;
	int **tablica;
};



int wczytaj(FILE *plikof);
void clear();
void filtrmedianowy(struct obraz obrazf);
void filtrgaussa(struct obraz obrazf);
void pieprz(struct obraz obrazf);
void wydruk(struct obraz obrazf);
void odbij(struct obraz obrazf, int osf);
void negatyw(struct obraz obrazf);
void proguj(int progf, struct obraz obrazf);
void zapiszhist(struct obraz obrazf);
void splot(struct obraz obrazf, int jadro[]);
struct obraz obroc(struct obraz obrazf);
struct obraz zmniejsz(struct obraz obrazf, int ilef);
struct obraz zwieksz(struct obraz obrazf, int ilef);
void wezobraz(struct obraz obrazf, int ile);
void zapisz(struct obraz obrazf, char nazwaf[]);

int main()
{
	int i, j, kom, komob, ileobraz=0;
	struct obraz test;
	struct obraz *tablicaobraz, *temptab;
	int ilosc, test1, razy=0;
	FILE *pliko;

	setlocale(LC_ALL, "polish_poland");

	{
		tablicaobraz = malloc(sizeof(struct obraz));
		ileobraz++;
		ilosc = ileobraz - 1;
		do
		{
			printf("Podaj nazwe pliku w formacie nazwa.pgm\n");
			scanf("%s", &tablicaobraz[ilosc].nazwa);
			clear();
			pliko = fopen(tablicaobraz[ilosc].nazwa, "r");
			if (pliko == NULL)
			{
				printf("Niepowodzenie otwarcia pliku\n");
				system("pause");
				system("cls");
			}
		} while (pliko == NULL);

		fscanf(pliko, "%2c", &tablicaobraz[ilosc].rodzaj);
		tablicaobraz[ilosc].szerokosc = wczytaj(pliko);
		tablicaobraz[ilosc].wysokosc = wczytaj(pliko);
		tablicaobraz[ilosc].szarosc = wczytaj(pliko);
		tablicaobraz[ilosc].tablica = malloc(tablicaobraz[ilosc].wysokosc * sizeof(tablicaobraz[ilosc].tablica));
		if (tablicaobraz[ilosc].tablica != NULL)
		{
			for (i = 0; i < tablicaobraz[ilosc].wysokosc; i++)
			{
				tablicaobraz[ilosc].tablica[i] = malloc(tablicaobraz[ilosc].szerokosc * sizeof(*tablicaobraz[ilosc].tablica));
				if (tablicaobraz[ilosc].tablica[i] == NULL)
				{
					printf("NIEPOWODZENIE ALOKACJI");
					for (i; i > 0; i--)
					{
						free(tablicaobraz[ilosc].tablica[i]);
					}
					free(tablicaobraz[ilosc].tablica);
					free(tablicaobraz);
					fclose(pliko);
					return 0;
				}
			}
		}
		else
		{
			printf("NIEPOWODZENIE ALOKACJI");
			for (i = 0; i < tablicaobraz[ilosc].szerokosc; i++)
			{
				free(tablicaobraz[ilosc].tablica[i]);
			}
			free(tablicaobraz[ilosc].tablica);
			free(tablicaobraz);
			fclose(pliko);
			return 0;
		}

		for (j = 0; j < tablicaobraz[ilosc].wysokosc; j++)
		{
			for (i = 0; i < tablicaobraz[ilosc].szerokosc; i++)
			{
				tablicaobraz[ilosc].tablica[j][i] = wczytaj(pliko);
			}
		}

		//wydruk(tablicaobraz[ilosc]);
		fclose(pliko);
	}

	system("cls");

	do
	{
		do
		{
			printf("Wpisz:\n 1 aby wczytac kolejny obraz do bazy\n 2 aby wyswietlic liste obrazow w bazie\n 3 aby wybrac obraz do dalszych dzialan\n 4 aby wyjsc\n");
			test1 = scanf("%d", &kom);
			clear();
		} while (test1 == 0 || kom < 1 || kom>4);

		switch (kom)
		{
			case 1:
			{
				ileobraz++;
				ilosc = ileobraz - 1;
				temptab = realloc(tablicaobraz, ileobraz * sizeof(struct obraz));
				if (temptab != NULL)
				{
					tablicaobraz = temptab;
				}
				else
				{
					printf("NIEPOWODZENIE ALOKACJI");
					for (ilosc; ilosc >= 0; ilosc--)
					{
						for (i = 0; i < tablicaobraz[ilosc].szerokosc; i++)
						{
							free(tablicaobraz[ilosc].tablica[i]);
						}
						free(tablicaobraz[ilosc].tablica);
					}
					free(tablicaobraz);
					fclose(pliko);
					return 0;
				}

				do
				{
					printf("Podaj nazwe pliku w formacie nazwa.pgm\n");
					scanf("%s", &tablicaobraz[ilosc].nazwa);
					clear();
					pliko = fopen(tablicaobraz[ilosc].nazwa, "r");
					if (pliko == NULL)
					{
						printf("Niepowodzenie otwarcia pliku\n");
						system("pause");
						system("cls");
					}
				} while (pliko == NULL);

				fscanf(pliko, "%2c", &tablicaobraz[ilosc].rodzaj);
				tablicaobraz[ilosc].szerokosc = wczytaj(pliko);
				tablicaobraz[ilosc].wysokosc = wczytaj(pliko);
				tablicaobraz[ilosc].szarosc = wczytaj(pliko);
				tablicaobraz[ilosc].tablica = malloc(tablicaobraz[ilosc].wysokosc * sizeof(tablicaobraz[ilosc].tablica));
				if (tablicaobraz[ilosc].tablica != NULL)
				{
					for (i = 0; i < tablicaobraz[ilosc].wysokosc; i++)
					{
						tablicaobraz[ilosc].tablica[i] = malloc(tablicaobraz[ilosc].szerokosc * sizeof(*tablicaobraz[ilosc].tablica));
						if (tablicaobraz[ilosc].tablica[i] == NULL)
						{
							printf("NIEPOWODZENIE ALOKACJI");
							for (i; i > 0; i--)
							{
								free(tablicaobraz[ilosc].tablica[i]);
							}
							free(tablicaobraz[ilosc].tablica);
							free(tablicaobraz);
							fclose(pliko);
							return 0;
						}
					}
				}
				else
				{
					printf("NIEPOWODZENIE ALOKACJI");
					for (ilosc; ilosc >= 0; ilosc--)
					{
						for (i = 0; i < tablicaobraz[ilosc].wysokosc; i++)
						{
							free(tablicaobraz[ilosc].tablica[i]);
						}
						free(tablicaobraz[ilosc].tablica);
					}
					free(tablicaobraz);
					fclose(pliko);
					return 0;
				}

				for (j = 0; j < tablicaobraz[ilosc].wysokosc; j++)
				{
					for (i = 0; i < tablicaobraz[ilosc].szerokosc; i++)
					{
						tablicaobraz[ilosc].tablica[j][i] = wczytaj(pliko);
					}
				}
				fclose(pliko);
				break;
			}

			case 2:
			{
				for (i = 0; i < ileobraz; i++)
				{
					//system("cls");
					printf("%d. %s\n", (i + 1), tablicaobraz[i].nazwa);
				}
				do
					{
						printf("Wpisz:\n 1 aby wyjsc\n");
						test1 = scanf("%d", &komob);
						clear();
					} while (test1 == 0 || komob!=1);
				break;
			}

			case 3:
			{
				for (i = 0; i < ileobraz; i++)
				{
					//system("cls");
					printf("%d. %s\n", (i + 1), tablicaobraz[i].nazwa);
				}
				do
				{
					printf("Wpisz: numer obrazu, ktory chcesz wybrac\n");
					test1 = scanf("%d", &komob);
					clear();
				} while (test1 == 0 || komob < 1|| komob>ileobraz);
				razy++;
				wezobraz(tablicaobraz[komob - 1], razy);
				break;
			}

			case 4:
			{
				for (ilosc; ilosc >= 0; ilosc--)
				{
					for (i = 0; i < tablicaobraz[ilosc].wysokosc; i++)
					{
						free(tablicaobraz[ilosc].tablica[i]);
					}
					free(tablicaobraz[ilosc].tablica);
				}
				free(tablicaobraz);
				break;
			}
		}
	}while (kom != 4);

	system("pause");
	return 1;
}

void wydruk(struct obraz test)
{
	int i, j;
	for (j = 0; j < test.wysokosc; j++)
	{
		for (i = 0; i < test.szerokosc; i++)
		{
			printf("%d", test.tablica[j][i]);
		}
		printf("\n");
	}
}

int wczytaj(FILE *plikof)
{
	int test, wynik;
	do
	{
		test = fscanf(plikof, "%d", &wynik);
		if (test == 0)
		{
			fscanf(plikof, "%s");
		}
	} while (test <= 0);
	return wynik;
}

void clear()
{
	char a;
	do
	{
		a = getc(stdin);
	} while (a != '\n');
}

void pieprz(struct obraz obrazf)
{
	int i, j, los;
	srand(time(NULL));
	for (j = 0; j < obrazf.wysokosc; j++)
	{
		for (i = 0; i < obrazf.szerokosc; i++)
		{
			los = rand() % 101;
			if ((los) < szansa)
				obrazf.tablica[j][i] = 0; 
			if((los) > (100 - szansa))
				obrazf.tablica[j][i] = obrazf.szarosc;
		}
	}
}

void zapiszhist(struct obraz obrazf)
{
	FILE* plikcsv;
	int i, j;
	int *histogram;
	

	plikcsv = fopen("histogram.csv", "w");
	histogram = calloc((obrazf.szarosc+1), sizeof(int));
	if (plikcsv == NULL||histogram == NULL)
	{
		printf("NIEPOWODZENIE ZAPISU\n");
		system("pause");
	}
	else
	{
		for (j = 0; j < obrazf.wysokosc; j++)
		{
			for (i = 0; i < obrazf.szerokosc; i++)
			{
				histogram[obrazf.tablica[j][i]]++;
			}
		}

		for (i = 0; i < obrazf.szarosc+1 ; i++)
		{
			fprintf(plikcsv, "%d;\n", histogram[i]);
		}
	}
	
	fclose(plikcsv);
	free(histogram);
}

void proguj(int progf, struct obraz obrazf)
{
	int i, j;
	for (j = 0; j < obrazf.wysokosc; j++)
	{
		for (i = 0; i < obrazf.szerokosc; i++)
		{
			if (obrazf.tablica[j][i] > progf)
				obrazf.tablica[j][i] = obrazf.szarosc;
			else
				obrazf.tablica[j][i] = 0;
		}
	}
}

void filtrmedianowy(struct obraz obrazf)
{
	int i, j, k, l, error=1;
	int okno[9], temp;
	int **tabf;

	tabf = malloc(obrazf.wysokosc * sizeof(tabf));
	if (tabf != NULL)
	{
		for (i = 0; i < obrazf.wysokosc; i++)
		{
			tabf[i] = malloc(obrazf.szerokosc * sizeof(tabf));
			if (tabf[i] == NULL)
			{
				error = 0;
			}
			else
			{
				for (j = 0; j < obrazf.szerokosc; j++)
				{
					tabf[i][j] = obrazf.tablica[i][j];
				}
			}
		}

		if (error==1)
		{
			for (i = 1; i < obrazf.wysokosc-1; i++)
			{
				for (j = 1; j < obrazf.szerokosc-1; j++)
				{
					for (k = 0; k < 3; k++)
					{
						for (l = 0; l < 3; l++)
						{
							okno[k*3+l] = obrazf.tablica[i - 1 + l][j - 1 + k];
						}
					}
					for (k = 0; k < 9; k++)
					{
						for (l = 0; l < 8; l++)
						{
							if (okno[l] > okno[l + 1])
							{
								temp = okno[l];
								okno[l] = okno[l + 1];
								okno[l + 1] = temp;
							}
						}
					}
					tabf[i][j] = okno[4];
				}
			}
			for (j = 1; j < obrazf.wysokosc-1; j++)
			{
				for (i = 1; i < obrazf.szerokosc-1; i++)
				{
					obrazf.tablica[j][i]=tabf[j][i];
				}
			}
		}
	}
	else
	{
		printf("NIEPOWODZENIE ALOKACJI");
	}
	
	for (i = 0; i < obrazf.wysokosc; i++)
	{
		free(tabf[i]);
	}
	free(tabf);

}

void zapisz(struct obraz obrazf, char nazwaf[])
{
	FILE* plik;
	int j, i;

	plik = fopen(nazwaf, "w");

	if (plik == NULL)
	{
		printf("NIEPOWODZENIE ZAPISU\n");
		nazwaf[1] ++;
		system("pause");
	}
	else
	{
		fprintf(plik, "%c%c\n%d %d\n%d\n", obrazf.rodzaj[0], obrazf.rodzaj[1], obrazf.szerokosc, obrazf.wysokosc, obrazf.szarosc);
		for (j = 0; j < obrazf.wysokosc; j++)
		{
			for (i = 0; i < obrazf.szerokosc; i++)
			{
				fprintf(plik, "%d ", obrazf.tablica[j][i]);
			}
			fprintf(plik,"\n");
		}
		fclose(plik);
	}
}

void filtrgaussa(struct obraz obrazf)
{
	int i, j, k, l, error = 1, srednia;
	int okno[9], temp;
	int **tabf;

	tabf = malloc(obrazf.wysokosc * sizeof(tabf));
	if (tabf != NULL)
	{
		for (i = 0; i < obrazf.wysokosc; i++)
		{
			tabf[i] = malloc(obrazf.szerokosc * sizeof(tabf));
			if (tabf[i] == NULL)
			{
				error = 0;
			}
			else
			{
				for (j = 0; j < obrazf.szerokosc; j++)
				{
					tabf[i][j] = obrazf.tablica[i][j];
				}
			}
		}

		if (error == 1)
		{
			for (i = 1; i < obrazf.wysokosc - 1; i++)
			{
				for (j = 1; j < obrazf.szerokosc - 1; j++)
				{
					for (k = 0; k < 3; k++)
					{
						for (l = 0; l < 3; l++)
						{
							okno[k * 3 + l] = obrazf.tablica[i - 1 + l][j - 1 + k];
						}
					}

					okno[0] *= 1;
					okno[1] *= 2;
					okno[2] *= 1;
					okno[3] *= 2;
					okno[4] *= 4;
					okno[5] *= 2;
					okno[6] *= 1;
					okno[7] *= 2;
					okno[8] *= 1;
					srednia = 0;

					for (k = 0; k < 9; k++)
					{
						srednia += okno[k];
					}
					srednia = srednia / 16;
					tabf[i][j] = srednia;
				}
			}
			for (j = 1; j < obrazf.wysokosc - 1; j++)
			{
				for (i = 1; i < obrazf.szerokosc - 1; i++)
				{
					obrazf.tablica[j][i] = tabf[j][i];
				}
			}
		}
	}
	else
	{
		printf("NIEPOWODZENIE ALOKACJI");
	}

	for (i = 0; i < obrazf.wysokosc; i++)
	{
		free(tabf[i]);
	}
	free(tabf);
}

void negatyw(struct obraz obrazf)
{
	int i, j;
	for (j = 0; j < obrazf.wysokosc; j++)
	{
		for (i = 0; i < obrazf.szerokosc; i++)
		{
			obrazf.tablica[j][i] = obrazf.szarosc - obrazf.tablica[j][i];
		}
	}
}

void odbij(struct obraz obrazf, int osf)
{
	int i, j, tempf;
	if (osf == 1)
	{
		for (j = 0; j < obrazf.wysokosc; j++)
		{
			for (i = 0; i < obrazf.szerokosc/2; i++)
			{
				tempf=obrazf.tablica[j][i];
				obrazf.tablica[j][i] = obrazf.tablica[j][obrazf.szerokosc - i-1];
				obrazf.tablica[j][obrazf.szerokosc - i-1] = tempf;
			}
		}
	}
	else
	{
		for (j = 0; j < obrazf.wysokosc/2; j++)
		{
			for (i = 0; i < obrazf.szerokosc; i++)
			{
				tempf = obrazf.tablica[j][i];
				obrazf.tablica[j][i] = obrazf.tablica[obrazf.wysokosc-j-1][i];
				obrazf.tablica[obrazf.wysokosc - j-1][i] = tempf;
			}
		}
	}
}

struct obraz obroc(struct obraz obrazf)
{
	int i, j, k, l, error = 1;
	int temp;
	struct obraz tempobraz;
	int **tabf;

	for (i = 0; i < 2; i++)
	{
		tempobraz.rodzaj[i] = obrazf.rodzaj[i];
	}
	for (i = 0; i < 20; i++)
	{
		tempobraz.nazwa[i] = obrazf.nazwa[i];
	}
	tempobraz.szarosc = obrazf.szarosc;
	tempobraz.szerokosc = obrazf.wysokosc;
	tempobraz.wysokosc = obrazf.szerokosc;




	tempobraz.tablica = malloc(tempobraz.wysokosc * sizeof(tempobraz.tablica));
	if (tempobraz.tablica != NULL)
	{
		for (i = 0; i < tempobraz.wysokosc; i++)
		{
			tempobraz.tablica[i] = malloc(tempobraz.szerokosc * sizeof(tempobraz.tablica));
			if (tempobraz.tablica[i] == NULL)
			{
				error = 0;
			}
			else
			{
				for (j = 0; j < obrazf.wysokosc; j++)
				{
					tempobraz.tablica[i][j] = obrazf.tablica[obrazf.wysokosc-j-1][obrazf.szerokosc-i-1];
				}
			}
		}
	}
	else
	{
		printf("NIEPOWODZENIE ALOKACJI");
	}

	return tempobraz;

}

struct obraz zmniejsz(struct obraz obrazf, int ilef)
{
	int i, j, error = 1;
	int temp;
	struct obraz tempobraz;

	for (i = 0; i < 2; i++)
	{
		tempobraz.rodzaj[i] = obrazf.rodzaj[i];
	}
	for (i = 0; i < 20; i++)
	{
		tempobraz.nazwa[i] = obrazf.nazwa[i];
	}
	tempobraz.szarosc = obrazf.szarosc;
	tempobraz.szerokosc = obrazf.szerokosc/ilef;
	tempobraz.wysokosc = obrazf.wysokosc/ilef;

	tempobraz.tablica = calloc(tempobraz.wysokosc, sizeof(tempobraz.tablica));
	if (tempobraz.tablica != NULL)
	{
		for (i = 0; i < tempobraz.wysokosc; i++)
		{
			tempobraz.tablica[i] = calloc(tempobraz.szerokosc, sizeof(tempobraz.tablica));
			if (tempobraz.tablica[i] == NULL)
			{
				error = 0;
			}
			else
			{
				for (j = 0; j < tempobraz.szerokosc; j++)
				{
					tempobraz.tablica[i][j] = obrazf.tablica[i*ilef][j*ilef];
				}
			}
		}
	}
	else
	{
		printf("NIEPOWODZENIE ALOKACJI");
	}

	return tempobraz;
}

struct obraz zwieksz(struct obraz obrazf, int ilef)
{
	int i, j, error = 1, k, l;
	int temp;
	struct obraz tempobraz;

	for (i = 0; i < 2; i++)
	{
		tempobraz.rodzaj[i] = obrazf.rodzaj[i];
	}
	for (i = 0; i < 20; i++)
	{
		tempobraz.nazwa[i] = obrazf.nazwa[i];
	}
	tempobraz.szarosc = obrazf.szarosc;
	tempobraz.szerokosc = obrazf.szerokosc * ilef;
	tempobraz.wysokosc = obrazf.wysokosc * ilef;

	tempobraz.tablica = calloc(tempobraz.wysokosc, sizeof(tempobraz.tablica));
	if (tempobraz.tablica != NULL)
	{
		for (i = 0; i < tempobraz.wysokosc; i++)
		{
			tempobraz.tablica[i] = calloc(tempobraz.szerokosc, sizeof(tempobraz.tablica));
			if (tempobraz.tablica[i] == NULL)
			{
				error = 0;
			}
		}
		for (i = 0; i < obrazf.wysokosc-1; i++)
		{
			for (j = 0; j < obrazf.szerokosc-1; j++)
			{
				for (k = 0; k < ilef; k++)
				{
					for (l = 0; l < ilef; l++)
					{
						tempobraz.tablica[i*ilef + k][j*ilef + l] = obrazf.tablica[i][j];
					}
				}
			}
		}
	}
	else
	{
		printf("NIEPOWODZENIE ALOKACJI");
	}

	return tempobraz;
}

void splot(struct obraz obrazf, int jadro[])
{
	int i, j, k, l, error = 1, srednia, dzielnik;
	int okno[9], temp;
	int **tabf;

	tabf = malloc(obrazf.wysokosc * sizeof(tabf));
	if (tabf != NULL)
	{
		for (i = 0; i < obrazf.wysokosc; i++)
		{
			tabf[i] = malloc(obrazf.szerokosc * sizeof(tabf));
			if (tabf[i] == NULL)
			{
				error = 0;
			}
			else
			{
				for (j = 0; j < obrazf.szerokosc; j++)
				{
					tabf[i][j] = obrazf.tablica[i][j];
				}
			}
		}

		if (error == 1)
		{
			for (i = 1; i < obrazf.wysokosc - 1; i++)
			{
				for (j = 1; j < obrazf.szerokosc - 1; j++)
				{
					for (k = 0; k < 3; k++)
					{
						for (l = 0; l < 3; l++)
						{
							okno[k * 3 + l] = obrazf.tablica[i - 1 + l][j - 1 + k];
						}
					}

					for(k=0;k<9;k++)
					okno[k] *= jadro[k];
				
					srednia = 0;
					dzielnik = 0;

					for (k = 0; k < 9; k++)
					{
						srednia += okno[k];
						dzielnik += jadro[k];
					}
					srednia = srednia / dzielnik;
					if (srednia < 0) srednia = 0;
					if (srednia > obrazf.szarosc) srednia = obrazf.szarosc;
					tabf[i][j] = srednia;
				}
			}
			for (j = 1; j < obrazf.wysokosc - 1; j++)
			{
				for (i = 1; i < obrazf.szerokosc - 1; i++)
				{
					obrazf.tablica[j][i] = tabf[j][i];
				}
			}
		}
	}
	else
	{
		printf("NIEPOWODZENIE ALOKACJI");
	}

	for (i = 0; i < obrazf.wysokosc; i++)
	{
		free(tabf[i]);
	}
	free(tabf);
}

void wezobraz(struct obraz obrazf, int ile)
{
	int test1, kom, prog, k, mniej, wiecej, kernel[9], i;
	const char pgm[5] = ".pgm";
	char os=' ',  nazwa[15]="@";
	nazwa[1] = (char)(ile + 48);
	strcat(nazwa, pgm);

	do
	{
		
		do
		{
			system("cls");
			printf("Wpisz:\n 1 aby odrocic wybrany obraz o k*90 stopni\n 2 aby odbic obraz wzgledem osi\n 3 aby zapieprzyc i zasolic obraz\n 4 aby stworzyc histogram w .csv\n 5 zaprogowac obraz\n\
 6 aby zrobic negatyw\n 7 aby przefiltrowac filtrem medianowym\n 8 aby przefiltrowac filtrem Gaussa\n 9 aby zapisac wynik\n 10 aby zmniejszyc obraz\n 11 aby powiekszyc obraz\n\
 12 aby stworzyc splot\n 13 aby wyjsc\n");
			test1 = scanf("%d", &kom);
			clear();
		} while (test1 == 0 || kom < 1 || kom>13);

		switch (kom)
		{
			case 1:
			{
				do
				{
					printf("Obrot obrazu o k*90 stopni, podaj k\n");
					test1 = scanf("%d", &k);
					clear();
				} while (test1 == 0 || k<0);
				for (k = k%4 ; k > 0; k--)
				{
					obrazf=obroc(obrazf, k);
				}
				break;
			}

			case 2:
			{
				
				do
				{
					printf("Wzgledem jakiej osi odbic?\n");
					test1 = scanf("%c", &os);
					clear();
				} while (test1 == 0 || (os !='x' && os != 'X' && os != 'y' && os != 'Y'));
				if (os == 'x' || os == 'X') odbij(obrazf, 1);
				if (os == 'y' || os == 'Y') odbij(obrazf, 2);
				break;
			}

			case 3:
			{
				pieprz(obrazf);
				break;
			}

			case 4:
			{
				zapiszhist(obrazf);

				break;
			}

			case 5:
			{
				do
				{
					printf("Wpisz wartosc progu miedzy 0 a %d\n", obrazf.szarosc);
					test1 = scanf("%d", &prog);
					clear();
				} while (test1 == 0 || prog < 0 || prog>obrazf.szarosc);
				proguj(prog, obrazf);
				break;
			}
			
			case 6:
			{
				negatyw(obrazf);
				break;
			}

			case 7:
			{
				filtrmedianowy(obrazf);
				break;
			}

			case 8:
			{
				filtrgaussa(obrazf);
				break;
			}

			case 9:
			{
				nazwa[0]++;
				zapisz(obrazf, nazwa);
				break;
			}

			case 10:
			{
				do
				{
					printf("Wpisz ile razy zmniejszyc\n");
					test1 = scanf("%d", &mniej);
					clear();
				} while (test1 == 0 || mniej<=0);
				obrazf=zmniejsz(obrazf, mniej);
				break;
			}

			case 11:
			{
				do
				{
					printf("Wpisz ile razy powiekszyc\n");
					test1 = scanf("%d", &wiecej);
					clear();
				} while (test1 == 0 || wiecej <= 0);
				obrazf = zwieksz(obrazf, wiecej);
				break;
			}

			case 12:
			{
				for (i = 0; i < 3; i++)
				{
					do
					{
						printf("Wpisz wyrazy do kernela, po 3\n");
						test1 = scanf("%d %d %d", &kernel[3*i], &kernel[3*i + 1], &kernel[3*i + 2]);
						clear();
					} while (test1 < 3);
				}
				splot(obrazf, kernel);
				break;
			}

		}
	} while (kom != 13);
}

