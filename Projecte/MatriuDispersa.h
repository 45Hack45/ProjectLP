#pragma once
#include <forward_list>

using namespace std;

class MatriuDispersa{
public:
	MatriuDispersa(): m_nFiles(0), m_nColumnes(0) {};
	MatriuDispersa(int files, int columnes) { init(files, columnes); }
	MatriuDispersa(MatriuDispersa& matriu);

	void init(int files, int columnes) {
		m_nFiles = files;
		m_nColumnes = columnes;
	}

	int getNFiles()const { return m_nFiles; }
	int getNColumnes()const { return m_nColumnes; }

	bool getValor(int fila, int col, int& valor);
	void setValor(int fila, int col, int valor);

	MatriuDispersa& operator=(MatriuDispersa& matriu);
	void operator*(int n);
	//TOOD: operator*(vector)
	void operator/(int n);
	//TODO: operator<<()

private:
	forward_list<int> m_fila;
	forward_list<int> m_columna;
	forward_list<int> m_valor;

	int m_nFiles;
	int m_nColumnes;

	bool cercaPosicio(int fila, int columna);
	bool cercaPosicio(int fila, int columna, int& valor);
	bool cercaPosicio(int fila, int columna, forward_list<int>::iterator& it_fila, forward_list<int>::iterator& it_columna);
};

