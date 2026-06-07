// main.cpp

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "GamesDatabase.hpp"
#include "Trie.hpp"

int main(int argc, char* argv[]) {

    // Verifica a quantidade correta de argumentos
    if (argc != 3) {
        std::cout << "Usage: ./app k prefix" << std::endl;
        return 1;
    }

    // Lê os argumentos da linha de comando
    int k = std::atoi(argv[1]);
    std::string prefix = argv[2];

    // Cria a Trie e insere todos os jogos da base de dados
    Trie trie;
    for (int i = 0; i < numberOfGames; i++) {
        trie.insert(&games[i]);
    }

    // Executa a busca por prefixo
    std::vector<Game*> results = trie.autocomplete(prefix, k);

    // Exibe os resultados no formato exato da especificação
    if (results.empty()) {
        std::cout << "No results found" << std::endl;
    } else {
        for (int i = 0; i < (int)results.size(); i++) {
            std::cout << results[i]->getTitle() << " | "
                      << results[i]->getShortDescription() << " | "
                      << results[i]->getPopularity() << std::endl;
        }
    }

    return 0;
}