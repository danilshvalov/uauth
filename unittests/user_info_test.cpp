#include <ya_auth/models/user_info.hpp>

#include <userver/formats/json/value.hpp>
#include <userver/utest/utest.hpp>

namespace json = userver::formats::json;

struct UserInfoTestData {
  std::string json;
  ya_auth::UserInfo expected;
};

struct UserInfoJsonTest : testing::TestWithParam<UserInfoTestData> {};

UTEST_P(UserInfoJsonTest, ParseTest) {
  const auto [document, expected] = GetParam();
  const auto result = json::FromString(document).As<ya_auth::UserInfo>();

  EXPECT_EQ(result.login, expected.login);
  EXPECT_EQ(result.id, expected.id);
  EXPECT_EQ(result.client_id, expected.client_id);
  EXPECT_EQ(result.psuid, expected.psuid);
  EXPECT_EQ(result.email, expected.email);
  EXPECT_EQ(result.avatar, expected.avatar);
  EXPECT_EQ(result.birthday, expected.birthday);
  EXPECT_EQ(result.names, expected.names);
  EXPECT_EQ(result.sex, expected.sex);
  EXPECT_EQ(result.phone, expected.phone);
}

INSTANTIATE_UTEST_SUITE_P(  //
    UserInfo, UserInfoJsonTest,
    testing::Values(
        UserInfoTestData{
            R"json(
              {
                 "first_name": "Иван",
                 "last_name": "Иванов",
                 "display_name": "ivan",
                 "emails": [
                    "test@yandex.ru",
                    "other-test@yandex.ru"
                 ],
                 "default_email": "test@yandex.ru",
                 "default_phone": {
                    "id": 12345678,
                    "number": "+79037659418"
                 },
                 "real_name": "Иван Иванов",
                 "is_avatar_empty": false,
                 "birthday": "1987-03-12",
                 "default_avatar_id": "131652443",
                 "login": "ivan",
                 "old_social_login": "uid-mmzxrnry",
                 "sex": "male",
                 "id": "1000034426",
                 "client_id": "4760187d81bc4b7799476b42b5103713",
                 "psuid": "1.AAceCw.tbHgw5DtJ9_zeqPrk-Ba2w.qPWSRC5v2t2IaksPJgnge"
              }
            )json",
            ya_auth::UserInfo{
                .login = "ivan",
                .id = "1000034426",
                .client_id = "4760187d81bc4b7799476b42b5103713",
                .psuid =
                    "1.AAceCw.tbHgw5DtJ9_zeqPrk-Ba2w.qPWSRC5v2t2IaksPJgnge",
                .email =
                    ya_auth::UserEmail{
                        .default_email = "test@yandex.ru",
                        .emails = {"test@yandex.ru", "other-test@yandex.ru"},
                    },
                .avatar =
                    ya_auth::UserAvatar{
                        .id = "131652443",
                        .is_empty = false,
                    },
                .birthday = "1987-03-12",
                .names =
                    ya_auth::UserNames{
                        .first_name = "Иван",
                        .last_name = "Иванов",
                        .display_name = "ivan",
                        .real_name = "Иван Иванов",
                    },
                .sex = ya_auth::UserSex::kMale,
                .phone =
                    ya_auth::UserPhone{
                        .id = 12345678,
                        .number = "+79037659418",
                    },
            },
        },
        UserInfoTestData{
            R"json(
              {
                 "login": "ivan",
                 "id": "1000034426",
                 "client_id": "4760187d81bc4b7799476b42b5103713",
                 "default_phone": {
                    "id": 12345678,
                    "number": "+79037659418"
                 },
                 "psuid": "1.AAceCw.tbHgw5DtJ9_zeqPrk-Ba2w.qPWSRC5v2t2IaksPJgnge"
              }
            )json",
            ya_auth::UserInfo{
                .login = "ivan",
                .id = "1000034426",
                .client_id = "4760187d81bc4b7799476b42b5103713",
                .psuid =
                    "1.AAceCw.tbHgw5DtJ9_zeqPrk-Ba2w.qPWSRC5v2t2IaksPJgnge",
                .phone =
                    ya_auth::UserPhone{
                        .id = 12345678,
                        .number = "+79037659418",
                    },
            },
        },
        UserInfoTestData{
            R"json(
              {
                 "first_name": "Иван",
                 "last_name": "Иванов",
                 "display_name": "Ivan",
                 "real_name": "Иван Иванов",
                 "login": "ivan",
                 "old_social_login": "uid-mmzxrnry",
                 "sex": "male",
                 "id": "1000034426",
                 "client_id": "4760187d81bc4b7799476b42b5103713",
                 "psuid": "1.AAceCw.tbHgw5DtJ9_zeqPrk-Ba2w.qPWSRC5v2t2IaksPJgnge"
              }
            )json",
            ya_auth::UserInfo{
                .login = "ivan",
                .id = "1000034426",
                .client_id = "4760187d81bc4b7799476b42b5103713",
                .psuid =
                    "1.AAceCw.tbHgw5DtJ9_zeqPrk-Ba2w.qPWSRC5v2t2IaksPJgnge",
                .names =
                    ya_auth::UserNames{
                        .first_name = "Иван",
                        .last_name = "Иванов",
                        .display_name = "Ivan",
                        .real_name = "Иван Иванов",
                    },
                .sex = ya_auth::UserSex::kMale,
            },
        },
        UserInfoTestData{
            R"json(
              {
                 "login": "ivan",
                 "old_social_login": "uid-mmzxrnry",
                 "birthday": "1987-03-12",
                 "id": "1000034426",
                 "client_id": "4760187d81bc4b7799476b42b5103713",
                 "psuid": "1.AAceCw.tbHgw5DtJ9_zeqPrk-Ba2w.qPWSRC5v2t2IaksPJgnge"
              }
            )json",
            ya_auth::UserInfo{
                .login = "ivan",
                .id = "1000034426",
                .client_id = "4760187d81bc4b7799476b42b5103713",
                .psuid =
                    "1.AAceCw.tbHgw5DtJ9_zeqPrk-Ba2w.qPWSRC5v2t2IaksPJgnge",
                .birthday = "1987-03-12",
            },
        },
        UserInfoTestData{
            R"json(
              {
                 "login": "ivan",
                 "old_social_login": "uid-mmzxrnry",
                 "id": "1000034426",
                 "client_id": "4760187d81bc4b7799476b42b5103713",
                 "is_avatar_empty": false,
                 "default_avatar_id": "131652443",
                 "psuid": "1.AAceCw.tbHgw5DtJ9_zeqPrk-Ba2w.qPWSRC5v2t2IaksPJgnge"
              }
            )json",
            ya_auth::UserInfo{
                .login = "ivan",
                .id = "1000034426",
                .client_id = "4760187d81bc4b7799476b42b5103713",
                .psuid =
                    "1.AAceCw.tbHgw5DtJ9_zeqPrk-Ba2w.qPWSRC5v2t2IaksPJgnge",
                .avatar =
                    ya_auth::UserAvatar{
                        .id = "131652443",
                        .is_empty = false,
                    },
            },
        },
        UserInfoTestData{
            R"json(
              {
                 "login": "ivan",
                 "old_social_login": "uid-mmzxrnry",
                 "default_email": "test@yandex.ru",
                 "id": "1000034426",
                 "client_id": "4760187d81bc4b7799476b42b5103713",
                 "emails": [
                    "test@yandex.ru",
                    "other-test@yandex.ru"
                 ],
                 "psuid": "1.AAceCw.tbHgw5DtJ9_zeqPrk-Ba2w.qPWSRC5v2t2IaksPJgnge"
              }
            )json",
            ya_auth::UserInfo{
                .login = "ivan",
                .id = "1000034426",
                .client_id = "4760187d81bc4b7799476b42b5103713",
                .psuid =
                    "1.AAceCw.tbHgw5DtJ9_zeqPrk-Ba2w.qPWSRC5v2t2IaksPJgnge",
                .email =
                    ya_auth::UserEmail{
                        .default_email = "test@yandex.ru",
                        .emails = {"test@yandex.ru", "other-test@yandex.ru"},
                    },
            },
        },
        UserInfoTestData{
            R"json(
              {
                 "login": "ivan",
                 "id": "1000034426",
                 "client_id": "4760187d81bc4b7799476b42b5103713",
                 "psuid": "1.AAceCw.tbHgw5DtJ9_zeqPrk-Ba2w.qPWSRC5v2t2IaksPJgnge"
              }
            )json",
            ya_auth::UserInfo{
                .login = "ivan",
                .id = "1000034426",
                .client_id = "4760187d81bc4b7799476b42b5103713",
                .psuid =
                    "1.AAceCw.tbHgw5DtJ9_zeqPrk-Ba2w.qPWSRC5v2t2IaksPJgnge",
            },
        }));
