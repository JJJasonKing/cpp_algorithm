#pragma once

#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace cypher {

// 同义词数据结构
    class Syn {
    public:
        std::string str;    // 同义词term
        int64_t id;
        float belief;       // 同义词置信度
    public:
        Syn() : str(""), id(0), belief(0) {
        }

        Syn(int64_t id, float b, const std::string &s = "") : str(s), id(id), belief(b) {
        }
    };

// query
    class QueryInfo {
    public:
        std::string query;

        std::vector<std::string> terms_str;
        std::vector<int64_t> terms;
        std::vector<float> tights;
        std::vector<float> weights;
        std::vector<std::vector<Syn>> syns;

        std::vector<std::string> phrase_terms_str;
        std::vector<float> phrase_weights;
        std::vector<int32_t> phrase_syns_map;

        std::vector<std::string> app_names;

        std::vector<std::string> brand_words; // query识别出来的品牌词
        std::unordered_set<int64_t> mt_brand_word_bidword; // query侧明投bidword

        std::vector<int64_t> traffic_labels; // query侧流量标识
        std::vector<int64_t> query_industry; // query行业标识
        bool hit_special_query; // 圈query监控

        float recency_score;
        int32_t search_type;          //主被动搜索
        std::string search_source;    //搜索来源
        int64_t query_convert_cnt;    // 搜索词上转化数
    public:
        QueryInfo() : recency_score(0) {
            terms_str.clear();
            terms.clear();
            tights.clear();
            weights.clear();
            syns.clear();
            phrase_terms_str.clear();
            phrase_weights.clear();
            phrase_syns_map.clear();
            app_names.clear();
            mt_brand_word_bidword.clear();
            traffic_labels.clear();
        }

        int build(const std::string &query_json);
    };

} // namespace search_rank
