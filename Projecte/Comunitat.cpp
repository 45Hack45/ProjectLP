#include "Comunitat.h"

Comunitat::Comunitat(MatriuSparse* pMAdj){
	m_primComdeltaQ = -1;
	m_Q = 0;
	m_pMAdj = pMAdj;
}

Comunitat::~Comunitat()
{
	m_pMAdj = nullptr;	
}
void Comunitat::clear()
{
	m_pMAdj = nullptr;
	m_deltaQ.clear();
	m_indexComs.clear();
	m_maxDeltaQFil.clear();
	m_primComdeltaQ=-1;
	m_vDendrograms.clear();
	m_k.clear();
	m_A.clear();
	m_hTotal.clear();
	m_Q=0;
	m_M2=0;	
}

//TODO:
void Comunitat::calculaA(){
	
}

//TODO:
void Comunitat::creaIndexComs(){
	
}
//TODO
void Comunitat::creaDeltaQHeap(){
		
}

//TODO
void Comunitat::modificaVei(int com1, int com2, int vei, int cas){

}

//TODO
void Comunitat::fusiona(int com1, int com2){

}

//TODO
void Comunitat::generaDendrogram(int pos1, int pos2, double deltaQp1p2){

}

//TODO
void Comunitat::calculaComunitats(list<Tree<double>*>& listDendrogram){

}

