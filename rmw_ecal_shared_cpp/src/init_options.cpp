// Copyright 2020 Continental AG
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

#include "rmw_ecal_shared_cpp/rmw/init_options.hpp"

#include <rmw/impl/cpp/macros.hpp>

#include "internal/common.hpp"

namespace eCAL
{
  namespace rmw
  {
    rmw_ret_t rmw_init_options_init(const char *implementation_identifier, rmw_init_options_t *init_options, rcutils_allocator_t allocator)
    {
      RMW_CHECK_ARGUMENT_FOR_NULL(init_options, RMW_RET_INVALID_ARGUMENT);
      RCUTILS_CHECK_ALLOCATOR(&allocator, return RMW_RET_INVALID_ARGUMENT);

      init_options->instance_id = 0;
      init_options->implementation_identifier = implementation_identifier;
      init_options->allocator = allocator;
      init_options->impl = nullptr;

      return RMW_RET_OK;
    }

    rmw_ret_t rmw_init_options_copy(const char *implementation_identifier, const rmw_init_options_t *src, rmw_init_options_t *dst)
    {
      RMW_CHECK_ARGUMENT_FOR_NULL(src, RMW_RET_INVALID_ARGUMENT);
      RMW_CHECK_ARGUMENT_FOR_NULL(dst, RMW_RET_INVALID_ARGUMENT);
      CHECK_RMW_IMPLEMENTATION(implementation_identifier, src);

      *dst = *src;

      return RMW_RET_OK;
    }

    rmw_ret_t rmw_init_options_fini(const char *implementation_identifier, rmw_init_options_t *init_options)
    {
      RMW_CHECK_ARGUMENT_FOR_NULL(init_options, RMW_RET_INVALID_ARGUMENT);
      RCUTILS_CHECK_ALLOCATOR(&(init_options->allocator), return RMW_RET_INVALID_ARGUMENT);
      CHECK_RMW_IMPLEMENTATION(implementation_identifier, init_options);

      *init_options = ::rmw_get_zero_initialized_init_options();

      return RMW_RET_OK;
    }

  } // namespace rmw
} // namespace eCAL
