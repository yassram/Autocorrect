#ifndef AUTOCORRECT_TRIE_HH
#define AUTOCORRECT_TRIE_HH

#include <map>
#include <string>

///
///
///
class Trie {
private:
    int frequency_ = 0;
    std::map<char, Trie*> children_;

public:
    Trie(){}
    ~Trie(){
        for(auto it = children_.begin(); it != children_.end(); ++it)
            delete it->second;
    }

    int getFrequency() const;
    const std::map<char, Trie *> &getChildren() const;
    Trie *getChild(char key);

///
/// \param word
/// \param frequency
    void insert(std::string word, int frequency);
};



#endif //AUTOCORRECT_TRIE_HH
