#include "services/http/recommender/LexicalRecommender.h"
#include <algorithm>

namespace services {
namespace http {
namespace recommender {

std::vector<data_source::QueryResult> LexicalRecommender::recommend(const std::string &key) {
  std::vector<data_source::QueryResult> result = getDataSource()->query(key);
  std::sort(result.begin(), result.end(), 
  [](const data_source::QueryResult& q1, const data_source::QueryResult& q2){
      return q1.title < q2.title;
  });
  return result;
}

} // namespace recommender
} // namespace http
} // namespace services