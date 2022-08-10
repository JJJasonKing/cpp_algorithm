#include <iostream>
#include <vector>
#include <regex>
#include <sys/time.h>
#include "cmath"
#include "stop_word.h"

#define REPEAT_NUM 20000

std::string wstring2string(const std::wstring& wstr) {
    unsigned len = wstr.size() * 4;
    setlocale(LC_CTYPE, "en_US.UTF-8");
    char* p = new char[len + 1];
    wcstombs(p, wstr.c_str(), len);
    p[len] = '\0';
    std::string str1(p);
    delete[] p;
    return str1;
}

std::wstring string2wstring(const std::string& str) {
    unsigned len = str.size();
    setlocale(LC_CTYPE, "en_US.UTF-8");
    wchar_t* p = new wchar_t[len + 1];
    mbstowcs(p, str.c_str(), len);
    p[len] = '\0';
    std::wstring str1(p);
    delete[] p;
    return str1;
}

namespace FillQueryParseRespOp {
    /* 直接传引用比较好吧
    std::vector<std::string> WordsToChar(std::vector<std::string> &clean_terms);
    std::vector<std::string> WordsToNGram(std::vector<std::string> &clean_terms, int n);

    std::vector<std::string> FillQueryParseRespOp::WordsToChar(std::vector<std::string> &clean_terms) {
        std::vector<std::string> res;
        for (std::string &term : clean_terms) {
            for (char &c : term) {
                res.emplace_back(std::to_string(c));
            }
        }
        return res;
    }

    std::vector<std::string> FillQueryParseRespOp::WordsToNGram(std::vector<std::string>& clean_terms, int n) {
        std::vector<std::string> res;
        if (n < 2 || clean_terms.empty()){
            return res;
        }

        return res;
    } */
    void WordsToChar(std::vector<std::string> &clean_terms, std::vector<std::string> &res);
    void WordsToNGram(std::vector<std::string> &clean_terms, int n, std::vector<std::string> &res);
    void WordsToChar2(std::vector<std::string> &clean_terms, std::vector<std::string> &res);
    void WordsToChar3(std::vector<std::string> &clean_terms, std::vector<std::string> &res);
    void cleanQueryWordsV19(std::vector<std::string> &clean_terms, std::vector<std::string> &res);


    void FillQueryParseRespOp::WordsToChar(std::vector<std::string>& clean_terms, std::vector<std::string>& res) {
        for (std::string &term : clean_terms) {
            std::wstring widstr = string2wstring(term);
            /*
            for (int i = 0; i < widstr.size(); ++i) {
                std::cout <<"widstr[i]:"<< wstring2string(&widstr[i]) << " ";
            }*/
            for (wchar_t &c : widstr) {
                std::wstring tmp;
                tmp.push_back(c);
                res.push_back(wstring2string(tmp));
            }
        }
        return;
    }

    void FillQueryParseRespOp::WordsToChar2(std::vector<std::string>& clean_terms, std::vector<std::string>& res) {
        for (std::string &term : clean_terms) {
            std::wstring widstr = string2wstring(term);
            for (int i = 0; i < widstr.size(); ++i) {
                // res.push_back(wstring2string(std::to_wstring(widstr[i])));
                // std::cout <<"widstr[i]:"<< wstring2string(&widstr[i]) << " ";
                res.push_back(wstring2string(widstr.substr(i,1)));
            }
        }
        return;
    }

    void FillQueryParseRespOp::WordsToNGram(std::vector<std::string>& clean_terms, int n, std::vector<std::string>& res) {
        if (n < 2 || clean_terms.empty()){
            return;
        }
        std::string gram;
        for (int i = 0; i < clean_terms.size(); ++i) {
            gram.clear();
            for (int j = n-1; j >= 0; --j) {
                if (i - j < 0) {
                    gram += "<Bos>";
                } else {
                    gram += clean_terms[i-j];
                }
            }
            res.emplace_back(gram);
        }
        gram = clean_terms[clean_terms.size()-1];
        for (size_t i = 1; i < n; ++i) {
            gram += "<Eos>";
        }
        res.emplace_back(gram);
        return;
    }

    void FillQueryParseRespOp::cleanQueryWordsV19(std::vector<std::string> &clean_terms, std::vector<std::string> &res) {
        for (std::string &term : clean_terms) {

        }
    }
} // end of namespace FillQueryParseRespOp

void new_test(std::vector<std::string>& clean_terms, std::vector<std::string>& res) {
    for (std::string &term : clean_terms) {
        std::wstring widstr = string2wstring(term);
        for (wchar_t &c : widstr) {
            std::wstring tmp;
            tmp.push_back(c);
            tmp.clear();
            res.push_back(wstring2string(tmp));
        }
    }
}

//
void clear_test(std::vector<std::string>& clean_terms, std::vector<std::string>& res) {
    std::wstring tmp;
    for (std::string &term : clean_terms) {
        std::wstring widstr = string2wstring(term);
        for (wchar_t &c : widstr) {
            tmp.push_back(c);
            res.push_back(wstring2string(tmp));
            tmp = L"";
            // res.emplace_back(wstring2string(std::to_wstring(c)));
        }
    }
}

int main7() {
    struct timeval sTime, eTime;
    std::vector<double> dd(2);
    std::vector<float> ff;
    ff.push_back(0.1);
    ff.push_back(0.2);
    //dd.push_back(ff[0]);
    dd[0] = ff[0];
    //std::cout << "ff:" << typeid(ff[0]).name() << std::endl;
    //std::cout << "dd:" << typeid(dd[0]).name() << std::endl;
    uint32_t nterms = 2;
    if (dd.size() == nterms)
        std::cout << "true" << std::endl;
    else
        std::cout << "false" << std::endl;
    /*
    string str[10];
    auto a = str[0].c_str();
    string ss = "abc";
    auto b = ss.c_str();*/

    std::vector<std::string> input;
    input.emplace_back("雷霆万钧ab");
    input.emplace_back("加法");
    input.emplace_back("定时发送大V213");
    input.emplace_back("是的");
    input.emplace_back("好");
    input.emplace_back("😁");

    std::cout<< "input:" << std::endl;
    for (std::string& tt : input) {
        std::cout<< tt << " ";
    }

    std::vector<std::string> res;
    std::cout << std::endl << "WordsToChar:" << std::endl;
    // FillQueryParseRespOp::WordsToChar(input, res);
    // clear_test(input,res);
    for (auto& tt : res) {
        printf("res:%s, ",tt.c_str());
    }
    auto tmp = std::move(res);
    res.clear();

    std::cout<< std::endl << std::endl << "WordsToNGram:" << std::endl;
    FillQueryParseRespOp::WordsToNGram(input, 2, res);
    for (std::string& tt : res) {
        std::cout<< tt << " ";
    }

    std::cout<< std::endl << "--------------------" << std::endl;

    /*
    gettimeofday(&sTime, NULL);
    for (int i = 0; i < REPEAT_NUM; ++i) {
        FillQueryParseRespOp::WordsToChar(input, res);
        res.clear();
    }
    gettimeofday(&eTime, NULL);
    long spend_time = (eTime.tv_sec-sTime.tv_sec)*1000000+(eTime.tv_usec-sTime.tv_usec); //exeTime 单位是微秒
    std::cout<< std::endl << "push_spend_time|||||||||:" << spend_time << std::endl;

    gettimeofday(&sTime, NULL);
    for (int i = 0; i < REPEAT_NUM; ++i) {
        FillQueryParseRespOp::WordsToChar2(input, res);
        res.clear();
    }
    gettimeofday(&eTime, NULL);
    spend_time = (eTime.tv_sec-sTime.tv_sec)*1000000+(eTime.tv_usec-sTime.tv_usec); //exeTime 单位是微秒
    std::cout<< std::endl << "substr_spend_time|||||||||:" << spend_time << std::endl;

    gettimeofday(&sTime, NULL);
    for (int i = 0; i < REPEAT_NUM; ++i) {
        clear_test(input, res);
        res.clear();
    }
    gettimeofday(&eTime, NULL);
    spend_time = (eTime.tv_sec-sTime.tv_sec)*1000000+(eTime.tv_usec-sTime.tv_usec); //exeTime 单位是微秒
    std::cout<< std::endl << "clear_test_spend_time|||||||||:" << spend_time << std::endl;

    res.clear();
    FillQueryParseRespOp::WordsToChar2(input, res);
    std::cout<< " --test res substr-- " << std::endl;
    for (auto &t : res) {
        std::cout<< t << "|";
    }*/

    StopWord stop_word;
    stop_word.init("/Users/bytedance/cpp/my_test/test_1/wordlist");
    for (std::string& term:input) {
        if (!stop_word.in_sa_stop_word_list(term) && !stop_word.in_emoji_word_list(term)) {
            std::cout<< term << "|";
        }
    }

}
