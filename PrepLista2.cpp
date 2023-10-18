#include <iostream>
#include <cstdlib>

using namespace std;

struct acaoPrograma{
    int identificador;
    string nomeAcao;
    int tempoExecucao; 
    int tempoConsumido;
};


class noh {
friend class listadup;
    private: 
        acaoPrograma acao;
        noh* proximo;
        noh* anterior;
    public:

        noh(acaoPrograma d);
};

noh::noh(acaoPrograma d){
    acao = d;
    proximo = NULL;
    anterior = NULL;
}

class listadup {
private:
    noh* primeiro;
    noh* ultimo;
    int tamanho;
    void removeTodos(); 
public:
    listadup();
    listadup(const listadup& umaLista);
    ~listadup();
    listadup& operator=(const listadup& umaLista);  
    void insereNoFim(acaoPrograma acao);
    void insereNoInicio(acaoPrograma acao);
    void insereNaPosicao(int posicao, acaoPrograma acao);
    int procura(string valor);
    void imprime();
    inline bool vazia();
    void removeNoFim();
    void removeNoInicio();
};

listadup::listadup() {
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}

listadup::listadup(const listadup& umaLista) {
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;

    noh* aux = umaLista.primeiro;

    while(aux!=NULL){
        insereNoFim(aux->acao);
        aux = aux->proximo;
    }    
}

listadup::~listadup( ) {
    removeTodos();
}    

void listadup::removeTodos( ) {
    noh *aux = primeiro;
    noh *temp;

    while(aux!=NULL){
        temp = aux;
        aux = aux->proximo;
        delete temp;
    }

    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}    

listadup& listadup::operator=(const listadup& umaLista){
    removeTodos();
    noh* aux = umaLista.primeiro;
    
    while (aux != NULL) {
        insereNoFim(aux->acao);
        aux = aux->proximo;  
    }
    
    return *this; 
}  

void listadup::insereNoFim(acaoPrograma acao) {
    noh *novo = new noh(acao);

    if(vazia()){
        primeiro = novo;
        ultimo = novo;
    }
    else{
        ultimo->proximo = novo;
        novo->anterior = ultimo;
        ultimo = novo;
    }
    tamanho++;
}

void listadup::insereNoInicio(acaoPrograma acao) {
    noh *novo = new noh(acao);

    if(vazia()){
        primeiro = novo;
        ultimo = novo;
    }
    else{
        novo->proximo = primeiro;
        primeiro->anterior = novo;      
        primeiro = novo;
    }
    tamanho++;
}

void listadup::insereNaPosicao(int posicao, acaoPrograma acao){
    noh *novo = new noh(acao);

    if((posicao < tamanho) and (posicao>=0)){
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
            aux->proximo->anterior = novo;
            aux->proximo = novo;
            novo->anterior = aux;
        }
        tamanho++;
    }
    else{
        throw runtime_error("Posição Inexistente!");
    }
}
                   

int listadup::procura(string valor) {
    if(vazia()){
       throw runtime_error("Lista vazia!");
    }
    noh *aux = primeiro;
    int posicao=0;

    while((aux!=NULL) and (aux->acao.nomeAcao!=valor)){
        posicao++;
        aux = aux->proximo;
    }

    if(aux == NULL){
        return -1;
    }
    else{
        return posicao;
    }
}

// método básico que *percorre* uma lista, imprimindo seus elementos
void listadup::imprime() {
    if (vazia()) {
        throw runtime_error("Lista vazia!");
    }
    noh *aux = primeiro;

    //IMPRIMIR NA ORDEM
    while(aux!=NULL){
        cout << "(" << aux->acao.identificador << ", " << aux->acao.nomeAcao << ", " << aux->acao.tempoExecucao
            << ", " << aux->acao.tempoConsumido << ")" << endl; 

        aux = aux->proximo;
    }

    //IMPRIMIR INVERSAMENTE

    cout << "IMPRIMINDO REVERSO" << endl;

    aux = ultimo;

    while(aux!=NULL){
        cout << "(" << aux->acao.identificador << ", " << aux->acao.nomeAcao << ", " << aux->acao.tempoExecucao
            << ", " << aux->acao.tempoConsumido << ")" << endl; 

        aux = aux->anterior;
    }
}

// verifica se a lista está vazia
inline bool listadup::vazia() {
    return (primeiro==NULL);
}

void listadup::removeNoInicio() {
    if(vazia()){
       throw runtime_error("Remoção em lista vazia!");
    }

    noh *aux = primeiro;

    primeiro = primeiro->proximo;

    if(primeiro!=NULL){
        primeiro->anterior = NULL;
    }

    delete aux;

    tamanho--;

    if(vazia()){
        ultimo = NULL;
    }
}


void listadup::removeNoFim() {
    if(vazia()){
       throw runtime_error("Remoção em lista vazia!");
    }

    noh *aux = ultimo;

    ultimo = ultimo->anterior;

    if(ultimo!=NULL){
        ultimo->proximo = NULL;
    }

    delete aux;

    tamanho--;

    if(vazia()){
        ultimo = NULL;
    }
}


int main() {
    listadup minhaLista;
    acaoPrograma info;
    char comando;
    int posicao;
    string nomeEquipe;

    do {
        try {
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    cin >> info.identificador >> info.nomeAcao >> info.tempoExecucao >> info.tempoConsumido;
                    minhaLista.insereNoInicio(info);
                    break;
                case 'h': // inserir
                    cin >> info.identificador >> info.nomeAcao >> info.tempoExecucao >> info.tempoConsumido;
                    minhaLista.insereNoFim(info);
                    break;             
                case 'm': // inserir
                    cin >> posicao;
                    cin >> info.identificador >> info.nomeAcao >> info.tempoExecucao >> info.tempoConsumido;
                    minhaLista.insereNaPosicao(posicao,info);
                    break;             
                case 's': // procurar
                    cin >> nomeEquipe;
                    posicao = minhaLista.procura(nomeEquipe);
                    if(posicao == -1)
                        cout << "Nao encontrado"<< endl;
                    else
                        cout << posicao << endl;
                    break;                    
                case 'r': // remover
                    minhaLista.removeNoInicio();
                    break;
                case 'a': // remover
                    minhaLista.removeNoFim();
                    break;                                   
                case 'p': // limpar tudo
                    minhaLista.imprime();
                    break;
                case 'f': // finalizar
                    // checado no do-while
                    break;
                default:
                    cerr << "comando inválido\n";
            }
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    } while (comando != 'f'); // finalizar execução
    cout << endl;
    return 0;
}
