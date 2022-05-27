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

#include "serialization/serializer_cpp.hpp"
#include "serialization/serializer_c.hpp"
#include "serialization/deserializer_cpp.hpp"
#include "serialization/deserializer_c.hpp"

#include "common.hpp"

//Additional serialization factory functions
namespace eCAL
{
  namespace rmw
  {

    inline Serializer *CreateSerializer(const rosidl_typesupport_introspection_cpp::MessageMembers *members)
    {
      return new CppSerializer(members);
    }

    inline Serializer *CreateSerializer(const rosidl_typesupport_introspection_c__MessageMembers *members)
    {
      return new CSerializer(members);
    }

    inline Deserializer *CreateDeserializer(const rosidl_typesupport_introspection_cpp::MessageMembers *members)
    {
      return new CppDeserializer(members);
    }

    inline Deserializer *CreateDeserializer(const rosidl_typesupport_introspection_c__MessageMembers *members)
    {
      return new CDeserializer(members);
    }

  } // namespace rmw
} // namespace eCAL
