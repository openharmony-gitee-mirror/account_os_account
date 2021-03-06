/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <gtest/gtest.h>

#define private public
#include "app_account_control_manager.h"
#include "app_account_manager_service.h"
#undef private

using namespace testing::ext;
using namespace OHOS;
using namespace OHOS::AccountSA;

namespace {
const std::string STRING_NAME = "name";
const std::string STRING_NAME_TWO = "name_two";
const std::string STRING_NAME_THREE = "name_three";
const std::string STRING_NAME_NOT_EXISTED = "name_not_existed";
const std::string STRING_EXTRA_INFO = "extra_info";
const std::string STRING_EXTRA_INFO_TWO = "extra_info_two";
const std::string STRING_BUNDLE_NAME = "com.example.third_party";
const std::string STRING_EMPTY = "";
const std::string STRING_OWNER = "com.example.owner";

const std::string HYPHEN = "#";

const bool SYNC_ENABLE_TRUE = true;
const bool SYNC_ENABLE_FALSE = false;

constexpr std::size_t SIZE_ZERO = 0;
constexpr std::size_t SIZE_ONE = 1;
}  // namespace

class AppAccountManagerServiceSyncModuleTest : public testing::Test {
public:
    static void SetUpTestCase(void);
    static void TearDownTestCase(void);
    void SetUp(void) override;
    void TearDown(void) override;

    void DeleteKvStore(void);

    std::shared_ptr<AppAccountControlManager> controlManagerPtr_;
};

void AppAccountManagerServiceSyncModuleTest::SetUpTestCase(void)
{}

void AppAccountManagerServiceSyncModuleTest::TearDownTestCase(void)
{}

void AppAccountManagerServiceSyncModuleTest::SetUp(void)
{
    DeleteKvStore();
}

void AppAccountManagerServiceSyncModuleTest::TearDown(void)
{
    DeleteKvStore();
}

void AppAccountManagerServiceSyncModuleTest::DeleteKvStore(void)
{
    controlManagerPtr_ = AppAccountControlManager::GetInstance();
    ASSERT_NE(controlManagerPtr_, nullptr);

    auto dataStoragePtr = controlManagerPtr_->GetDataStorage();
    ASSERT_NE(dataStoragePtr, nullptr);

    ErrCode result = dataStoragePtr->DeleteKvStore();
    ASSERT_EQ(result, ERR_OK);

    dataStoragePtr = controlManagerPtr_->GetDataStorage(true);
    ASSERT_NE(dataStoragePtr, nullptr);

    result = dataStoragePtr->DeleteKvStore();
    ASSERT_EQ(result, ERR_OK);
}

/**
 * @tc.number: AppAccountManagerServiceSync_AddAccount_0100
 * @tc.name: AddAccount
 * @tc.desc: Set account sync enable with valid data.
 */
HWTEST_F(AppAccountManagerServiceSyncModuleTest, AppAccountManagerServiceSync_AddAccount_0100,
    Function | MediumTest | Level1)
{
    ACCOUNT_LOGI("AppAccountManagerServiceSync_AddAccount_0100");

    auto servicePtr = std::make_shared<AppAccountManagerService>();
    ASSERT_NE(servicePtr, nullptr);

    ErrCode result = servicePtr->AddAccount(STRING_NAME, STRING_EXTRA_INFO);
    EXPECT_EQ(result, ERR_OK);

    {
        auto dataStoragePtr = controlManagerPtr_->GetDataStorage();
        ASSERT_NE(dataStoragePtr, nullptr);

        std::map<std::string, std::shared_ptr<IAccountInfo>> accounts;
        accounts.clear();

        result = dataStoragePtr->LoadAllData(accounts);
        EXPECT_EQ(result, ERR_OK);
        EXPECT_EQ(accounts.size(), SIZE_ONE);

        auto accountPtr = accounts.begin();
        EXPECT_NE(accountPtr, accounts.end());

        auto appAccountInfoPtr = std::static_pointer_cast<AppAccountInfo>(accountPtr->second);
        ASSERT_NE(appAccountInfoPtr, nullptr);

        std::string name;
        result = appAccountInfoPtr->GetName(name);
        EXPECT_EQ(result, ERR_OK);
        EXPECT_EQ(name, STRING_NAME);
    }
    {
        auto dataStoragePtr = controlManagerPtr_->GetDataStorage(true);
        ASSERT_NE(dataStoragePtr, nullptr);

        std::map<std::string, std::shared_ptr<IAccountInfo>> accounts;
        accounts.clear();

        result = dataStoragePtr->LoadAllData(accounts);
        EXPECT_EQ(result, ERR_OK);
        EXPECT_EQ(accounts.size(), SIZE_ZERO);
    }

    result = servicePtr->DeleteAccount(STRING_NAME);
    EXPECT_EQ(result, ERR_OK);
}

/**
 * @tc.number: AppAccountManagerServiceSync_AddAccount_0200
 * @tc.name: AddAccount
 * @tc.desc: Set account sync enable with valid data.
 */
HWTEST_F(AppAccountManagerServiceSyncModuleTest, AppAccountManagerServiceSync_AddAccount_0200,
    Function | MediumTest | Level1)
{
    ACCOUNT_LOGI("AppAccountManagerServiceSync_AddAccount_0200");

    auto servicePtr = std::make_shared<AppAccountManagerService>();
    ASSERT_NE(servicePtr, nullptr);

    ErrCode result = servicePtr->AddAccount(STRING_NAME, STRING_EXTRA_INFO);
    EXPECT_EQ(result, ERR_OK);

    result = servicePtr->SetAppAccountSyncEnable(STRING_NAME, SYNC_ENABLE_TRUE);
    EXPECT_EQ(result, ERR_OK);

    {
        auto dataStoragePtr = controlManagerPtr_->GetDataStorage();
        ASSERT_NE(dataStoragePtr, nullptr);

        std::map<std::string, std::shared_ptr<IAccountInfo>> accounts;
        accounts.clear();

        result = dataStoragePtr->LoadAllData(accounts);
        EXPECT_EQ(result, ERR_OK);
        EXPECT_EQ(accounts.size(), SIZE_ONE);

        auto accountPtr = accounts.begin();
        EXPECT_NE(accountPtr, accounts.end());

        auto appAccountInfoPtr = std::static_pointer_cast<AppAccountInfo>(accountPtr->second);
        ASSERT_NE(appAccountInfoPtr, nullptr);

        std::string name;
        result = appAccountInfoPtr->GetName(name);
        EXPECT_EQ(result, ERR_OK);
        EXPECT_EQ(name, STRING_NAME);
    }
    {
        auto dataStoragePtr = controlManagerPtr_->GetDataStorage(true);
        ASSERT_NE(dataStoragePtr, nullptr);

        std::map<std::string, std::shared_ptr<IAccountInfo>> accounts;
        accounts.clear();

        result = dataStoragePtr->LoadAllData(accounts);
        EXPECT_EQ(result, ERR_OK);
        EXPECT_EQ(accounts.size(), SIZE_ONE);

        auto accountPtr = accounts.begin();
        EXPECT_NE(accountPtr, accounts.end());

        auto appAccountInfoPtr = std::static_pointer_cast<AppAccountInfo>(accountPtr->second);
        ASSERT_NE(appAccountInfoPtr, nullptr);

        std::string name;
        result = appAccountInfoPtr->GetName(name);
        EXPECT_EQ(result, ERR_OK);
        EXPECT_EQ(name, STRING_NAME);
    }

    result = servicePtr->DeleteAccount(STRING_NAME);
    EXPECT_EQ(result, ERR_OK);
}

/**
 * @tc.number: AppAccountManagerServiceSync_DeleteAccount_0100
 * @tc.name: DeleteAccount
 * @tc.desc: Set account sync enable with valid data.
 */
HWTEST_F(AppAccountManagerServiceSyncModuleTest, AppAccountManagerServiceSync_DeleteAccount_0100,
    Function | MediumTest | Level1)
{
    ACCOUNT_LOGI("AppAccountManagerServiceSync_DeleteAccount_0100");

    auto servicePtr = std::make_shared<AppAccountManagerService>();
    ASSERT_NE(servicePtr, nullptr);

    ErrCode result = servicePtr->AddAccount(STRING_NAME, STRING_EXTRA_INFO);
    EXPECT_EQ(result, ERR_OK);

    result = servicePtr->SetAppAccountSyncEnable(STRING_NAME, SYNC_ENABLE_TRUE);
    EXPECT_EQ(result, ERR_OK);

    result = servicePtr->DeleteAccount(STRING_NAME);
    EXPECT_EQ(result, ERR_OK);

    {
        auto dataStoragePtr = controlManagerPtr_->GetDataStorage();
        ASSERT_NE(dataStoragePtr, nullptr);

        std::map<std::string, std::shared_ptr<IAccountInfo>> accounts;
        accounts.clear();

        result = dataStoragePtr->LoadAllData(accounts);
        EXPECT_EQ(result, ERR_OK);
        EXPECT_EQ(accounts.size(), SIZE_ZERO);
    }
    {
        auto dataStoragePtr = controlManagerPtr_->GetDataStorage(true);
        ASSERT_NE(dataStoragePtr, nullptr);

        std::map<std::string, std::shared_ptr<IAccountInfo>> accounts;
        accounts.clear();

        result = dataStoragePtr->LoadAllData(accounts);
        EXPECT_EQ(result, ERR_OK);
        EXPECT_EQ(accounts.size(), SIZE_ZERO);
    }
}

/**
 * @tc.number: AppAccountManagerServiceSync_DeleteAccount_0200
 * @tc.name: DeleteAccount
 * @tc.desc: Set account sync enable with valid data.
 */
HWTEST_F(AppAccountManagerServiceSyncModuleTest, AppAccountManagerServiceSync_DeleteAccount_0200,
    Function | MediumTest | Level1)
{
    ACCOUNT_LOGI("AppAccountManagerServiceSync_DeleteAccount_0200");

    auto servicePtr = std::make_shared<AppAccountManagerService>();
    ASSERT_NE(servicePtr, nullptr);

    ErrCode result = servicePtr->AddAccount(STRING_NAME, STRING_EXTRA_INFO);
    EXPECT_EQ(result, ERR_OK);

    result = servicePtr->SetAppAccountSyncEnable(STRING_NAME, SYNC_ENABLE_TRUE);
    EXPECT_EQ(result, ERR_OK);

    result = servicePtr->SetAppAccountSyncEnable(STRING_NAME, SYNC_ENABLE_FALSE);
    EXPECT_EQ(result, ERR_OK);

    result = servicePtr->DeleteAccount(STRING_NAME);
    EXPECT_EQ(result, ERR_OK);

    {
        auto dataStoragePtr = controlManagerPtr_->GetDataStorage();
        ASSERT_NE(dataStoragePtr, nullptr);

        std::map<std::string, std::shared_ptr<IAccountInfo>> accounts;
        accounts.clear();

        result = dataStoragePtr->LoadAllData(accounts);
        EXPECT_EQ(result, ERR_OK);
        EXPECT_EQ(accounts.size(), SIZE_ZERO);
    }
    {
        auto dataStoragePtr = controlManagerPtr_->GetDataStorage(true);
        ASSERT_NE(dataStoragePtr, nullptr);

        std::map<std::string, std::shared_ptr<IAccountInfo>> accounts;
        accounts.clear();

        result = dataStoragePtr->LoadAllData(accounts);
        EXPECT_EQ(result, ERR_OK);
        EXPECT_EQ(accounts.size(), SIZE_ONE);
    }
}

/**
 * @tc.number: AppAccountManagerServiceSync_SetAccountExtraInfo_0100
 * @tc.name: SetAccountExtraInfo
 * @tc.desc: Set account sync enable with valid data.
 */
HWTEST_F(AppAccountManagerServiceSyncModuleTest, AppAccountManagerServiceSync_SetAccountExtraInfo_0100,
    Function | MediumTest | Level1)
{
    ACCOUNT_LOGI("AppAccountManagerServiceSync_SetAccountExtraInfo_0100");

    auto servicePtr = std::make_shared<AppAccountManagerService>();

    ErrCode result = servicePtr->AddAccount(STRING_NAME, STRING_EXTRA_INFO);
    EXPECT_EQ(result, ERR_OK);

    result = servicePtr->SetAppAccountSyncEnable(STRING_NAME, SYNC_ENABLE_TRUE);
    EXPECT_EQ(result, ERR_OK);

    result = servicePtr->SetAccountExtraInfo(STRING_NAME, STRING_EXTRA_INFO);
    EXPECT_EQ(result, ERR_OK);

    {
        auto dataStoragePtr = controlManagerPtr_->GetDataStorage();
        ASSERT_NE(dataStoragePtr, nullptr);

        std::map<std::string, std::shared_ptr<IAccountInfo>> accounts;

        result = dataStoragePtr->LoadAllData(accounts);
        ASSERT_EQ(accounts.size(), SIZE_ONE);

        auto accountPtr = accounts.begin();
        auto appAccountInfoPtr = std::static_pointer_cast<AppAccountInfo>(accountPtr->second);

        std::string name;
        appAccountInfoPtr->GetName(name);
        EXPECT_EQ(name, STRING_NAME);

        std::string extraInfo;
        appAccountInfoPtr->GetExtraInfo(extraInfo);
        EXPECT_EQ(extraInfo, STRING_EXTRA_INFO);
    }
    {
        auto dataStoragePtr = controlManagerPtr_->GetDataStorage(true);
        ASSERT_NE(dataStoragePtr, nullptr);

        std::map<std::string, std::shared_ptr<IAccountInfo>> accounts;

        result = dataStoragePtr->LoadAllData(accounts);
        ASSERT_EQ(accounts.size(), SIZE_ONE);

        auto accountPtr = accounts.begin();
        auto appAccountInfoPtr = std::static_pointer_cast<AppAccountInfo>(accountPtr->second);

        std::string name;
        appAccountInfoPtr->GetName(name);
        EXPECT_EQ(name, STRING_NAME);

        std::string extraInfo;
        appAccountInfoPtr->GetExtraInfo(extraInfo);
        EXPECT_EQ(extraInfo, STRING_EXTRA_INFO);
    }

    result = servicePtr->DeleteAccount(STRING_NAME);
    EXPECT_EQ(result, ERR_OK);
}

/**
 * @tc.number: AppAccountManagerServiceSync_SetAccountExtraInfo_0200
 * @tc.name: SetAccountExtraInfo
 * @tc.desc: Set account sync enable with valid data.
 */
HWTEST_F(AppAccountManagerServiceSyncModuleTest, AppAccountManagerServiceSync_SetAccountExtraInfo_0200,
    Function | MediumTest | Level1)
{
    ACCOUNT_LOGI("AppAccountManagerServiceSync_SetAccountExtraInfo_0200");

    auto servicePtr = std::make_shared<AppAccountManagerService>();

    ErrCode result = servicePtr->AddAccount(STRING_NAME, STRING_EXTRA_INFO);
    EXPECT_EQ(result, ERR_OK);

    result = servicePtr->SetAppAccountSyncEnable(STRING_NAME, SYNC_ENABLE_TRUE);
    EXPECT_EQ(result, ERR_OK);

    result = servicePtr->SetAccountExtraInfo(STRING_NAME, STRING_EXTRA_INFO);
    EXPECT_EQ(result, ERR_OK);

    result = servicePtr->SetAppAccountSyncEnable(STRING_NAME, SYNC_ENABLE_FALSE);
    EXPECT_EQ(result, ERR_OK);

    result = servicePtr->SetAccountExtraInfo(STRING_NAME, STRING_EXTRA_INFO_TWO);
    EXPECT_EQ(result, ERR_OK);

    {
        auto dataStoragePtr = controlManagerPtr_->GetDataStorage();
        ASSERT_NE(dataStoragePtr, nullptr);

        std::map<std::string, std::shared_ptr<IAccountInfo>> accounts;

        result = dataStoragePtr->LoadAllData(accounts);
        ASSERT_EQ(accounts.size(), SIZE_ONE);

        auto accountPtr = accounts.begin();
        EXPECT_NE(accountPtr, accounts.end());

        auto appAccountInfoPtr = std::static_pointer_cast<AppAccountInfo>(accountPtr->second);
        ASSERT_NE(appAccountInfoPtr, nullptr);

        std::string name;
        appAccountInfoPtr->GetName(name);
        EXPECT_EQ(name, STRING_NAME);

        std::string extraInfo;
        appAccountInfoPtr->GetExtraInfo(extraInfo);
        EXPECT_EQ(extraInfo, STRING_EXTRA_INFO_TWO);
    }
    {
        auto dataStoragePtr = controlManagerPtr_->GetDataStorage(true);
        ASSERT_NE(dataStoragePtr, nullptr);

        std::map<std::string, std::shared_ptr<IAccountInfo>> accounts;

        result = dataStoragePtr->LoadAllData(accounts);
        ASSERT_EQ(accounts.size(), SIZE_ONE);

        auto accountPtr = accounts.begin();
        auto appAccountInfoPtr = std::static_pointer_cast<AppAccountInfo>(accountPtr->second);

        std::string name;
        appAccountInfoPtr->GetName(name);
        EXPECT_EQ(name, STRING_NAME);

        std::string extraInfo;
        appAccountInfoPtr->GetExtraInfo(extraInfo);
        EXPECT_EQ(extraInfo, STRING_EXTRA_INFO);
    }

    result = servicePtr->DeleteAccount(STRING_NAME);
    EXPECT_EQ(result, ERR_OK);
}

/**
 * @tc.number: AppAccountManagerServiceSync_SetAccountExtraInfo_0300
 * @tc.name: SetAccountExtraInfo
 * @tc.desc: Set account sync enable with valid data.
 */
HWTEST_F(AppAccountManagerServiceSyncModuleTest, AppAccountManagerServiceSync_SetAccountExtraInfo_0300,
    Function | MediumTest | Level1)
{
    ACCOUNT_LOGI("AppAccountManagerServiceSync_SetAccountExtraInfo_0300");

    auto servicePtr = std::make_shared<AppAccountManagerService>();

    ErrCode result = servicePtr->AddAccount(STRING_NAME, STRING_EXTRA_INFO);
    EXPECT_EQ(result, ERR_OK);

    result = servicePtr->SetAppAccountSyncEnable(STRING_NAME, SYNC_ENABLE_TRUE);
    EXPECT_EQ(result, ERR_OK);

    result = servicePtr->SetAccountExtraInfo(STRING_NAME, STRING_EXTRA_INFO);
    EXPECT_EQ(result, ERR_OK);

    result = servicePtr->SetAppAccountSyncEnable(STRING_NAME, SYNC_ENABLE_FALSE);
    EXPECT_EQ(result, ERR_OK);

    result = servicePtr->SetAccountExtraInfo(STRING_NAME, STRING_EXTRA_INFO_TWO);
    EXPECT_EQ(result, ERR_OK);

    result = servicePtr->SetAppAccountSyncEnable(STRING_NAME, SYNC_ENABLE_TRUE);
    EXPECT_EQ(result, ERR_OK);

    {
        auto dataStoragePtr = controlManagerPtr_->GetDataStorage();
        ASSERT_NE(dataStoragePtr, nullptr);

        std::map<std::string, std::shared_ptr<IAccountInfo>> accounts;
        result = dataStoragePtr->LoadAllData(accounts);
        ASSERT_EQ(accounts.size(), SIZE_ONE);

        auto accountPtr = accounts.begin();
        auto appAccountInfoPtr = std::static_pointer_cast<AppAccountInfo>(accountPtr->second);

        std::string name;
        appAccountInfoPtr->GetName(name);
        EXPECT_EQ(name, STRING_NAME);

        std::string extraInfo;
        appAccountInfoPtr->GetExtraInfo(extraInfo);
        EXPECT_EQ(extraInfo, STRING_EXTRA_INFO_TWO);
    }
    {
        auto dataStoragePtr = controlManagerPtr_->GetDataStorage(true);
        ASSERT_NE(dataStoragePtr, nullptr);

        std::map<std::string, std::shared_ptr<IAccountInfo>> accounts;
        result = dataStoragePtr->LoadAllData(accounts);
        ASSERT_EQ(accounts.size(), SIZE_ONE);

        auto accountPtr = accounts.begin();
        auto appAccountInfoPtr = std::static_pointer_cast<AppAccountInfo>(accountPtr->second);

        std::string name;
        appAccountInfoPtr->GetName(name);
        EXPECT_EQ(name, STRING_NAME);

        std::string extraInfo;
        appAccountInfoPtr->GetExtraInfo(extraInfo);
        EXPECT_EQ(extraInfo, STRING_EXTRA_INFO_TWO);
    }

    result = servicePtr->DeleteAccount(STRING_NAME);
    EXPECT_EQ(result, ERR_OK);
}

/**
 * @tc.number: AppAccountManagerServiceSync_EnableAppAccess_0100
 * @tc.name: EnableAppAccess
 * @tc.desc: Set account sync enable with valid data.
 */
HWTEST_F(AppAccountManagerServiceSyncModuleTest, AppAccountManagerServiceSync_EnableAppAccess_0100,
    Function | MediumTest | Level1)
{
    ACCOUNT_LOGI("AppAccountManagerServiceSync_EnableAppAccess_0100");

    auto servicePtr = std::make_shared<AppAccountManagerService>();
    ASSERT_NE(servicePtr, nullptr);

    ErrCode result = servicePtr->AddAccount(STRING_NAME, STRING_EXTRA_INFO);
    EXPECT_EQ(result, ERR_OK);

    result = servicePtr->SetAppAccountSyncEnable(STRING_NAME, SYNC_ENABLE_TRUE);
    EXPECT_EQ(result, ERR_OK);

    result = servicePtr->EnableAppAccess(STRING_NAME, STRING_BUNDLE_NAME);
    EXPECT_EQ(result, ERR_OK);

    {
        auto dataStoragePtr = controlManagerPtr_->GetDataStorage();
        ASSERT_NE(dataStoragePtr, nullptr);

        std::string authorizedAccounts;
        ErrCode result = dataStoragePtr->GetConfigById(AppAccountDataStorage::AUTHORIZED_ACCOUNTS, authorizedAccounts);
        ASSERT_EQ(result, ERR_OK);

        auto jsonObject = Json::parse(authorizedAccounts, nullptr, false);
        EXPECT_EQ(jsonObject.is_discarded(), false);

        auto accessibleAccounts = jsonObject[STRING_BUNDLE_NAME].get<std::vector<std::string>>();
        EXPECT_EQ(accessibleAccounts.size(), SIZE_ONE);

        auto accountPtr = accessibleAccounts.begin();
        ASSERT_NE(accountPtr, accessibleAccounts.end());

        EXPECT_EQ(*accountPtr, STRING_OWNER + HYPHEN + STRING_NAME);
    }
    {
        auto dataStoragePtr = controlManagerPtr_->GetDataStorage(true);
        ASSERT_NE(dataStoragePtr, nullptr);

        std::string authorizedAccounts;
        ErrCode result = dataStoragePtr->GetConfigById(AppAccountDataStorage::AUTHORIZED_ACCOUNTS, authorizedAccounts);
        ASSERT_EQ(result, ERR_OK);

        auto jsonObject = Json::parse(authorizedAccounts, nullptr, false);
        EXPECT_EQ(jsonObject.is_discarded(), false);

        auto accessibleAccounts = jsonObject[STRING_BUNDLE_NAME].get<std::vector<std::string>>();
        EXPECT_EQ(accessibleAccounts.size(), SIZE_ONE);

        auto accountPtr = accessibleAccounts.begin();
        ASSERT_NE(accountPtr, accessibleAccounts.end());

        EXPECT_EQ(*accountPtr, STRING_OWNER + HYPHEN + STRING_NAME);
    }

    result = servicePtr->DeleteAccount(STRING_NAME);
    EXPECT_EQ(result, ERR_OK);
}

/**
 * @tc.number: AppAccountManagerServiceSync_EnableAppAccess_0200
 * @tc.name: EnableAppAccess
 * @tc.desc: Set account sync enable with valid data.
 */
HWTEST_F(AppAccountManagerServiceSyncModuleTest, AppAccountManagerServiceSync_EnableAppAccess_0200,
    Function | MediumTest | Level1)
{
    ACCOUNT_LOGI("AppAccountManagerServiceSync_EnableAppAccess_0200");

    auto servicePtr = std::make_shared<AppAccountManagerService>();
    ASSERT_NE(servicePtr, nullptr);

    ErrCode result = servicePtr->AddAccount(STRING_NAME, STRING_EXTRA_INFO);
    EXPECT_EQ(result, ERR_OK);

    result = servicePtr->SetAppAccountSyncEnable(STRING_NAME, SYNC_ENABLE_TRUE);
    EXPECT_EQ(result, ERR_OK);

    result = servicePtr->EnableAppAccess(STRING_NAME, STRING_BUNDLE_NAME);
    EXPECT_EQ(result, ERR_OK);

    result = servicePtr->EnableAppAccess(STRING_NAME, STRING_BUNDLE_NAME);
    EXPECT_EQ(result, ERR_APPACCOUNT_SERVICE_ENABLE_APP_ACCESS_ALREADY_EXISTS);

    {
        auto dataStoragePtr = controlManagerPtr_->GetDataStorage();
        ASSERT_NE(dataStoragePtr, nullptr);

        std::string authorizedAccounts;
        ErrCode result = dataStoragePtr->GetConfigById(AppAccountDataStorage::AUTHORIZED_ACCOUNTS, authorizedAccounts);
        ASSERT_EQ(result, ERR_OK);

        auto jsonObject = Json::parse(authorizedAccounts, nullptr, false);
        EXPECT_EQ(jsonObject.is_discarded(), false);

        auto accessibleAccounts = jsonObject[STRING_BUNDLE_NAME].get<std::vector<std::string>>();
        EXPECT_EQ(accessibleAccounts.size(), SIZE_ONE);

        auto accountPtr = accessibleAccounts.begin();
        ASSERT_NE(accountPtr, accessibleAccounts.end());

        EXPECT_EQ(*accountPtr, STRING_OWNER + HYPHEN + STRING_NAME);
    }
    {
        auto dataStoragePtr = controlManagerPtr_->GetDataStorage(true);
        ASSERT_NE(dataStoragePtr, nullptr);

        std::string authorizedAccounts;
        ErrCode result = dataStoragePtr->GetConfigById(AppAccountDataStorage::AUTHORIZED_ACCOUNTS, authorizedAccounts);
        ASSERT_EQ(result, ERR_OK);

        auto jsonObject = Json::parse(authorizedAccounts, nullptr, false);
        EXPECT_EQ(jsonObject.is_discarded(), false);

        auto accessibleAccounts = jsonObject[STRING_BUNDLE_NAME].get<std::vector<std::string>>();
        EXPECT_EQ(accessibleAccounts.size(), SIZE_ONE);

        auto accountPtr = accessibleAccounts.begin();
        ASSERT_NE(accountPtr, accessibleAccounts.end());

        EXPECT_EQ(*accountPtr, STRING_OWNER + HYPHEN + STRING_NAME);
    }

    result = servicePtr->DeleteAccount(STRING_NAME);
    EXPECT_EQ(result, ERR_OK);
}

/**
 * @tc.number: AppAccountManagerServiceSync_DisableAppAccess_0100
 * @tc.name: DisableAppAccess
 * @tc.desc: Set account sync enable with valid data.
 */
HWTEST_F(AppAccountManagerServiceSyncModuleTest, AppAccountManagerServiceSync_DisableAppAccess_0100,
    Function | MediumTest | Level1)
{
    ACCOUNT_LOGI("AppAccountManagerServiceSync_DisableAppAccess_0100");

    auto servicePtr = std::make_shared<AppAccountManagerService>();
    ASSERT_NE(servicePtr, nullptr);

    ErrCode result = servicePtr->AddAccount(STRING_NAME, STRING_EXTRA_INFO);
    EXPECT_EQ(result, ERR_OK);

    result = servicePtr->SetAppAccountSyncEnable(STRING_NAME, SYNC_ENABLE_TRUE);
    EXPECT_EQ(result, ERR_OK);

    result = servicePtr->EnableAppAccess(STRING_NAME, STRING_BUNDLE_NAME);
    EXPECT_EQ(result, ERR_OK);

    result = servicePtr->DisableAppAccess(STRING_NAME, STRING_BUNDLE_NAME);
    EXPECT_EQ(result, ERR_OK);

    {
        auto dataStoragePtr = controlManagerPtr_->GetDataStorage();
        ASSERT_NE(dataStoragePtr, nullptr);

        std::string authorizedAccounts;
        ErrCode result = dataStoragePtr->GetConfigById(AppAccountDataStorage::AUTHORIZED_ACCOUNTS, authorizedAccounts);
        ASSERT_EQ(result, ERR_OK);

        auto jsonObject = Json::parse(authorizedAccounts, nullptr, false);
        EXPECT_EQ(jsonObject.is_discarded(), false);

        auto accessibleAccounts = jsonObject[STRING_BUNDLE_NAME].get<std::vector<std::string>>();
        EXPECT_EQ(accessibleAccounts.size(), SIZE_ZERO);
    }
    {
        auto dataStoragePtr = controlManagerPtr_->GetDataStorage(true);
        ASSERT_NE(dataStoragePtr, nullptr);

        std::string authorizedAccounts;
        ErrCode result = dataStoragePtr->GetConfigById(AppAccountDataStorage::AUTHORIZED_ACCOUNTS, authorizedAccounts);
        ASSERT_EQ(result, ERR_OK);

        auto jsonObject = Json::parse(authorizedAccounts, nullptr, false);
        EXPECT_EQ(jsonObject.is_discarded(), false);

        auto accessibleAccounts = jsonObject[STRING_BUNDLE_NAME].get<std::vector<std::string>>();
        EXPECT_EQ(accessibleAccounts.size(), SIZE_ZERO);
    }

    result = servicePtr->DeleteAccount(STRING_NAME);
    EXPECT_EQ(result, ERR_OK);
}
