#include <iostream>
#include <cstdlib>

using namespace std;

struct equipe{
    string nomeEquipe;
    string lider;
    string linguagem; 
    int qtdMembros;
};

class noh {
friend class lista;
private:
    equipe elenco;
    noh* proximo;
public:
    //noh();
    noh(equipe d);
};

noh::noh(equipe d){
    elenco = d;
    proximo = NULL;
}

class lista {
private:
    noh* primeiro;
    noh* ultimo;
    int tamanho;
    void removeTodos();
    void imprimeReversoAux(noh* umNoh);
public:
    lista();
    lista(const lista& umaLista);
    ~lista();
    lista& operator=(const lista& umaLista);  
    inline void insere(equipe elenco);
    void insereNoFim(equipe elenco);
    void insereNoInicio(equipe elenco);
    void insereNaPosicao(int posicao, equipe elenco);
    int procura(string valor);
    void imprime();
    void imprimeReverso();
    inline bool vazia();
    void removeNoFim();
    void removeNoInicio();
};

lista::lista() {
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}

lista::lista(const lista& umaLista) {
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;

    noh* aux = umaLista.primeiro;

    while(aux!=NULL){
        insereNoFim(aux->elenco);
        aux = aux->proximo;
    }
}

lista::~lista( ) {
    removeTodos();
}    

void lista::removeTodos( ) {
    noh* aux = primeiro;
    noh* temp;

    while(aux!=NULL){
        temp = aux;
        aux = aux->proximo;
        delete temp;
    }

    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}    

lista& lista::operator=(const lista& umaLista){
    removeTodos();

    noh* aux = umaLista.primeiro;
    
    while (aux != NULL) {
        insereNoFim(aux->elenco);
        aux = aux->proximo;  
    }
    
    return *this; 
}  

void lista::insereNoFim(equipe elenco) {
    noh * novo = new noh(elenco);

    if(vazia()){
        primeiro = novo;
        ultimo = novo;
    }
    else{
        ultimo->proximo = novo;
        ultimo = novo;
    }
    tamanho++;
}

// insere no início da lista
void lista::insereNoInicio(equipe elenco) {
    noh * novo = new noh(elenco);

    if(vazia()){
        primeiro = novo;
        ultimo = novo;
    }
    else{
        novo->proximo = primeiro;
        primeiro = novo;
    }
    tamanho++;
}

void lista::insereNaPosicao(int posicao, equipe elenco){
    noh * novo = new noh(elenco);

    if((posicao <= tamanho) and (posicao >= 0)){

        if(vazia()){
            primeiro = novo;
            ultimo = novo;
        }
        else if(posicao == 0){
            novo->proximo = primeiro;
            primeiro = novo;
        }
        else if(posicao == tamanho){
            ultimo->proximo = novo;
            ultimo = novo;
        }
        else{
            noh* aux = primeiro;
            int posAux = 0;

            while(posAux < (posicao-1)){
                aux = aux->proximo;
                posAux++;
            }
            novo->proximo = aux->proximo;
            aux->proximo = novo;
        }
        tamanho++;
    }
    else{
        throw runtime_error("Posição Inexistente!");
    }

}

int lista::procura(string valor) {
    if (vazia()) {
        throw runtime_error("Lista vazia!");
    }

    noh* aux = primeiro;
    int posAux = 0;

    while((aux!=NULL) and (aux->elenco.nomeEquipe!=valor)){
        posAux++;
        aux = aux->proximo;
    }

    if(aux==NULL){
        posAux = -1;
        throw runtime_error("Nao encontrado");
    }

    return posAux; 

}

void lista::imprime() {
    if (vazia()) {
        throw runtime_error("Lista vazia!");
    }
    noh* aux = primeiro;

    while(aux!=NULL){
        cout << "(" <<  aux->elenco.nomeEquipe << ", " << aux->elenco.lider << ", " << aux->elenco.linguagem
            << ", " << aux->elenco.qtdMembros << ")" << endl;
        aux = aux->proximo;
    }
    cout << endl; 
}

inline bool lista::vazia() {
    return (primeiro == NULL);
}
   
void lista::removeNoFim() {
    if(vazia()){
        throw runtime_error("Remoção em lista vazia!");
    }

    noh* aux = primeiro;
    noh* anterior;

    while(aux->proximo!=NULL){
        anterior = aux;
        aux = aux->proximo;
    }
    //parou no penultimo

    delete ultimo;
    anterior -> proximo = NULL;
    ultimo = anterior;

    tamanho--;

    if(tamanho == 0){
        primeiro = NULL;
    }
}
    
void lista::removeNoInicio() {
    if(vazia()){
       throw runtime_error("Remoção em lista vazia!");
    }

    noh* aux = primeiro;

    primeiro = primeiro->proximo;

    delete aux;

    tamanho--;

    if(vazia()){
        ultimo = NULL;
    }
}

int main() {
    lista minhaLista;
    equipe info;
    char comando;
    int posicao;
    string nomeEquipe;

    do {
        try {
            cin >> comando;
            switch (comando) {
                case 'i': 
                    cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                    minhaLista.insereNoInicio(info);
                    break;
                case 'h': 
                    cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                    minhaLista.insereNoFim(info);
                    break;             
                case 'm': 
                    cin >> posicao;
                    cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                    minhaLista.insereNaPosicao(posicao,info);
                    break;             
                case 's': 
                    cin >> nomeEquipe;
                    cout << minhaLista.procura(nomeEquipe) <<endl;
                    break;                    
                case 'r':
                    minhaLista.removeNoInicio();
                    break;
                case 'a': 
                    minhaLista.removeNoFim();
                    break;                                   
                case 'p':
                    minhaLista.imprime();
                    break;
                case 'f':
                    break;
                default:
                    cerr << "comando inválido\n";
            }
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    } while (comando != 'f');
    cout << endl;
    return 0;
}
