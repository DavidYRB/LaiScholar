#pragma once

#include "services/http/HttpRequestHandler.h"
#include <memory>

namespace services {
namespace http {
    class HelloHandler : public HttpRequestHandler {
        public:
         void handle(std::shared_ptr<HttpSession> session) override;
    };
}
}