#ifndef TEST_1_STOP_WORD_H
#define TEST_1_STOP_WORD_H
#include <string>
#include <unordered_set>
#include <fstream>

class StopWord {
public:
    static std::string words_path_;
    void load_txt();


    int read_words(const std::string &filepath, std::unordered_set<std::string> &word_list);

    bool in_stop_word_list(const std::string& word);

    bool in_sa_stop_word_list(const std::string& word);

    bool in_emoji_word_list(const std::string& word);

    void init(const std::string& words_path) {
        words_path_ = words_path;
        load_txt();
    }

private:
    std::unordered_set<std::string> _stop_words;
    std::unordered_set<std::string> _sa_stop_words;
    std::unordered_set<std::string> _emoji_words;
};


#endif //TEST_1_STOP_WORD_H
