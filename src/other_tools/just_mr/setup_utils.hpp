// Copyright 2023 Huawei Cloud Computing Technology Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef INCLUDED_SRC_OTHER_TOOLS_JUST_MR_SETUP_UTILS_HPP
#define INCLUDED_SRC_OTHER_TOOLS_JUST_MR_SETUP_UTILS_HPP

#include <filesystem>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "src/buildtool/build_engine/expression/configuration.hpp"
#include "src/buildtool/build_engine/expression/expression_ptr.hpp"
#include "src/buildtool/execution_api/common/execution_api.hpp"
#include "src/other_tools/just_mr/cli.hpp"

/* Setup-related constants and utilities for just-mr */

std::vector<std::string> const kAltDirs = {"target_root",
                                           "rule_root",
                                           "expression_root"};

namespace JustMR {

struct SetupRepos {
    std::vector<std::string> to_setup;
    std::vector<std::string> to_include;
};

namespace Utils {

/// \brief Get the repo dependency closure for a given main repository.
void ReachableRepositories(
    ExpressionPtr const& repos,
    std::string const& main,
    std::shared_ptr<JustMR::SetupRepos> const& setup_repos);

/// \brief By default, we set up and include the full repo dependency closure.
void DefaultReachableRepositories(
    ExpressionPtr const& repos,
    std::shared_ptr<JustMR::SetupRepos> const& setup_repos);

/// \brief Read in a just-mr configuration file.
[[nodiscard]] auto ReadConfiguration(
    std::optional<std::filesystem::path> const& config_file_opt) noexcept
    -> std::shared_ptr<Configuration>;

/// \brief Setup of a remote API based on just-mr arguments.
auto SetupRemoteApi(std::optional<std::string> const& remote_exec_addr,
                    MultiRepoRemoteAuthArguments const& auth)
    -> IExecutionApi::Ptr;

}  // namespace Utils

}  // namespace JustMR

#endif  // INCLUDED_SRC_OTHER_TOOLS_JUST_MR_SETUP_UTILS_HPP
