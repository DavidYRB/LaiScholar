#include "services/http/SearchHandler.h"

#include "boost/beast/http.hpp"
#include "glog/logging.h"
#include "nlohmann/json.hpp"
#include "services/http/HttpUtils.h"
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

namespace services {
namespace http {

SearchHandler::SearchHandler(
    std::unique_ptr<recommender::Recommender> recommender)
    : recommender_(std::move(recommender)) {}

void SearchHandler::handle(std::shared_ptr<HttpSession> session) {
  // TODO(HOMEWORK-1): ADD YOUR CODE HERE.
  // get key and see if the input is valid
  // use recommender to pass key and use the return of the recommender to session
  const auto &jsonBody = session->getRequest().body();
  try{
    auto obj = nlohmann::json::parse(jsonBody);
    nlohmann::json jsonResponse;
    std::string responseStr{""};
    std::string key{""};
    key = obj["search_key"].get<std::string>();
    std::vector<data_source::QueryResult> responseVec = recommender_->recommend(key);
    for(auto entity : responseVec){
      nlohmann::json temp;
      temp += nlohmann::json::object_t::value_type("citation", entity.citation);
      temp += nlohmann::json::object_t::value_type("title", entity.title);
      jsonResponse.push_back(temp);
    }
    if(jsonResponse.empty()){
      responseStr = "[]";
    }
    else{
      responseStr += jsonResponse.dump();
    }
    session->respond(services::http::HttpUtils::buildJsonResponse(session, std::move(responseStr)));
  }
  catch (nlohmann::json::parse_error& e){
    std::cout << "error : " <<e.what() << '\n';
    std::string errormsg = "Invalid JSON body: " + jsonBody;
    session->respond(services::http::HttpUtils::buildErrorResponse(session, boost::beast::http::status::unknown, std::move(errormsg)));
  }
}
} // namespace http
} // namespace services
