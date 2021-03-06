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

#ifndef OS_ACCOUNT_SERVICES_ACCOUNTMGR_INCLUDE_ACCOUNT_PERMISSION_MANAGER_H
#define OS_ACCOUNT_SERVICES_ACCOUNTMGR_INCLUDE_ACCOUNT_PERMISSION_MANAGER_H

#include "account_error_no.h"
#include "singleton.h"

namespace OHOS {
namespace AccountSA {
class AccountPermissionManager : public DelayedSingleton<AccountPermissionManager> {
public:
    AccountPermissionManager();
    ~AccountPermissionManager();

    ErrCode VerifyPermission(const std::string &permissionName, const std::string &bundleName = "");

    static const std::string DISTRIBUTED_DATASYNC;
    static const std::string GET_ACCOUNTS_PRIVILEGED;
};
}  // namespace AccountSA
}  // namespace OHOS

#endif  // OS_ACCOUNT_SERVICES_ACCOUNTMGR_INCLUDE_ACCOUNT_PERMISSION_MANAGER_H
