#include <iostream>
#include "stop_word.h"

std::string StopWord::words_path_;

int StopWord::read_words(const std::string &filepath, std::unordered_set<std::string> &word_list) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        return -1;
    }
    while (!file.eof()) {
        std::string s;
        getline(file, s);
        word_list.insert(s);
    }
    return 0;
}

bool StopWord::in_stop_word_list(const std::string& word) {
    // std::cout<< "in_stop_word_list" << std::endl;
    // for (auto & t:_stop_words) {
        // std::cout<< t << "|";
    // }
    return _stop_words.find(word) != _stop_words.end();
}

bool StopWord::in_sa_stop_word_list(const std::string &word) {
    return _sa_stop_words.find(word) != _sa_stop_words.end();
}

bool StopWord::in_emoji_word_list(const std::string &word) {
    return _emoji_words.find(word) != _emoji_words.end();
}

void StopWord::load_txt() {
    read_words(words_path_ + "/stopwords_v1.txt", _stop_words);
    read_words(words_path_ + "/stop_words.txt", _sa_stop_words);
    read_words(words_path_ + "/emoji.data", _emoji_words);
}