#include "MatriuDispersa.h"

MatriuDispersa::MatriuDispersa(MatriuDispersa& matriu) {
	m_fila = matriu.m_fila;
	m_columna = matriu.m_columna;
	m_nFiles = matriu.getNFiles();
	m_nColumnes = matriu.getNColumnes();
}


bool MatriuDispersa::cercaPosicio(int fila, int columna) {
	bool trobat = false;
	forward_list<int>::iterator it_fila = m_fila.begin();
	forward_list<int>::iterator it_columna = m_columna.begin();
	while (it_fila != m_fila.end() && !trobat) {
		if (*it_fila == fila && *it_columna == columna) {
			trobat = true;
		}else {
			it_fila++;
			it_columna++;
		}
	}
	return trobat;
}
bool MatriuDispersa::cercaPosicio(int fila, int columna, int& valor) {
	bool trobat = false;
	forward_list<int>::iterator it_fila = m_fila.begin();
	forward_list<int>::iterator it_columna = m_columna.begin();
	forward_list<int>::iterator it_valor = m_columna.begin();
	while (it_fila != m_fila.end() && !trobat) {
		if (*it_fila == fila && *it_columna == columna) {
			trobat = true;
			valor = *it_valor;
		}else {
			it_fila++;
			it_columna++;
			it_valor++;
		}
	}
	return trobat;
}

bool MatriuDispersa::cercaPosicio(int fila, int columna, forward_list<int>::iterator& it_fila, forward_list<int>::iterator& it_columna) {
	bool trobat = false;
	it_fila = m_fila.begin();
	it_columna = m_columna.begin();
	while (it_fila != m_fila.end() && !trobat) {
		if (*it_fila == fila && *it_columna == columna) {
			trobat = true;
		}else {
			it_fila++;
			it_columna++;
		}
	}
	return trobat;
}


bool MatriuDispersa::getValor(int fila, int col, int& valor) {
	if (fila < 0 || col < 0 || fila > m_nFiles || col > m_nColumnes) {
		return false;
	}else {
		if(!cercaPosicio(fila, col,valor)) {
			valor = 0;
		}
	}
	return true;
}

void MatriuDispersa::setValor(int fila, int columna, int valor) {
	if (valor != 0){
		if (fila > m_nFiles) {
			m_nFiles = fila;
		}
		if (columna > m_nColumnes) {
			m_nColumnes = columna;
		}
		m_fila.push_front(fila);
		m_columna.push_front(columna);
		m_valor.push_front(valor);
	}else {
		return;
	}
}


MatriuDispersa& MatriuDispersa::operator=(MatriuDispersa& matriu) {
	m_fila = matriu.m_fila;
	m_columna = matriu.m_columna;
	m_valor = matriu.m_valor;
	m_nFiles = matriu.getNFiles();
	m_nColumnes = matriu.getNColumnes();
	return matriu;
}

void MatriuDispersa::operator*(int n) {
	forward_list<int>::iterator it_fila = m_fila.begin();
	forward_list<int>::iterator it_columna = m_columna.begin();
	forward_list<int>::iterator it_valor = m_columna.begin();
	while (it_fila != m_fila.end()) {
		*it_valor *= n;
		it_fila++;
		it_columna++;
		it_valor++;
	}
}

void MatriuDispersa::operator/(int n) {
	forward_list<int>::iterator it_fila = m_fila.begin();
	forward_list<int>::iterator it_columna = m_columna.begin();
	forward_list<int>::iterator it_valor = m_columna.begin();
	while (it_fila != m_fila.end()) {
		*it_valor /= n;
		it_fila++;
		it_columna++;
		it_valor++;
	}
}