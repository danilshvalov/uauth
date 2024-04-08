#pragma once

#include <ya_auth/client.hpp>

#include <userver/components/loggable_component_base.hpp>

namespace ya_auth {

class YaAuthClient : public userver::components::LoggableComponentBase {
 public:
  static constexpr std::string_view kName = "ya-auth-client";

  YaAuthClient(const userver::components::ComponentConfig&,
              const userver::components::ComponentContext&);

  [[nodiscard]] Client& GetClient() const;

  static userver::yaml_config::Schema GetStaticConfigSchema();

 private:
  std::unique_ptr<Client> client_;
};

}  // namespace ya_auth
