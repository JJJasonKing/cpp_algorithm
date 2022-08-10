#pragma once

#include <mutex>
#include <memory>
#include <string>
#include <algorithm>
#include <unordered_set>
#include "query_ad.h"

std::unique_ptr<cypher::QueryInfo> query_info_;

namespace cypher {
    class QueryInfo;
}

namespace treetargeting {
    class TargetingUserContext {
    public:
        TargetingUserContext();

        ~TargetingUserContext();


        static const cypher::QueryInfo &search_query_info() {
            return *query_info_;
        }
    };
}
