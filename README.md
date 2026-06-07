# Sistema de Autocomplete de Jogos com Trie

## Descrição do Projeto
Este projeto consiste na implementação de um sistema de **autocomplete de jogos** eletrônicos que utiliza uma **Trie** (Árvore de Prefixos) como estrutura de dados principal. O sistema armazena um catálogo de jogos onde cada item possui título, descrição curta e índice de popularidade. A partir de um prefixo informado e um limite máximo `k`, o programa realiza buscas eficientes por prefixo, retornando as sugestões ordenadas por relevância de acordo com as especificações exigidas.

A busca possui duas propriedades fundamentais:
* **Case-insensitive:** Não há diferenciação entre letras maiúsculas e minúsculas.
* **Remoção de Espaços:** Espaços em branco são ignorados na indexação e na busca, tornando consultas como `"halfl"`, `"half l"` e `"Half L"` equivalentes.

Os resultados obtidos são limitados a no máximo `k` elementos e ordenados de forma decrescente por popularidade. Em cenários de empate na popularidade, o critério de desempate adota a ordem alfabética da chave de busca interna do título do jogo.

## Organização dos Arquivos
A arquitetura do projeto está modularizada de acordo com as exigências do enunciado, dividindo-se nos seguintes arquivos:
* **`main.cpp`**: Arquivo principal encarregado de validar os parâmetros de linha de comando, popular a estrutura da Trie com a base de dados disponível, chamar o método de autocomplete e exibir os jogos retornados nos formatos especificados.
* **`Game.hpp` / `Game.cpp`**: Contém a definição e implementação da classe `Game`, encapsulando as propriedades de cada jogo (`title`, `shortDescription`, `popularity`) e seus métodos de acesso.
* **`Trie.hpp` / `Trie.cpp`**: Contém as declarações e implementações das classes `TrieNode` (os nós individuais da árvore com suporte a alfabeto de tamanho 36) e `Trie` (responsável pelos métodos de inserção, verificação de existência, busca por prefixo e ordenação manual por *Insertion Sort*).
* **`GamesDatabase.hpp` / `GamesDatabase.cpp`**: Estrutura fornecida para o carregamento do catálogo fixo inicial de jogos, evitando a necessidade de leituras de arquivos externos ou inputs interativos.

## Instruções de Compilação
O projeto foi desenvolvido em C++ padrão e pode ser compilado em qualquer terminal compatível via `g++` através do comando abaixo:

```bash
g++ main.cpp Game.cpp Trie.cpp GamesDatabase.cpp -o app
```
## Exemplos de Uso pela Linha de Comando

### 1. Busca comum trazendo até 3 resultados ordenados por popularidade:


``` bash
./app 3 ha
```

### Saída obtida:
``` bash
Hades | Defy the god of the dead as you hack and slash out of the Underworld in this rogue like dungeon crawler from the creators of Bastion Transistor and Pyre | 213542

Halo The Master Chief Collection | The Master Chief s iconic journey includes six games built for PC and collected in a single integrated experience Whether you re a long time fan or meeting Spartan 117 for the first time The Master Chief Collection is the definitive Halo gaming experience | 192219

Halo Infinite | The legendary Halo series returns with the most expansive Master Chief campaign yet and a ground breaking free to play multiplayer experience | 160647
```
### 2. Busca utilizando prefixo composto com espaço e letras maiúsculas:**
``` bash 
./app 3 "Half L"
```
### Saída obtida:
``` bash
Half Life 2 | 1998 HALF LIFE sends a shock through the game industry with its combination of pounding action and continuous immersive storytelling Valve s debut title wins more than 50 game of the year awards on its way to being named Best PC Game Ever by PC Gamer and launches a franchise with more than eight million retail units sold worldwide | 131995

Half Life Alyx | Half Life Alyx is Valve s VR return to the Half Life series It s the story of an impossible fight against a vicious alien race known as the Combine set between the events of Half Life and Half Life 2 Playing as Alyx Vance you are humanity s only chance for survival | 71194

Half Life 2 Episode Two | Half Life 2 Episode Two is the second in a trilogy of new games created by Valve that extends the award winning and best selling Half Life adventure As Dr Gordon Freeman you were last seen exiting City 17 with Alyx Vance as the Citadel erupted amidst a storm of unknown proportions | 28291
```
**3. Busca por prefixo inexistente no catálogo atual:**
``` bash
./app 3 zelda
```
### Saída obtida:
``` bash
No results found
```
**4. Passagem incorreta ou incompleta de parâmetros operacionais:**
./app 3

### Saída obtida:
``` bash
Usage: ./app k prefix
```