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

#ifndef OS_ACCOUNT_SERVICES_ACCOUNTMGR_INCLUDE_APPACCOUNT_APP_ACCOUNT_CONTROL_MANAGER_H
#define OS_ACCOUNT_SERVICES_ACCOUNTMGR_INCLUDE_APPACCOUNT_APP_ACCOUNT_CONTROL_MANAGER_H

#include "app_account_data_storage.h"
#include "bundle_constants.h"
#include "singleton.h"

namespace OHOS {
namespace AccountSA {
class AppAccountControlManager : public DelayedSingleton<AppAccountControlManager> {
public:
    AppAccountControlManager();
    virtual ~AppAccountControlManager();

    ErrCode AddAccount(const std::string &name, const std::string &extraInfo, const std::string &bundleName,
        AppAccountInfo &appAccountInfo);
    ErrCode DeleteAccount(const std::string &name, const std::string &bundleName, AppAccountInfo &appAccountInfo);

    ErrCode GetAccountExtraInfo(const std::string &name, std::string &extraInfo, const std::string &bundleName);
    ErrCode SetAccountExtraInfo(const std::string &name, const std::string &extraInfo, const std::string &bundleName,
        AppAccountInfo &appAccountInfo);

    ErrCode EnableAppAccess(const std::string &name, const std::string &authorizedApp, const std::string &bundleName,
        AppAccountInfo &appAccountInfo);
    ErrCode DisableAppAccess(const std::string &name, const std::string &authorizedApp, const std::string &bundleName,
        AppAccountInfo &appAccountInfo);

    ErrCode CheckAppAccountSyncEnable(const std::string &name, bool &syncEnable, const std::string &bundleName);
    ErrCode SetAppAccountSyncEnable(
        const std::string &name, const bool &syncEnable, const std::string &bundleName, AppAccountInfo &appAccountInfo);

    ErrCode GetAssociatedData(
        const std::string &name, const std::string &key, std::string &value, const std::string &bundleName);
    ErrCode SetAssociatedData(const std::string &name, const std::string &key, const std::string &value,
        const std::string &bundleName, AppAccountInfo &appAccountInfo);

    ErrCode GetAccountCredential(const std::string &name, const std::string &credentialType, std::string &credential,
        const std::string &bundleName);
    ErrCode SetAccountCredential(const std::string &name, const std::string &credentialType,
        const std::string &credential, const std::string &bundleName, AppAccountInfo &appAccountInfo);

    ErrCode GetOAuthToken(const std::string &name, std::string &token, const std::string &bundleName);
    ErrCode SetOAuthToken(const std::string &name, const std::string &token, const std::string &bundleName);
    ErrCode ClearOAuthToken(const std::string &name, const std::string &bundleName);

    ErrCode GetAllAccounts(
        const std::string &owner, std::vector<AppAccountInfo> &appAccounts, const std::string &bundleName);
    ErrCode GetAllAccessibleAccounts(std::vector<AppAccountInfo> &appAccounts, const std::string &bundleName);

    ErrCode OnPackageRemoved(const int32_t &uid, const std::string &bundleName);

private:
    std::shared_ptr<AppAccountDataStorage> GetDataStorage(
        const bool &autoSync = false, const int32_t uid = AppExecFwk::Constants::INVALID_UID);
    ErrCode GetStoreId(std::string &storeId, int32_t uid = AppExecFwk::Constants::INVALID_UID);

    bool NeedSyncDataStorage(const AppAccountInfo &appAccountInfo);
    ErrCode GetAccountInfoFromDataStorage(
        AppAccountInfo &appAccountInfo, std::shared_ptr<AppAccountDataStorage> &dataStoragePtr);
    ErrCode AddAccountInfoIntoDataStorage(
        AppAccountInfo &appAccountInfo, const std::shared_ptr<AppAccountDataStorage> &dataStoragePtr);
    ErrCode SaveAccountInfoIntoDataStorage(
        AppAccountInfo &appAccountInfo, const std::shared_ptr<AppAccountDataStorage> &dataStoragePtr);
    ErrCode DeleteAccountInfoFromDataStorage(
        AppAccountInfo &appAccountInfo, std::shared_ptr<AppAccountDataStorage> &dataStoragePtr);

    ErrCode SaveAuthorizedAccount(const std::string &authorizedApp, AppAccountInfo &appAccountInfo,
        const std::shared_ptr<AppAccountDataStorage> &dataStoragePtr);
    ErrCode RemoveAuthorizedAccount(const std::string &authorizedApp, AppAccountInfo &appAccountInfo,
        const std::shared_ptr<AppAccountDataStorage> &dataStoragePtr);
    ErrCode SaveAuthorizedAccountIntoDataStorage(const std::string &authorizedApp, AppAccountInfo &appAccountInfo,
        const std::shared_ptr<AppAccountDataStorage> &dataStoragePtr);
    ErrCode RemoveAuthorizedAccountFromDataStorage(const std::string &authorizedApp, AppAccountInfo &appAccountInfo,
        const std::shared_ptr<AppAccountDataStorage> &dataStoragePtr);

private:
    std::map<std::string, std::string> dataCache_;

    std::size_t ACCOUNT_MAX_SIZE = 1000;
};
}  // namespace AccountSA
}  // namespace OHOS

#endif  // OS_ACCOUNT_SERVICES_ACCOUNTMGR_INCLUDE_APPACCOUNT_APP_ACCOUNT_CONTROL_MANAGER_H
