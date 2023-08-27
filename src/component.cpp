#include <yauth/component.hpp>

#include <userver/clients/http/component.hpp>
#include <userver/components/component_config.hpp>
#include <userver/components/component_context.hpp>
#include <userver/storages/secdist/component.hpp>
#include <userver/utils/string_to_duration.hpp>
#include <userver/yaml_config/merge_schemas.hpp>

namespace yauth {

YauthClient::YauthClient(const userver::components::ComponentConfig& config,
                         const userver::components::ComponentContext& context)
    : LoggableComponentBase(config, context) {
  ClientConfig client_config;
  client_config.timeout = userver::utils::StringToDuration(
      config["http-timeout"].As<std::string>());
  client_config.retries = config["http-retries"].As<int>();
  auto stage_filepath =
      config["configs-stage-filepath"].As<std::optional<std::string>>();
  client_config.yauth_url = config["meteum-url"].As<std::string>();

  client_ = std::make_unique<Client>(
      context.FindComponent<userver::components::HttpClient>().GetHttpClient(),
      client_config);
}

Client& YauthClient::GetClient() const { return *client_; }

userver::yaml_config::Schema YauthClient::GetStaticConfigSchema() {
  return userver::yaml_config::MergeSchemas<LoggableComponentBase>(R"(
type: object
description: Component that starts a meteum client.
additionalProperties: false
properties:
    yauth-url:
        type: string
        description: HTTP URL to request meteum data
    http-timeout:
        type: string
        description: HTTP request timeout to the remote in utils::StringToDuration() suitable format
    http-retries:
        type: integer
        description: string HTTP retries before reporting the request failure
)");
}

}  // namespace yauth
