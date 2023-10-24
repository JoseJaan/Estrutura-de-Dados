#include <iostream>
#include <string>
#include <cmath>

using namespace std;

const int UMPRIMO = 7;

class noh
{
    friend class lista;
    friend class tabelaHash;

private:
    string chave;
    char tipo;
    int valor;
    noh *proximo;
    noh(const string &c = "", const char &t = 'a', const int &v = 0, noh *prox = NULL) : chave(c), tipo(t), valor(v), proximo(prox) {}
};

class lista
{
    friend class tabelaHash;

private:
    noh *primeiro;               // primeiro nó da lista
    unsigned short numElementos; // quantidade de valores na lista
public:
    lista()
    {
        primeiro = NULL;
        numElementos = 0;
    }
    ~lista()
    {
        noh *aux = primeiro;
        noh *temp;

        while (aux != NULL)
        {
            temp = aux;
            aux = aux->proximo;
            delete temp;
        }

        numElementos = 0;
        primeiro = NULL;
    }
    unsigned short tamanho() { return numElementos; }

    void insere(const string &c, const char &t, const int &v)
    {
        noh *novo = new noh(c, t, v);

        if (numElementos == 0)
        {
            primeiro = novo;
        }
        else
        {
            novo->proximo = primeiro;
            primeiro = novo;
        }
        numElementos += 1;
    }

    bool remove(const string &c)
    {
        noh *ultimo = NULL;
        noh *aux = primeiro;

        while (aux->chave != c and aux != NULL)
        {
            ultimo = aux;
            aux = aux->proximo;
        }
        if (aux == primeiro)
        {
            primeiro = aux->proximo;
        }
        else
        {
            ultimo->proximo = aux->proximo;
        }
        delete aux;

        numElementos--;

        if (numElementos == 0)
        {
            primeiro = NULL;
        }
        return true;
    }

    bool busca(const string &c, char &tipoBuscado, int &valorBuscado)
    {

        noh *aux = primeiro;
        int posAux = 0;

        while (aux != NULL)
        {
            if (aux->chave == c)
            {
                tipoBuscado = aux->tipo;
                valorBuscado = aux->valor;
                return true;
            }
            posAux++;
            aux = aux->proximo;
        }
        valorBuscado = -1;
        return false;
    }

    bool verificaOcorrencia(const string &c)
    {
        noh *aux = primeiro;

        while (aux != NULL)
        {
            if (aux->chave == c)
            {
                return true;
            }
            aux = aux->proximo;
        }
        return false;
    }

    void imprime()
    {
        noh *atual = primeiro;
        while (atual != NULL)
        {
            cout << "[" << atual->chave << "/"
                 << atual->valor << "]";
            atual = atual->proximo;
        }
    }
};

class tabelaHash
{
private:
    lista *tabela;
    unsigned numPosicoes;
    // converte uma chave (string) num endereço da tabela
    // - versão simples
    unsigned funcaoHash(const string &s)
    {
        return funcaoHash(s, numPosicoes);
    }
    // converte uma chave (string) num endereço da tabela
    // - versão para redimensionamento
    unsigned funcaoHash(const string &s, int cap)
    {
        unsigned pos = 0;
        for (unsigned int i = 0; i < s.size(); ++i)
            pos = (UMPRIMO * pos + s[i]) % cap;
        return pos;
    }

public:
    // construtor padrão
    tabelaHash(unsigned cap = 100)
    {
        numPosicoes = cap;
        tabela = new lista[cap];
    }
    ~tabelaHash()
    {
        delete[] tabela;
    }

    bool insere(const string &c, char &t, const int &v)
    {
        int aux = funcaoHash(c);

        if (tabela[aux].verificaOcorrencia(c))
        {
            return false;
        }
        tabela[aux].insere(c, t, v);

        cout << "chave '" << c << "' inserida na posicao " << aux << endl;

        return true;
    }

    bool valor(const string &c, char &tipoBuscado, int &valorRetorno)
    {
        int pos = funcaoHash(c);
        tabela[pos].busca(c, tipoBuscado, valorRetorno);
        if (valorRetorno != -1)
        {
            return true;
        }
        return false;
    }

    bool remove(const string &c)
    {
        int aux = funcaoHash(c);
        char tipo;
        int valor;

        if (this->valor(c, tipo, valor))
        {
            tabela[aux].remove(c);
            return true;
        }
        return false;
    }

    void imprime()
    {
        for (unsigned i = 0; i < numPosicoes; i++)
        {
            cout << i << ": ";
            tabela[i].imprime();
            cout << endl;
        }
    }
};

int main()
{
    int tamanhoTH;
    cin >> tamanhoTH;
    tabelaHash tabela(tamanhoTH);
    char comando;
    string chave;
    char tipo = 'a';
    int valor = -1;
    do
    {
        try
        {
            cin >> comando;
            switch (comando)
            {
            case 'i': // inserir
                cin >> chave >> tipo >> valor;
                if (not tabela.insere(chave, tipo, valor))
                    cout << "Erro na inserção: chave já existente!" << endl;
                break;
            case 'r': // remover
                cin >> chave;
                if (not tabela.remove(chave))
                    cout << "Erro na remoção: chave não encontrada!" << endl;
                break;
            case 'l': // remover
                cin >> chave;
                if (not tabela.valor(chave, tipo, valor))
                    cout << "Erro na busca: chave não encontrada!" << endl;
                else
                    cout << "Tipo: " << tipo << " Valor: " << valor << endl;
                break;
            case 'p': // mostrar estrutura
                tabela.imprime();
                break;

            case 'f': // finalizar
                // checado no do-while
                break;
            default:
                cerr << "comando inválido\n";
            }
        }
        catch (runtime_error &e)
        {
            cout << e.what() << endl;
        }
    } while (comando != 'f'); // finalizar execução
    tabela.imprime();
    cout << endl;
    return 0;
}