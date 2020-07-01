#include "services/http/HelloHandler.h"

#include "boost/beast/http.hpp"
#include "glog/logging.h"
#include "nlohmann/json.hpp"
#include "services/http/HttpUtils.h"
#include <unordered_map>

using json = nlohmann::json;

namespace beast_http = boost::beast::http;

namespace service{
namespace http{
    void handle(std::shared_ptr<HttpSession> session){
        std::unordered_map<std::string, std::string> resp = {
            {"message", "hello, world"},
            {"status", "completed"},
            {"path", session->getRequest().target().to_string()}
        };
        json jsonResult(resp);
        session->respond(HttpUtils::buildJsonResponse(session, jsonResult.dump()));
    }
}// namespace http
}// namespace services