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

#ifndef ACCOUNT_ACCOUNT_EVENT_PROVIDER_H
#define ACCOUNT_ACCOUNT_EVENT_PROVIDER_H

#include <string>
#include "account_error_no.h"
#include "nocopyable.h"

namespace OHOS {
namespace AccountSA {
class AccountEventProvider {
public:
    static bool EventPublish(const std::string& event);
};
} // namespace AccountSA
} // namespace OHOS

#endif // ACCOUNT_ACCOUNT_EVENT_PROVIDER_H