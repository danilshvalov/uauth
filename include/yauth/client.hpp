#pragma once

#include <yauth/models/access_token.hpp>
#include <yauth/models/user_info.hpp>

#include <chrono>
#include <memory>
#include <string>

namespace userver::clients::http {
class Client;
class Response;
}  // namespace userver::clients::http

namespace yauth {

struct ClientConfig {
  std::string yauth_url;
  std::chrono::milliseconds timeout{0};
  int retries{1};
};

class Client final {
 public:
  Client(userver::clients::http::Client& http_client,
         const ClientConfig& config);

  UserInfo FetchUserInfo(const AccessToken& token) const;

 private:
  std::shared_ptr<userver::clients::http::Response> SendRequest(
      const AccessToken& token) const;

  userver::clients::http::Client& http_client_;
  const ClientConfig config_;
};

}  // namespace yauth
