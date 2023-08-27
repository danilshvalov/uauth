#pragma once

#include <yauth/client.hpp>

#include <userver/components/loggable_component_base.hpp>

namespace yauth {

class YauthClient : public userver::components::LoggableComponentBase {
 public:
  static constexpr std::string_view kName = "yauth-client";

  YauthClient(const userver::components::ComponentConfig&,
              const userver::components::ComponentContext&);

  [[nodiscard]] Client& GetClient() const;

  static userver::yaml_config::Schema GetStaticConfigSchema();

 private:
  std::unique_ptr<Client> client_;
};

}  // namespace yauth
