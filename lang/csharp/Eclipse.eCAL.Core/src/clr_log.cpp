/* ========================= eCAL LICENSE =================================
 *
 * Copyright (C) 2016 - 2025 Continental Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * ========================= eCAL LICENSE =================================
*/

#include "clr_log.h"
#include "clr_common.h"

#include <ecal/log.h>

using namespace System;
using namespace Eclipse::eCAL::Core;
using namespace Internal;

void Logging::Log(eLoggingLogLevel level, System::String^ message)
{
  // Convert the managed string to a native std::string
  std::string nativeMsg = StringToStlString(message);
  
  // Cast the managed LogLevel to the native eCAL::Logging::eLogLevel.
  // The values match, so a static_cast is sufficient.
  ::eCAL::Logging::Log(eLoggingLogLevelHelper::ToNative(level), nativeMsg);
}

array<Byte>^ Logging::GetSerializedLogging()
{
  std::string logging;
  if (!::eCAL::Logging::GetLogging(logging))
  {
    // If the call failed, return nullptr
    return nullptr;
  }
  
  return StlStringToByteArray(logging);
}

SLogging^ Logging::GetLogging()
{
  ::eCAL::Logging::SLogging logging;;
  if (!::eCAL::Logging::GetLogging(logging))
  {
    // If the call failed, return nullptr
    return nullptr;
  }

  // Create a managed SLogging instance and populate it with the native data
  SLogging^ managedLogging = SLogging::FromNative(logging);
  return managedLogging;
}
