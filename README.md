# Edytor-plików-PGM
Projekt napisany przeze mnie podczas zajęć z programwoania w języku C. Pozwala na proste działania na plikach graficznych PGM.

Wybierzmy plik do prezentacji działania:

![Angel original](https://github.com/MaciejG604/PGM-Files-editor/blob/master/Resources/Results/Original.PNG)

Po zastosowaniu szumu pieprz i sól:

![Angel salted](https://github.com/MaciejG604/PGM-Files-editor/blob/master/Resources/Results/Salt&Pepper.PNG)

Zastosowanie filtru medianowego około 5 razy:

![Angel median](https://github.com/MaciejG604/PGM-Files-editor/blob/master/Resources/Results/Medianfilter.PNG)

Zastosowanie filtru gaussa i negatyw:

![Angel negative](https://github.com/MaciejG604/PGM-Files-editor/blob/master/Resources/Results/Negative.PNG)

# Format .PGM
Plik .PGM jest sekwencją wartości szarości poszczególnych pikseli zapisanych znakami ASCII.
Jego format składa się z poniższych danych (w kolejnosci):
1. Typ pliku składający się z dwóch znaków, np. "P1".
2. Znak biały (spacja, tabulator, nowa linia).
3. Szerokość obrazu w pikselach, zapisana jako liczba dziesiętna.
4. Znak biały.
5. Wysokość obrazu w pikselach, zapisana jako liczba dziesiętna.
6. Znak biały.
7. Maksymalna wartość szarości pikseli (Maxval) w obrazie (między 65536 - 0)
8. Znak biały, zazwyczaj nowa linia.
9. Sekwencja szarości pikseli zapisana rzędami od góy do dołu. Każdy rząd zawiera wartości od 0 do wartości Maxval, gdzie 0 oznacza czerń a Maxval biel, w kolejnosci pikseli od lewej do prawej. Wartości szarości mogą być zapisane w formacie binarnym (MSBF) dwu lub jedno bitowym zaleznie od wartości Maxval lub zapisane dziesiętnie i przedzielone białym znakiem (plain PGM format). OPISYWANY PROGRAM ZAKŁADA ZAPIS LICZBAMI DZIESIĘTNYMI PRZEDZIELONYMI ZNAKAMI BIAŁYMI.
(zródło:http://netpbm.sourceforge.net/doc/pgm.html#:~:text=The%20PGM%20format%20is%20a,learn%20and%20write%20programs%20for.&text=A%20PGM%20image%20represents%20a,meaning%20of%20individual%20pixel%20values.)

# Struktura Programu
Projekt oparty jest na strukturze "struct obraz" przechowującej potrzebne dane dotyczace formatu obrazu oraz wskaznik na alokowaną dynamicznie dwuwymiarową tablicę wartości pikseli. Interfejs użytkownika zbudowany na wpisywanych przez uzytkownika wartosciach z klawiatury w formie liczb zawiera sie czesciowo w funckji "main" oraz "wezobraz". Pozostałe funckje dokonują tylko odpowiednich dzialan na przekazanych im danych, niektore znich ,jak "obroc","zmniejsz" czy "zwieksz" przeprowadzaja ponowną alokację tablic pikseli i zwracaja nowe wartosci struktur "struct obraz", ktore musza byc odpowiednio zapisane.

# Wazne ifnformacje
Po wykonaniu na pliku wybranych dzialan nalezy go zapisac przed wyjsciem (opcja 9).
W splocie (opcja 12) nalezy wpisywac wartosci wag kernela po 3, przykladowo "1 2 3 *ENTER 4 5 6 *ENTER 7 8 9 *ENTER".
