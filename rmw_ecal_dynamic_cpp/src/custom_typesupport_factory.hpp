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

#pragma once

#include <rosidl_typesupport_introspection_cpp/message_introspection.hpp>
#include <rosidl_typesupport_introspection_c/message_introspection.h>
#include <rosidl_typesupport_introspection_cpp/identifier.hpp>
#include <rosidl_typesupport_introspection_c/identifier.h>

#include "typesupport/message_typesupport_c.hpp"
#include "typesupport/message_typesupport_cpp.hpp"
#include "typesupport/service_typesupport_c.hpp"
#include "typesupport/service_typesupport_cpp.hpp"

namespace eCAL
{
  namespace rmw
  {
    class CustomTypeSupportFactory : public TypesupportFactory
    {
      MessageTypeSupport *Create(const rosidl_message_type_support_t *type_support) const override
      {
        auto ts = get_message_typesupport_handle(type_support, rosidl_typesupport_introspection_cpp::typesupport_identifier);
        if (ts != nullptr)
        {
          return new CppMessageTypeSupport(ts);
        }

        ts = get_message_typesupport_handle(type_support, rosidl_typesupport_introspection_c__identifier);
        if (ts != nullptr)
        {
          return new CMessageTypeSupport(ts);
        }

        throw std::runtime_error("Unsupported type support.");
      }

      ServiceTypeSupport *Create(const rosidl_service_type_support_t *type_support) const override
      {
        auto ts = get_service_typesupport_handle(type_support, rosidl_typesupport_introspection_cpp::typesupport_identifier);
        if (ts != nullptr)
        {
          return new CppServiceTypeSupport(ts);
        }

        ts = get_service_typesupport_handle(type_support, rosidl_typesupport_introspection_c__identifier);
        if (ts != nullptr)
        {
          return new CServiceTypeSupport(ts);
        }
        throw std::runtime_error("Unsupported type support.");
      }
    };

  } // namespace rmw
} // namespace eCAL
