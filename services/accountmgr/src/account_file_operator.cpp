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

#include <fstream>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>

#include "account_log_wrapper.h"
#include "directory_ex.h"

#include "account_file_operator.h"

namespace OHOS {
namespace AccountSA {
AccountFileOperator::AccountFileOperator()
{}

AccountFileOperator::~AccountFileOperator()
{}

ErrCode AccountFileOperator::CreateDir(const std::string &path)
{
    ACCOUNT_LOGI("enter");

    if (!OHOS::ForceCreateDirectory(path)) {
        return ERR_OS_ACCOUNT_SERVICE_FILE_CREATE_DIR_ERROR;
    }
    mode_t mode = S_IRWXU | S_IRGRP | S_IXGRP | S_IXOTH;
    mode |= (false ? S_IROTH : 0);
    bool createFlag = OHOS::ChangeModeDirectory(path, mode);
    if (!createFlag) {
        return ERR_OS_ACCOUNT_SERVICE_FILE_CHANGE_DIR_MODE_ERROR;
    }

    return ERR_OK;
}

ErrCode AccountFileOperator::DeleteDirOrFile(const std::string &path)
{
    bool delFlag = false;
    if (IsExistFile(path)) {
        delFlag = OHOS::RemoveFile(path);
    }
    if (IsExistDir(path)) {
        delFlag = OHOS::ForceRemoveDirectory(path);
    }
    if (!delFlag) {
        return ERR_OS_ACCOUNT_SERVICE_FILE_DELE_ERROR;
    }

    return ERR_OK;
}

ErrCode AccountFileOperator::InputFileByPathAndContent(const std::string &path, const std::string &content)
{
    std::string str = path;
    str.erase(str.rfind('/'));
    if (!IsExistDir(str)) {
        ErrCode errCode = CreateDir(str);
        if (errCode != ERR_OK) {
            ACCOUNT_LOGE("failed to create dir, str = %{public}s", str.c_str());
            return ERR_OS_ACCOUNT_SERVICE_FILE_FIND_DIR_ERROR;
        }
    }
    std::ofstream o(path);
    if (!o.is_open()) {
        return ERR_OS_ACCOUNT_SERVICE_FILE_CREATE_FILE_FAILED_ERROR;
    }
    o << content;

    ACCOUNT_LOGI("end");

    return ERR_OK;
}

ErrCode AccountFileOperator::GetFileContentByPath(const std::string &path, std::string &content)
{
    if (!IsExistFile(path)) {
        return ERR_OS_ACCOUNT_SERVICE_FILE_FIND_FILE_ERROR;
    }
    std::stringstream buffer;
    std::ifstream i(path);
    if (!i.is_open()) {
        return ERR_OS_ACCOUNT_SERVICE_FILE_CREATE_FILE_FAILED_ERROR;
    }
    buffer << i.rdbuf();
    content = buffer.str();

    return ERR_OK;
}

bool AccountFileOperator::IsExistFile(const std::string &path)
{
    if (path.empty()) {
        return false;
    }

    struct stat buf = {};
    if (stat(path.c_str(), &buf) != 0) {
        return false;
    }

    return S_ISREG(buf.st_mode);
}

bool AccountFileOperator::IsExistDir(const std::string &path)
{
    if (path.empty()) {
        return false;
    }

    struct stat buf = {};
    if (stat(path.c_str(), &buf) != 0) {
        return false;
    }

    return S_ISDIR(buf.st_mode);
}
}  // namespace AccountSA
}  // namespace OHOS
