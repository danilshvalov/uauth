#include <yauth/client.hpp>

#include <fmt/format.h>
#include <userver/clients/http/client.hpp>
#include <userver/formats/json/value.hpp>
#include <userver/http/header_map.hpp>
#include <userver/http/url.hpp>
#include <userver/storages/secdist/secdist.hpp>

namespace yauth {

namespace {

namespace http = userver::http;
namespace json = userver::formats::json;

}  // namespace

Client::Client(userver::clients::http::Client& http_client,
               const ClientConfig& config)
    : http_client_(http_client), config_(config) {}

UserInfo Client::FetchUserInfo(const AccessToken& token) const {
  auto response = SendRequest(token);
  return json::FromString(response->body()).As<UserInfo>();
}

std::shared_ptr<userver::clients::http::Response> Client::SendRequest(
    const AccessToken& token) const {
  http::headers::HeaderMap headers = {
      {"Authorization", fmt::format("OAuth {}", token.GetUnderlying())},
  };

  return http_client_.CreateRequest()
      .get(config_.yauth_url)
      .headers(headers)
      .retry(config_.retries)
      .timeout(config_.timeout)
      .perform();
}

}  // namespace yauth
