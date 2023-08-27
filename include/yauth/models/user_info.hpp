#pragma once

#include <chrono>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

#include <userver/formats/json_fwd.hpp>

namespace yauth {

struct UserEmail {
  std::string default_email;
  std::vector<std::string> emails;

  bool operator==(const UserEmail& other) const {
    return std::tie(default_email, emails) ==
           std::tie(other.default_email, other.emails);
  }
};

struct UserAvatar {
  std::string id;
  bool is_empty;

  bool operator==(const UserAvatar& other) const {
    return std::tie(id, is_empty) == std::tie(other.id, other.is_empty);
  }
};

struct UserNames {
  std::string first_name;
  std::string last_name;
  std::string display_name;
  std::string real_name;

  bool operator==(const UserNames& other) const {
    return std::tie(first_name, last_name, display_name, real_name) ==
           std::tie(other.first_name, other.last_name, other.display_name,
                    other.real_name);
  }
};

enum class UserSex {
  kMale,
  kFemale,
  kUnknown,
};

struct UserPhone {
  uint64_t id;
  std::string number;

  bool operator==(const UserPhone& other) const {
    return std::tie(id, number) == std::tie(other.id, other.number);
  }
};

struct UserInfo {
  std::string login;
  std::string id;
  std::string client_id;
  std::string psuid;
  std::optional<UserEmail> email;
  std::optional<UserAvatar> avatar;
  std::optional<std::string> birthday;
  std::optional<UserNames> names;
  std::optional<UserSex> sex;
  std::optional<UserPhone> phone;
};

UserInfo Parse(const userver::formats::json::Value& value,
               userver::formats::parse::To<UserInfo>);

}  // namespace yauth
