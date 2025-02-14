// Copyright (c) 2019, QuantStack and Mamba Contributors
//
// Distributed under the terms of the BSD 3-Clause License.
//
// The full license is in the file LICENSE, distributed with this software.

#ifndef MAMBA_SOLVER_LIBSOLV_REPO_INFO_HPP
#define MAMBA_SOLVER_LIBSOLV_REPO_INFO_HPP

#include <string_view>

#include "mamba/solver/libsolv/parameters.hpp"


extern "C"
{
    using Repo = struct s_Repo;
}

namespace mamba
{
    class MPool;
    class MTransaction;
}

namespace mamba::solver::libsolv
{
    /**
     * A libsolv repository descriptor.
     *
     * In libsolv, most of the data is help in the Pool, and repo are tightly coupled with them.
     * This repository class is a lightwight description of a repository returned when creating
     * a new repository in the Pool.
     * Some modifications to the repo are possible throught the Pool.
     * @see MPool::add_repo_from_repodata_json
     * @see MPool::add_repo_from_packages
     * @see MPool::remove_repo
     */
    class RepoInfo
    {
    public:

        using RepoId = int;

        RepoInfo(const RepoInfo&) = default;
        RepoInfo(RepoInfo&&) = default;
        auto operator=(const RepoInfo&) -> RepoInfo& = default;
        auto operator=(RepoInfo&&) -> RepoInfo& = default;

        [[nodiscard]] auto id() const -> RepoId;

        [[nodiscard]] auto name() const -> std::string_view;

        [[nodiscard]] auto package_count() const -> std::size_t;

        [[nodiscard]] auto priority() const -> Priorities;

    private:

        ::Repo* m_ptr = nullptr;  // This is a view managed by libsolv pool

        explicit RepoInfo(::Repo* repo);

        friend class ::mamba::MPool;
        friend class ::mamba::MTransaction;  // As long as MTransaction leaks libsolv impl
        friend auto operator==(RepoInfo lhs, RepoInfo rhs) -> bool;
    };

    auto operator==(RepoInfo lhs, RepoInfo rhs) -> bool;
    auto operator!=(RepoInfo lhs, RepoInfo rhs) -> bool;
}
#endif
