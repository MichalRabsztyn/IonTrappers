// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <iostream>
#include <vector>
#include <complex>
/**
 * 
 */
class IONTRAPPERS_API MatrixCalculator
{
	std::complex<double>** m;///< pointer on dynamic allocated tabel
	int x;///< size of MatrixCalculator in x dimension
	int y;///< size of MatrixCalculator in y dimension
	int c_x;///< capacity of x dimension
	int c_y;///<capacity of y dimension
public:

	/**Konstruktor domyslny macierzy
	Tworzy obiekt ale nie rezerwuje na niego zadnej pamieci*/
	MatrixCalculator();

	/** Konstruktor - tworzy macierz o rozmiarach AxB gdzie A to liczba wierszy, a B to liczba kolumn
	@param[in] a liczba wierszy macierzy
	@param[in] b liczba kolumn macierzy*/
	MatrixCalculator(int a, int b);

	MatrixCalculator(int a, int b, std::complex<double>** tab);

	MatrixCalculator(int a, int b, std::vector<std::vector<std::complex<double>>> tab);

	/** Konstruktor kopiujacy
	@param[in] A macierz za pomoca ktorej nalezy zainicjowac dana macierz*/
	MatrixCalculator(MatrixCalculator& A);

	/**Destruktor macierzy*/
	~MatrixCalculator();

	/**Operator pozwalajacy na dostep do konkretnych komorek macierzy.
	Jesli macierz ma jedna wiersz lub kolumne to nalezy odwolac sie do niej - np A[0][n]
	@param[in] a indekswiersza do ktorego chcemy sie odwolac*/
	std::complex<double>* operator[] (int a) const;

	/**Operator przepisania macierzy
	@param[in] A macierz ktora chcemy przepisac
	@return *this */
	MatrixCalculator& operator= (const MatrixCalculator& A);



	MatrixCalculator& operator= (MatrixCalculator& A);


	MatrixCalculator tensorProduct(MatrixCalculator& A);

	/**Operator przepisania tablicy do macierzy. Zakladam, ze tablica ma rozmiar taki jak aktualnie ma macierz
	@param[in] a tablica zmiennych typu double, nalezy uwazac na rozmiar tablicy i macierzy
	@return *this */
	MatrixCalculator& operator=(std::complex<double>** a);

	/**Operator dodawania macierzy
	@param[in] skladnik sumy
	@return macierz sumy */
	MatrixCalculator operator+ (const MatrixCalculator& A)const;

	/**Operator dodawania i przypisania macierzy
	@param[in] A skladnik sumy
	@return *this */
	MatrixCalculator& operator+= (MatrixCalculator& A);

	/**Operator mnozenia macierzy
	@param[in] A prawostronny czynnik iloczynu macierzy
	@return macierz iloczynu*/
	MatrixCalculator operator* (const MatrixCalculator& A)const;

	/**Operator mnozenia macierzy przez skalar
	@param[in] a skalar przez ktory ma byc pomnozona macierz
	@return macierz iloczynu*/
	MatrixCalculator operator* (const std::complex<double> a)const;

	/**Operator mnozenia macierzy pezez skalar i przypisania
	@param[in] a skalar przez ktory ma byc pomnozona macierz
	@return macierz iloczynu*/
	MatrixCalculator operator*= (std::complex<double> a);

	/**Funkcja zaprzyjazniona - operator mnozenia macierzy przez skalar
	@param[in] a skalar przez ktory ma byc pomnozona macierz
	@return macierz iloczynu*/
	friend MatrixCalculator operator* (std::complex<double> a, MatrixCalculator A);

	/** Zamienia  ze soba kolumny macierzy
	@param[in] x1 indeks kolumny ktora ma byc zamieniona
	@param[in] x2 indeks kolumny ktora ma byc zamieniona*/
	void swap_x(int x1, int x2);

	/** Zamienia  ze soba kolumny macierzy
	@param[in] y1 indeks wiersza ktory ma byc zamieniony
	@param[in] y2 indeks wiersza ktory ma byc zamieniony*/
	void swap_y(int y1, int y2);

	/** Dodaje x kolumn do macierzy
	@param[in] x Liczba kolumn ktore chcemy dodac*/
	void add_d_x(int x);

	/**Ustawia rozmiar macierzy na y na x
	@param[in] y Liczba wierszy ktore chcemy posiadac po operacji
	@param[in] x Liczba kolumn ktore chcemy posiadac po operacji*/
	void set_d(int y, int x);

	/** Dodaje y wierszy do macierzy
	@param[in] y Liczba wierszy ktore chcemy dodac*/
	void add_d_y(int y);

	/**Wyswietla macierz*/
	const void print();

	/**Wyswietla macierz
	@param[in] precision ustawia precyzje wyswietlania liczb w macierzy
	@param[in] width ustawia szerokosc wyswietlenia pojedyñczej komorki macierzy*/
	const void print(int precision, int width);

	/**Wyswietla macierz
	@param[in] precision ustawia precyzje wyswietlania liczb w macierzy*/
	const void print(int precision);

	/**Wyswietla macierz transponowan¹
	@param[in] precision ustawia precyzje wyswietlania liczb w macierzy*/
	const void print_t(int precision);

	/**Zaprzyjazniona funkcja operator strumieniowy
	@param[in] os strumieñ do ktorego chcemy przeslac macierz
	@param[in] A Macierz ktora przesylamy do strumienia*/
	friend std::ostream& operator<<(std::ostream& os, MatrixCalculator& A);

	/**Zwraca wartosc y rozmiaru macierzy
	@return rozmiar y macierzy*/
	const int size_y()const;

	/**Zwraca wartosc x rozmiaru macierzy
	@return rozmiar x macierzy*/
	const int size_x()const;

	/**Zwraca wartosc x pojemnosci macierzy
	@return pojemnosc x macierzy*/
	const int capacity_x()const;

	/**Zwraca wartosc y pojemnosci macierzy
	@return pojemnosc y macierzy*/
	const int capacity_y()const;


};
