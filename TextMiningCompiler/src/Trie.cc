#include "Trie.hh"

int Trie::getFrequency() const {
    return frequency_;
}

const std::map<char, Trie *> &Trie::getChildren() const {
    return children_;
}

void Trie::setFrequency(int frequency) {
    frequency_ = frequency;
}

void Trie::setChildren(const std::map<char, Trie *> &children) {
    children_ = children;
}

void Trie::insert(std::string word, int frequency) {
    if (word == "") {
        this->frequency_ = frequency;
        return;
    }
    char current = word[0];
    Trie *child = this->getChild(current);
    if (child == NULL) {
        Trie *new_node = new Trie();
        auto pair = std::pair<char, Trie*>(current,new_node);
        this->children_.insert(pair);

        new_node->insert(word.substr(1), frequency);
    } else {
        child->insert(word.substr(1), frequency);
    }
}

Trie *Trie::getChild(char key) {
    auto child = this->children_.find(key);
    if (child != this->children_.end())
        return child->second;
    return NULL;
}
