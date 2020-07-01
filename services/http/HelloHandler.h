#pragma once

#include "services/http/HttpRequestHandler.h"
#include <memory>

namespace services {
namespace http {
    class HellowHandler : public HttpRequestHandler {
        public:
         void handle(std::shared_ptr<HttpSession> session) override;
    };
}
}