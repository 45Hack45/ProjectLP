#pragma once
#include <list>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class MatriuSparse{
public:
	MatriuSparse(): m_nFiles(0), m_nColumnes(0) {};
	MatriuSparse(int files, int columnes) { init(files, columnes); }
	MatriuSparse(string fitxer);
	MatriuSparse(MatriuSparse& matriu);

	~MatriuSparse(){}

	void init(int files, int columnes) {
		if (!buida()){
			buidarLlistes();
		}
		m_nFiles = files;
		m_nColumnes = columnes;
	}

	int getNFiles()const { return m_nFiles; }
	int getNColumnes()const { return m_nColumnes; }

	bool getVal(int fila, int col, float& valor);
	void setVal(int fila, int col, float valor);

	bool buida() {
		return (m_nFiles > 0 && m_nColumnes > 0);
	}

	MatriuSparse& operator=(MatriuSparse& matriu);
	MatriuSparse& operator*(float n);
	//TOOD: operator*(vector)
	vector<float> operator*(vector<float> v);
	MatriuSparse& operator/(float n);
	//TODO: operator<<()
	friend ostream& operator<<(ostream& o, MatriuSparse& mD);

private:
	vector<int> m_fila;
	vector<int> m_columna;
	vector<float> m_valor;

	int m_nFiles;
	int m_nColumnes;

	//Afageix un valor a la matriu
	void pushVal(int fila, int columna, float valor);

	void insertVal(int fila, int columna, float valor);

	//Crida clear en totes les llistes
	void buidarLlistes() {
		m_nFiles = 0;
		m_nColumnes = 0;
		m_fila.clear();
		m_columna.clear();
		m_valor.clear();
	}

	//Copia un per un els valors de m a la matriu
	void copiarLlistes(MatriuSparse& m);

	bool cercaPosicio(int fila, int columna);
	bool cercaPosicio(int fila, int columna, float& valor);
	bool cercaPosicio(int fila, int columna, vector<int>::iterator& it_fila, vector<int>::iterator& it_columna);
	bool cercaPosicio(int fila, int columna, vector<float>::iterator& it_valor);
};
