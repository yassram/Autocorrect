#ifndef AUTOCORRECT_TRIE_HH
#define AUTOCORRECT_TRIE_HH

#include <map>
#include <string>

class Trie {
private:
    int frequency_ = 0;
    std::map<char, Trie*> children_;

public:
    Trie(){}
    ~Trie(){}

    int getFrequency() const;

    const std::map<char, Trie *> &getChildren() const;

    void setFrequency(int frequency);

    void setChildren(const std::map<char, Trie *> &children);

    Trie *getChild(char key);

    void insert(std::string word, int frequency);

};



#endif //AUTOCORRECT_TRIE_HH
