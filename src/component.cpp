#include <ya_auth/component.hpp>

#include <userver/clients/http/component.hpp>
#include <userver/components/component_config.hpp>
#include <userver/components/component_context.hpp>
#include <userver/storages/secdist/component.hpp>
#include <userver/utils/string_to_duration.hpp>
#include <userver/yaml_config/merge_schemas.hpp>

namespace ya_auth {

YaAuthClient::YaAuthClient(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context
)
    : LoggableComponentBase(config, context) {
  ClientConfig client_config;
  client_config.timeout =
      userver::utils::StringToDuration(config["http-timeout"].As<std::string>()
      );
  client_config.retries = config["http-retries"].As<int>();
  auto stage_filepath =
      config["configs-stage-filepath"].As<std::optional<std::string>>();
  client_config.ya_auth_url = config["ya_auth-url"].As<std::string>();

  client_ = std::make_unique<Client>(
      context.FindComponent<userver::components::HttpClient>().GetHttpClient(),
      client_config
  );
}

Client& YaAuthClient::GetClient() const { return *client_; }

userver::yaml_config::Schema YaAuthClient::GetStaticConfigSchema() {
  return userver::yaml_config::MergeSchemas<LoggableComponentBase>(R"(
type: object
description: Component that starts a yandex auth client.
additionalProperties: false
properties:
    ya_auth-url:
        type: string
        description: HTTP URL to request yandex auth data
    http-timeout:
        type: string
        description: HTTP request timeout to the remote in utils::StringToDuration() suitable format
    http-retries:
        type: integer
        description: string HTTP retries before reporting the request failure
)");
}

}  // namespace ya_auth
