#include "Trie.hpp"


//-------------------- TrieNode --------------------
TrieNode::TrieNode() {
    this->isEndOfTitle = false;
    this->game = nullptr;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        this->children[i] = nullptr;
    }
}

TrieNode::~TrieNode() {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (this->children[i] != nullptr) {
            delete this->children[i];
        }
    }
}


//-------------------- Trie --------------------
Trie::Trie() {
    this->root = new TrieNode();
}

Trie::~Trie() {
    delete this->root;
}

std::string Trie::toSearchKey(std::string text) {
    std::string key = "";
    for (char c : text) {
        // Ignora espacos
        if (c == ' ') {
            continue;
        }

        // Converte letras maiusculas para minusculas usando ASCII
        if (c >= 'A' && c <= 'Z') {
            c = c + ('a' - 'A');
        }

        // So adiciona na chave se for letra minuscula ou numero
        if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
            key += c;
        }
    }
    return key;
}

bool Trie::insert(Game* game) {
    if (game == nullptr) return false;

    // Gera a chave de busca usando o titulo do jogo
    std::string key = toSearchKey(game->getTitle());
    TrieNode* current = this->root;

    // Percorre cada caractere da chave
    for (char c : key) {
        int index = 0;
        
        // Mapeia 'a'-'z' para 0-25 e '0'-'9' para 26-35
        if (c >= 'a' && c <= 'z') {
            index = c - 'a';
        } else if (c >= '0' && c <= '9') {
            index = (c - '0') + 26; 
        }

        // Cria um novo node se o caminho ainda nao existir
        if (current->children[index] == nullptr) {
            current->children[index] = new TrieNode();
        }
    
        // Avanca para o proximo node
        current = current->children[index];
    }

    // Marca o final do titulo e salva o ponteiro do jogo
    current->isEndOfTitle = true;
    current->game = game;

    return true;
}

bool Trie::contains(std::string title) {
    // Gera a chave de busca usando o titulo informado
    std::string key = toSearchKey(title);
    TrieNode* current = this->root;

    // Percorre cada caractere da chave na Trie
    for (char c : key) {
        int index = 0;
        
        // Mapeia 'a'-'z' para 0-25 e '0'-'9' para 26-35
        if (c >= 'a' && c <= 'z') {
            index = c - 'a';
        } else if (c >= '0' && c <= '9') {
            index = (c - '0') + 26; 
        }

        // Se o caminho nao existe, o titulo nao esta na Trie
        if (current->children[index] == nullptr) {
            return false;
        }
        
        // Avanca para o proximo no
        current = current->children[index];
    }

    // Verifica se chegou ao fim de um titulo valido
    return current->isEndOfTitle;
}


// Metodo auxiliar para percorrer a subarvore e coletar os jogos
void Trie::collectGames(TrieNode* node, std::vector<Game*>& results) {
    if (node == nullptr) return;

    if (node->isEndOfTitle && node->game != nullptr) {
        results.push_back(node->game);
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i] != nullptr) {
            collectGames(node->children[i], results);
        }
    }
}

std::vector<Game*> Trie::autocomplete(std::string prefix, int k) {
    std::vector<Game*> results;
    
    if (k <= 0) return results;

    std::string key = toSearchKey(prefix);
    TrieNode* current = this->root;

    // Desce na arvore seguindo o prefixo
    for (char c : key) {
        int index = 0;
        if (c >= 'a' && c <= 'z') {
            index = c - 'a';
        } else if (c >= '0' && c <= '9') {
            index = (c - '0') + 26; 
        }

        if (current->children[index] == nullptr) {
            return results; // Prefixo nao encontrado
        }
        current = current->children[index];
    }

    // Coleta todos os jogos a partir do no do prefixo
    collectGames(current, results);

    // Ordena os resultados conforme as regras
    sortResults(results);

    // Retorna apenas ate k resultados
    std::vector<Game*> topK;
    for (int i = 0; i < k && i < results.size(); i++) {
        topK.push_back(results[i]);
    }

    return topK;
}

void Trie::sortResults(std::vector<Game*>& games) {
    int n = games.size();
    
    // Implementacao do Insertion Sort
    for (int i = 1; i < n; i++) {
        Game* keyGame = games[i];
        int j = i - 1;

        int keyPop = keyGame->getPopularity();
        std::string keyStr = toSearchKey(keyGame->getTitle());

        // Move os elementos que sao "menores" nos criterios de ordenacao
        // para uma posicao a frente de sua posicao atual
        while (j >= 0) {
            int currentPop = games[j]->getPopularity();
            std::string currentStr = toSearchKey(games[j]->getTitle());

            bool shouldMove = false;
            
            // Popularidade maior vem primeiro
            if (currentPop < keyPop) {
                shouldMove = true;
            } 
            // Desempate pela ordem alfabetica da chave de busca
            else if (currentPop == keyPop && currentStr > keyStr) {
                shouldMove = true;
            }

            if (shouldMove) {
                games[j + 1] = games[j];
                j--;
            } else {
                break;
            }
        }
        games[j + 1] = keyGame;
    }
}
