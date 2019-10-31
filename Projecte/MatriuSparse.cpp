#include "MatriuSparse.h"

MatriuSparse::MatriuSparse(MatriuSparse& matriu) {
	copiarLlistes(matriu);
	m_nFiles = matriu.getNFiles();
	m_nColumnes = matriu.getNColumnes();
}

MatriuSparse::MatriuSparse(string fitxer) {
	m_nFiles = 0;
	m_nColumnes = 0;
	ifstream file;
	file.open(fitxer);
	if (file.is_open()) {
		int fila = 0, columna = 0;
		while (!file.eof() && !file.bad()) {
			file >> fila;
			file >> columna;
			if (fila > m_nFiles) {
				m_nFiles = fila;
			}
			if (columna > m_nColumnes) {
				m_nColumnes = columna;
			}
			pushVal(fila, columna, 1);
		}
	}else {
		cout << "Error obrin arxiu" << endl;
	}
	file.close();
}

bool MatriuSparse::cercaPosicio(int fila, int columna) {
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
bool MatriuSparse::cercaPosicio(int fila, int columna, float& valor) {
	bool trobat = false;
	forward_list<int>::iterator it_fila = m_fila.begin();
	forward_list<int>::iterator it_columna = m_columna.begin();
	forward_list<int>::iterator it_valor = m_columna.begin();
	while (it_fila != m_fila.end() && !trobat) {
		if (*it_fila == fila && *it_columna == columna) {
			trobat = true;
			valor = *it_valor;
			cout << valor << endl;
		}else {
			it_fila++;
			it_columna++;
			it_valor++;
		}
	}
	return trobat;
}

bool MatriuSparse::cercaPosicio(int fila, int columna, forward_list<int>::iterator& it_fila, forward_list<int>::iterator& it_columna) {
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

bool MatriuSparse::cercaPosicio(int fila, int columna, forward_list<float>::iterator& it_valor) {
	bool trobat = false;
	forward_list<int>::iterator it_fila = m_fila.begin();
	forward_list<int>::iterator it_columna = m_columna.begin();
	it_valor = m_valor.begin();
	while (it_fila != m_fila.end() && !trobat) {
		if (*it_fila == fila && *it_columna == columna) {
			trobat = true;
		}
		else {
			it_fila++;
			it_columna++;
			it_valor++;
		}
	}
	return trobat;
}


bool MatriuSparse::getVal(int fila, int col, float& valor) {
	try {
		if (fila < 0 || col < 0 || fila > m_nFiles || col > m_nColumnes) {
			throw "Fora de rang";
		}else {
			if (!cercaPosicio(fila, col, valor)) {
				cout << "no trobat" << endl;
				valor = 0;
			}
		}
	}catch (const char* e) {
		cout << e << endl;
		return false;
	}
	cout << "trobat" << endl;
	return true;
}

void MatriuSparse::setVal(int fila, int columna, float valor) {
	if (valor != 0){
		if (fila > m_nFiles) {
			m_nFiles = fila;
		}
		if (columna > m_nColumnes) {
			m_nColumnes = columna;
		}
		forward_list<float>::iterator it_valor;
		if (!cercaPosicio(fila, columna, it_valor)) {
			pushVal(fila, columna, valor);
		}else {
			*(it_valor) = valor;
		}
	}else {
		return;
	}
}

void MatriuSparse::pushVal(int fila, int columna, float valor) {
	m_fila.push_front(fila);
	m_columna.push_front(columna);
	m_valor.push_front(valor);
}

MatriuSparse& MatriuSparse::operator=(MatriuSparse& matriu) {
	if (!buida()) {
		buidarLlistes();
	}
	copiarLlistes(matriu);
	m_nFiles = matriu.getNFiles();
	m_nColumnes = matriu.getNColumnes();
	return matriu;
}

void MatriuSparse::copiarLlistes(MatriuSparse& m) {
	buidarLlistes();

	forward_list<int>::iterator it_fila = m.m_fila.begin();
	forward_list<int>::iterator it_columna = m.m_columna.begin();
	forward_list<float>::iterator it_valor = m.m_valor.begin();
	while (it_fila != m.m_fila.end()) {
		m_fila.push_front(*it_fila);
		m_columna.push_front(*it_columna);
		m_valor.push_front(*it_valor);

		it_fila++;
		it_columna++;
		it_valor++;
	}
}

MatriuSparse& MatriuSparse::operator*(float n) {
	try {
		if (n == 0) { throw "Multiplicant per zero"; }

		MatriuSparse* M = new MatriuSparse();
		forward_list<int>::iterator it_fila = m_fila.begin();
		forward_list<int>::iterator it_columna = m_columna.begin();
		forward_list<float>::iterator it_valor = m_valor.begin();

		while (it_fila != m_fila.end()) {
			M->pushVal(*it_fila, *it_columna, (*it_valor) * n);
			it_fila++;
			it_columna++;
			it_valor++;
		}

		return *M;
	}catch (const char* e) {
		cout << e << endl;
		//tots els valors de la matriu son zero per tant no es guarda res en les llistes
		//pero es conserven les dimensions de la matriu
		buidarLlistes();
	}
}

vector<float> MatriuSparse::operator*(vector<float> v) {

	vector<float>* s = new vector<float>(0);

	return *s;
}

MatriuSparse& MatriuSparse::operator/(float n) {
	try {

		if (n == 0){
			throw "Divident es zero";
		}

		MatriuSparse* M = new MatriuSparse();
		forward_list<int>::iterator it_fila = m_fila.begin();
		forward_list<int>::iterator it_columna = m_columna.begin();
		forward_list<float>::iterator it_valor = m_valor.begin();

		while (it_fila != m_fila.end()) {
			M->pushVal(*it_fila, *it_columna, (*it_valor) / n);
			it_fila++;
			it_columna++;
			it_valor++;
		}

		return *M;
	}catch (const char* e) {
		cout << e << endl;
	}
}

ostream& operator<<(ostream& o, MatriuSparse& mD) {

	forward_list<int>::iterator it_fila = mD.m_fila.begin();
	forward_list<int>::iterator it_columna = mD.m_columna.begin();
	forward_list<float>::iterator it_valor = mD.m_valor.begin();

	cout << "MATRIU DE (FILES: " << mD.m_nFiles << " COLUMNES: " << mD.m_nColumnes << " )" << endl;
	
	while (it_valor != mD.m_valor.end()) {
		o << "( " << *(it_fila) << " :: " << *(it_columna) << " :: " << *(it_valor) << " )" << endl;
		it_valor++;
		it_fila++;
		it_columna++;
	}
	return o;
}
