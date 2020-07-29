#include "Trie.hh"

int Trie::get_frequency() const {
    return frequency_;
}

const std::map<char, Trie *> &Trie::get_children() const {
    return children_;
}

void Trie::insert(std::string word, int frequency) {
    if (word == "") {
        this->frequency_ = frequency;
        return;
    }
    char current = word[0];
    Trie *child = this->get_child(current);
    if (child == NULL) {
        Trie *new_node = new Trie();
        auto pair = std::pair<char, Trie*>(current,new_node);
        this->children_.insert(pair);

        new_node->insert(word.substr(1), frequency);
    } else {
        child->insert(word.substr(1), frequency);
    }
}

Trie *Trie::get_child(char key) {
    auto child = this->children_.find(key);
    if (child != this->children_.end())
        return child->second;
    return NULL;
}
