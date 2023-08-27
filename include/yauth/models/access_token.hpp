#pragma once

#include <string>

#include <userver/utils/strong_typedef.hpp>

namespace yauth {

using AccessToken =
    userver::utils::NonLoggable<class AccessTokenTag, std::string>;

}  // namespace yauth
