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

#include "rmw_ecal_shared_cpp/rmw/get_service_names_and_types.hpp"

#include <tuple>
#include <algorithm>

#include "rmw_ecal_shared_cpp/string_functions.hpp"

#include "internal/common.hpp"
#include "internal/graph.hpp"

namespace eCAL
{
  namespace rmw
  {

    rmw_ret_t rmw_get_service_names_and_types(const char *implementation_identifier,
                                              const rmw_node_t *node,
                                              rcutils_allocator_t *allocator,
                                              rmw_names_and_types_t *service_names_and_types)
    {
      RMW_CHECK_ARGUMENT_FOR_NULL(node, RMW_RET_INVALID_ARGUMENT);
      RMW_CHECK_ARGUMENT_FOR_NULL(allocator, RMW_RET_INVALID_ARGUMENT);
      RMW_CHECK_ARGUMENT_FOR_NULL(service_names_and_types, RMW_RET_INVALID_ARGUMENT);
      CHECK_RMW_IMPLEMENTATION(implementation_identifier, node);

      auto services = Graph::GetServices();

      auto init_success = ::rmw_names_and_types_init(service_names_and_types, services.size(), allocator);
      if (init_success != RMW_RET_OK)
      {
        RMW_SET_ERROR_MSG("Failed to initialize service_names_and_types.");
        return init_success;
      }

      try
      {
        std::transform(services.begin(), services.end(), RosArray::Begin(*service_names_and_types),
                       [allocator](auto &service) {
                         auto demangled_name{DemangleServiceName(service.name)};
                         auto name{ConstructCString(demangled_name)};

                         rcutils_string_array_t types;
                         auto init_success = rcutils_string_array_init(&types, 2, allocator);
                         if (init_success != RMW_RET_OK)
                         {
                           throw std::runtime_error("Failed to init types.");
                         }
                         types.data[0] = ConstructCString(service.request_type);
                         types.data[1] = ConstructCString(service.response_type);

                         return std::make_tuple(name, types);
                       });
      }
      catch (const std::runtime_error &e)
      {
        RMW_SET_ERROR_MSG(e.what());
        return RMW_RET_ERROR;
      }

      return RMW_RET_OK;
    }

  } // namespace rmw
} // namespace eCAL
