#include "MatriuSparse.h"

MatriuSparse::MatriuSparse(MatriuSparse& matriu) {
	copiarLlistes(matriu);
	m_nFiles = matriu.m_nFiles;
	m_nColumnes = matriu.m_nColumnes;
}

MatriuSparse::MatriuSparse(string fitxer) {
	m_nFiles = 0;
	m_nColumnes = 0;
	ifstream file;
	file.open(fitxer);
	if (file.is_open()) {
		int fila = 0,last_F = -1, columna = 0,last_C = -1;
		while (!file.eof() && !file.bad()) {
			file >> fila;
			file >> columna;
			if (last_F == fila && last_C == columna) {
				continue;
			}
			if (fila > m_nFiles) {
				m_nFiles = fila;
				m_nColumnes = fila;
			}
			if (columna > m_nColumnes) {
				m_nColumnes = columna;
				m_nFiles = columna;
			}
			pushBack(fila, columna, 1);
			last_F = fila;
			last_C = columna;
		}
	}else {
		cout << "Error obrin arxiu" << endl;
	}
	file.close();
}

//TODO: En teoria funciona. falta provar
void MatriuSparse::calculaGrau(vector<int>& k) {
	k.clear();
	k.resize(m_fila.size(), 0);
	for (int i = 0; i < m_fila.size(); i++) {
		k[m_fila[i]]++;
	}
}

//TODO:
void MatriuSparse::calculaDendograms(vector<Tree<double>*> Dendrograms) {

}

bool MatriuSparse::cercaPosicio(int fila, int columna) {
	bool trobat = false;
	vector<int>::iterator it_fila = m_fila.begin();
	vector<int>::iterator it_columna = m_columna.begin();
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
	vector<int>::iterator it_fila = m_fila.begin();
	vector<int>::iterator it_columna = m_columna.begin();
	vector<float>::iterator it_valor = m_valor.begin();
	while (it_fila != m_fila.end() && !trobat) {
		if (*it_fila == fila && *it_columna == columna) {
			trobat = true;
			valor = *it_valor;
			//cout << "Trobat Valor es: " << valor << endl;
		}else {
			it_fila++;
			it_columna++;
			it_valor++;
		}
	}
	return trobat;
}

bool MatriuSparse::cercaPosicio(int fila, int columna, vector<int>::iterator& it_fila, vector<int>::iterator& it_columna) {
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

bool MatriuSparse::cercaPosicio(int fila, int columna, vector<float>::iterator& it_valor) {
	bool trobat = false;
	vector<int>::iterator it_fila = m_fila.begin();
	vector<int>::iterator it_columna = m_columna.begin();
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
				//cout << "no trobat" << endl;
				valor = 0;
			}
		}
	}catch (const char* e) {
		cout << e << endl;
		return false;
	}
	//cout << "trobat" << endl;
	return true;
}

void MatriuSparse::setVal(int fila, int columna, float valor) {
	insertVal(fila, columna, valor);
}

void MatriuSparse::pushBack(int fila, int columna, float valor) {
	m_fila.push_back(fila);
	m_columna.push_back(columna);
	m_valor.push_back(valor);
}


void MatriuSparse::insertVal(int fila, int columna, float valor) {
	if (valor != 0) {
		if (m_fila.size() == 0) {
			pushBack(fila, columna, valor);
			return;
		}
		if (fila > m_nFiles) {
			m_nFiles = fila;
			m_nColumnes = fila;
		}
		if (columna > m_nColumnes) {
			m_nColumnes = columna;
			m_nFiles = columna;
		}
		//cout << "Fila: " << fila << "	Columna: " << columna << endl;
		if ((fila > m_nFiles)) {
			//El nou valor esta fora de la matriu i per tant no cal buscar si existeix
			//automaticament es l'ultim element ja que no hi ha cap mes gran
			pushBack(fila, columna, valor);
		}
		else {
			int ini = 0, fi = m_fila.size(), centre = m_fila.size() / 2;
			while (ini <= fi) {
				centre = ini + (fi - ini) / 2;
				//cout << "Ini: " << ini << "		Center: " << centre << "	Fi: " << fi << endl;
				
				if (fila > m_fila[centre]) {
					ini = centre + 1;
				}else if (fila < m_fila[centre]) {
					fi = centre - 1;
				}else {
					if (columna > m_columna[centre]) {
						ini = centre + 1;
					}else if (columna < m_columna[centre]) {
						fi = centre - 1;
					}else {
						//s'ha trobat l'element i assigna nou valor

						//cout << "Canviant valor" << endl << endl;
						m_valor[centre] = valor;
						break;
					}
				}

				if (ini == fi) {
					//No s'ha trobat l'element i insereix nou valor

					int offset = 0;
					//La funcio insert insereix en pos -1 
					//quan fi == centre - 1 fa que insereixi una posicio abans del que toca
					//offset soluciona aquest problema
					if (columna > m_columna[centre] || centre> fi){
						offset = 1;
					}

					//cout << "Inserint nou element";
					vector<int>::iterator itF = m_fila.begin();
					vector<int>::iterator itC = m_columna.begin();
					vector<float>::iterator itV = m_valor.begin();
					m_fila.insert(itF + ini + offset, fila);
					m_columna.insert(itC + ini + offset, columna);
					m_valor.insert(itV + ini + offset, valor);
					//cout << endl << endl;
					break;
				}
				if (fi < 0) {
					m_fila.insert(m_fila.begin(), fila);
					m_columna.insert(m_columna.begin(), columna);
					m_valor.insert(m_valor.begin(), valor);
				}
			}
		}
	}
}


MatriuSparse& MatriuSparse::operator=(MatriuSparse& matriu) {
	m_nFiles = matriu.m_nFiles;
	m_nColumnes = matriu.m_nColumnes;
	if (matriu.buida()) {
		buidarLlistes();
	}
	else {
		copiarLlistes(matriu);
	}
	return matriu;
}

void MatriuSparse::copiarLlistes(MatriuSparse& m) {
	buidarLlistes();
	vector<int>::iterator it_fila = m.m_fila.begin();
	vector<int>::iterator it_columna = m.m_columna.begin();
	vector<float>::iterator it_valor = m.m_valor.begin();
	while (it_fila != m.m_fila.end()) {
		m_fila.push_back(*it_fila);
		m_columna.push_back(*it_columna);
		m_valor.push_back(*it_valor);

		it_fila++;
		it_columna++;
		it_valor++;
	}
}

MatriuSparse& MatriuSparse::operator*(float n) {
	try {
		if (n == 0) { throw "Multiplicant per zero"; }

		MatriuSparse* M = new MatriuSparse();

		M->m_nFiles = m_nFiles;
		M->m_nColumnes = m_nColumnes;

		vector<int>::iterator it_fila = m_fila.begin();
		vector<int>::iterator it_columna = m_columna.begin();
		vector<float>::iterator it_valor = m_valor.begin();

		while (it_fila != m_fila.end()) {
			M->pushBack(*it_fila, *it_columna, (*it_valor) * n);
			it_fila++;
			it_columna++;
			it_valor++;
		}

		return *M;
	}catch (const char* e) {
		cout << e << endl;
		//tots els valors de la matriu son zero per tant no es guarda res en les llistes
		//pero es conserven les dimensions de la matriu
		
		//buidarLlistes();

		MatriuSparse* M = new MatriuSparse();

		return *M;
	}
}

vector<float>& MatriuSparse::operator*(vector<float>& v) {

	try {
		if (v.size() != getNFiles()) {
			throw "Error. Producte amb vector";
		}
		vector<float>* u = new vector<float>(getNFiles());

		vector<int>::iterator i = m_fila.begin();
		vector<float>::iterator it_valor = m_valor.begin();

		while (i != m_fila.end()) {

			(*u)[*i] += *it_valor * (v[*i]);

			i++;
			it_valor++;
		}

		return *u;
	}
	catch (const string& e) {
		cout << e << endl;
		return v;
	}
}

MatriuSparse& MatriuSparse::operator/(float n) {
	try {

		if (n == 0){
			throw "Divident es zero";
		}

		MatriuSparse* M = new MatriuSparse();
		M->m_nFiles = m_nFiles;
		M->m_nColumnes = m_nColumnes;
		vector<int>::iterator it_fila = m_fila.begin();
		vector<int>::iterator it_columna = m_columna.begin();
		vector<float>::iterator it_valor = m_valor.begin();

		while (it_fila != m_fila.end()) {
			M->pushBack(*it_fila, *it_columna, (*it_valor) / n);
			it_fila++;
			it_columna++;
			it_valor++;
		}

		return *M;
	}catch (const char* e) {
		cout << e << endl;
		MatriuSparse* M = new MatriuSparse();

		return *M;
	}
}

ostream& operator<<(ostream& os, const MatriuSparse& mD) {

	vector<int>::const_iterator it_fila = mD.m_fila.begin();
	vector<int>::const_iterator it_columna = mD.m_columna.begin();
	vector<float>::const_iterator it_valor = mD.m_valor.begin();

	os << "MATRIU DE (FILES: " << mD.getNFiles() << "  COLUMNES: " << mD.getNColumnes() << " )" << endl;
	os << "VALORS (FILA::COL::VALOR)" << endl;
	while (it_valor != mD.m_valor.end()) {
		os << "( " << *(it_fila) << " :: " << *(it_columna) << " :: " << *(it_valor) << " ) " << endl;
		it_valor++;
		it_fila++;
		it_columna++;
	}
	return os;
}
