#ifndef AUTOCORRECT_TRIE_HH
#define AUTOCORRECT_TRIE_HH

#include <map>
#include <string>

/**
 * @class Trie
 *
 * @brief The Trie data structure
 *
 * a Trie is an ordered tree data structure (used for searching)
 * which stores keys and values (the keys are usually strings)
 */
class Trie {
private:
    int frequency_ = 0; /**< if a word is formed, its frequency of apparition */
    std::map<char, Trie*> children_; /**< the children of the node */

public:
    /**
     * @brief constructor of the Trie class
     */
    Trie(){}
    /**
     * @brief destructor of the Trie class
     */
    ~Trie(){
        for(auto it = children_.begin(); it != children_.end(); ++it)
            delete it->second;
    }

    /**
     * @brief frequency getter
     */
    int get_frequency() const;
    /**
     * @brief children getter
     */
    const std::map<char, Trie *> &get_children() const;
    /**
     * @brief single child getter from a key
     *
     * @param key the key to find the node in the map
     * @return the node
     */
    Trie *get_child(char key);

    /**
     * @brief given a frequency and a word, insert it in the trie
     *
     * @param word the word we want to insert in our trie
     * @param frequency of apparition
     */
    void insert(std::string word, int frequency);
};



#endif //AUTOCORRECT_TRIE_HH
