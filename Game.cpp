#include "Game.hpp"

Game::Game() {
    this->title = "";
    this->shortDescription = "";
    this->popularity = 0;
}

Game::Game(std::string title, std::string shortDescription, int popularity) {
    this->title = title;
    this->shortDescription = shortDescription;
    this->popularity = popularity;
}

Game::~Game() { 
    // nao sao feitas alocacoes dinamicas nessa classe
}

std::string Game::getTitle() {
    return this->title;
}

std::string Game::getShortDescription() {
    return this->shortDescription;
}

int Game::getPopularity() {
    return this->popularity;
}