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

#ifndef APP_ACCOUNT_INTERFACES_INNERKITS_APPACCOUNT_NATIVE_INCLUDE_APP_ACCOUNT_MANAGER_H
#define APP_ACCOUNT_INTERFACES_INNERKITS_APPACCOUNT_NATIVE_INCLUDE_APP_ACCOUNT_MANAGER_H

#include "app_account_subscriber.h"
#include "app_account_info.h"

namespace OHOS {
namespace AccountSA {
class AppAccountManager {
public:
    static ErrCode AddAccount(const std::string &name, const std::string &extraInfo = "");
    static ErrCode DeleteAccount(const std::string &name);

    static ErrCode GetAccountExtraInfo(const std::string &name, std::string &extraInfo);
    static ErrCode SetAccountExtraInfo(const std::string &name, const std::string &extraInfo);

    static ErrCode EnableAppAccess(const std::string &name, const std::string &authorizedApp);
    static ErrCode DisableAppAccess(const std::string &name, const std::string &authorizedApp);

    static ErrCode CheckAppAccountSyncEnable(const std::string &name, bool &syncEnable);
    static ErrCode SetAppAccountSyncEnable(const std::string &name, const bool &syncEnable);

    static ErrCode GetAssociatedData(const std::string &name, const std::string &key, std::string &value);
    static ErrCode SetAssociatedData(const std::string &name, const std::string &key, const std::string &value);

    static ErrCode GetAccountCredential(
        const std::string &name, const std::string &credentialType, std::string &credential);
    static ErrCode SetAccountCredential(
        const std::string &name, const std::string &credentialType, const std::string &credential);

    static ErrCode GetOAuthToken(const std::string &name, std::string &token);
    static ErrCode SetOAuthToken(const std::string &name, const std::string &token);
    static ErrCode ClearOAuthToken(const std::string &name);

    static ErrCode GetAllAccounts(const std::string &owner, std::vector<AppAccountInfo> &appAccounts);
    static ErrCode GetAllAccessibleAccounts(std::vector<AppAccountInfo> &appAccounts);

    static ErrCode SubscribeAppAccount(const std::shared_ptr<AppAccountSubscriber> &subscriber);
    static ErrCode UnsubscribeAppAccount(const std::shared_ptr<AppAccountSubscriber> &subscriber);
};
}  // namespace AccountSA
}  // namespace OHOS

#endif  // APP_ACCOUNT_INTERFACES_INNERKITS_APPACCOUNT_NATIVE_INCLUDE_APP_ACCOUNT_MANAGER_H
