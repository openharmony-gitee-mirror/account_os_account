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

#ifndef APP_ACCOUNT_FRAMEWORKS_APPACCOUNT_CORE_TEST_MOCK_MOCK_APP_ACCOUNT_STUB_H
#define APP_ACCOUNT_FRAMEWORKS_APPACCOUNT_CORE_TEST_MOCK_MOCK_APP_ACCOUNT_STUB_H

#include "gmock/gmock.h"

#include "app_account_stub.h"

namespace OHOS {
namespace AccountSA {
class MockAppAccountStub : public AppAccountStub {
public:
    virtual ErrCode AddAccount(const std::string &name, const std::string &extraInfo) override;
    virtual ErrCode DeleteAccount(const std::string &name) override;

    virtual ErrCode GetAccountExtraInfo(const std::string &name, std::string &extraInfo) override;
    virtual ErrCode SetAccountExtraInfo(const std::string &name, const std::string &extraInfo) override;

    virtual ErrCode EnableAppAccess(const std::string &name, const std::string &authorizedApp) override;
    virtual ErrCode DisableAppAccess(const std::string &name, const std::string &authorizedApp) override;

    virtual ErrCode CheckAppAccountSyncEnable(const std::string &name, bool &syncEnable) override;
    virtual ErrCode SetAppAccountSyncEnable(const std::string &name, const bool &syncEnable) override;

    virtual ErrCode GetAssociatedData(const std::string &name, const std::string &key, std::string &value) override;
    virtual ErrCode SetAssociatedData(
        const std::string &name, const std::string &key, const std::string &value) override;

    virtual ErrCode GetAccountCredential(
        const std::string &name, const std::string &credentialType, std::string &credential) override;
    virtual ErrCode SetAccountCredential(
        const std::string &name, const std::string &credentialType, const std::string &credential) override;

    virtual ErrCode GetOAuthToken(const std::string &name, std::string &token) override;
    virtual ErrCode SetOAuthToken(const std::string &name, const std::string &token) override;
    virtual ErrCode ClearOAuthToken(const std::string &name) override;

    virtual ErrCode GetAllAccounts(const std::string &owner, std::vector<AppAccountInfo> &appAccounts) override;
    virtual ErrCode GetAllAccessibleAccounts(std::vector<AppAccountInfo> &appAccounts) override;

    virtual ErrCode SubscribeAppAccount(
        const AppAccountSubscribeInfo &subscribeInfo, const sptr<IRemoteObject> &eventListener) override;
    virtual ErrCode UnsubscribeAppAccount(const sptr<IRemoteObject> &eventListener) override;
};
}  // namespace AccountSA
}  // namespace OHOS

#endif  // APP_ACCOUNT_FRAMEWORKS_APPACCOUNT_CORE_TEST_MOCK_MOCK_APP_ACCOUNT_STUB_H
