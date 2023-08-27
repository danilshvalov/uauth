#include <yauth/models/user_info.hpp>

#include <userver/formats/json/value.hpp>
#include <userver/formats/parse/common_containers.hpp>
#include <userver/utils/trivial_map.hpp>

namespace yauth {

namespace {

namespace json = userver::formats::json;

const userver::utils::TrivialBiMap kUserSexToString = [](auto selector) {
  return selector()
      .Case("male", UserSex::kMale)
      .Case("female", UserSex::kFemale);
};

std::optional<UserEmail> ParseUserEmail(const json::Value& value) {
  if (!value.HasMember("default_email")) {
    return std::nullopt;
  }
  return UserEmail{
      value["default_email"].As<std::string>(),
      value["emails"].As<std::vector<std::string>>(),
  };
}

std::optional<UserAvatar> ParseUserAvatar(const json::Value& value) {
  if (!value.HasMember("default_avatar_id")) {
    return std::nullopt;
  }
  return UserAvatar{
      value["default_avatar_id"].As<std::string>(),
      value["is_avatar_empty"].As<bool>(),
  };
}

std::optional<UserNames> ParseUserNames(const json::Value& value) {
  if (!value.HasMember("first_name")) {
    return std::nullopt;
  }
  return UserNames{
      value["first_name"].As<std::string>(),
      value["last_name"].As<std::string>(),
      value["display_name"].As<std::string>(),
      value["real_name"].As<std::string>(),
  };
}

std::optional<UserSex> ParseUserSex(const json::Value& value) {
  if (!value.HasMember("sex")) {
    return std::nullopt;
  }

  const auto& sex = value["sex"];
  if (sex.IsNull()) {
    return UserSex::kUnknown;
  }

  return kUserSexToString.TryFind(sex.As<std::string>())
      .value_or(UserSex::kUnknown);
}

}  // namespace

UserPhone Parse(const userver::formats::json::Value& value,
                userver::formats::parse::To<UserPhone>) {
  return UserPhone{
      value["id"].As<uint64_t>(),
      value["number"].As<std::string>(),
  };
}

UserInfo Parse(const userver::formats::json::Value& value,
               userver::formats::parse::To<UserInfo>) {
  return UserInfo{
      value["login"].As<std::string>(),
      value["id"].As<std::string>(),
      value["client_id"].As<std::string>(),
      value["psuid"].As<std::string>(),
      ParseUserEmail(value),
      ParseUserAvatar(value),
      value["birthday"].As<std::optional<std::string>>(),
      ParseUserNames(value),
      ParseUserSex(value),
      value["default_phone"].As<std::optional<UserPhone>>(),
  };
}

}  // namespace yauth
