#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
using namespace std;

int** alokujTablice(int wiersze, int kolumny)
{
    int** tab = new int* [wiersze +1];
    //XXYY
    // XX - liczba kolumn
    //YY - liczba wierszy
    
    int rozmiar = kolumny;
    rozmiar = rozmiar << 16;
    rozmiar = rozmiar + wiersze;

    tab[0] = new int[1];
    tab[0][0] = rozmiar;
    tab++;

    for (int w = 0; w < wiersze; w++)
    {
        tab[w] = new int[kolumny];
        for (int k = 0; k < kolumny; k++)
        {
            tab[w][k] = 0;
        }
    }

    return tab;
}

void wypisz(int** tab)
{
    int rozmiar = tab[-1][0];
    int wiersze = rozmiar & 0x0000ffff;
    int kolumny = (rozmiar & 0xffff0000) >> 16; 
    
    for (int w = 0; w < wiersze; w++)
    {
        
        for (int k = 0; k < kolumny; k++)
        {
            cout << tab[w][k] << " ";
        }
        cout << endl;
    }
}

void skasuj(int** tab)
{
    int rozmiar = tab[-1][0];
    tab--;
    int wiersze = rozmiar & 0x0000ffff;
    for (int i = 0; i <= wiersze; i++)
    {
        delete[] tab[i];
    }
    delete[] tab;
}

int** wczytaj(const char* nazwaPliku)
{
    FILE* plik = fopen(nazwaPliku, "r+b");
    short kolumny;
    short wiersze;

    fread(&wiersze, sizeof(short), 1, plik);
    fread(&kolumny, sizeof(short), 1, plik);
    
    int** tab = alokujTablice(wiersze, kolumny);
    for (int w = 0; w < wiersze; w++)
    {
        fread(tab[w], sizeof(int), kolumny, plik);
    }
    fclose(plik);
    return tab;
}

void zapisz(int** tab, const char* nazwaPliku)
{
    FILE* plik = fopen(nazwaPliku, "w+b");
    
    int rozmiar = tab[-1][0];
    int wiersze = rozmiar & 0x0000ffff;
    int kolumny = (rozmiar & 0xffff0000) >> 16;
    fwrite(&rozmiar, sizeof(int), 1, plik);
    for (int w = 0; w < wiersze; w++)
    {
        fwrite(tab[w], sizeof(int), kolumny, plik);
    }
    fclose(plik);
}

int main()
{
    int wiersze = 5;
    int kolumny = 10;
    int** tab = alokujTablice(5, 10);

    for (int w = 0; w < wiersze; w++)
    {
        for (int k = 0; k < kolumny; k++)
        {
            tab[w][k] =(w+1)*(k+1);
        }
    }
    wypisz(tab);
    zapisz(tab, "dane.txt");
    skasuj(tab);
    int** tab2 = wczytaj("dane.txt");
    wypisz(tab2);
    skasuj(tab2);


}

