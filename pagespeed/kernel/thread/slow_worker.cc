/*
 * Copyright 2011 Google Inc.
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
 */

// Author: morlovich@google.com (Maksim Orlovich)
//
// Implements SlowWorker, which runs a single task only in a background thread.

#include "pagespeed/kernel/thread/slow_worker.h"

#include "pagespeed/kernel/base/function.h"

namespace net_instaweb {

class ThreadSystem;

SlowWorker::SlowWorker(StringPiece thread_name, ThreadSystem* runtime)
    : Worker(thread_name, runtime) {
}

SlowWorker::~SlowWorker() {
}

void SlowWorker::RunIfNotBusy(Function* closure) {
  bool ok = QueueIfPermitted(closure);
  if (!ok) {
    closure->CallCancel();
  }
}

bool SlowWorker::IsPermitted(Function* closure) {
  return NumJobs() == 0;
}

}  // namespace net_instaweb
