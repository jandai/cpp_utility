/*
 * Copyright 2019-present jan dai <jandai@126.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

#include <atomic>
#include <thread>

namespace jan {

struct NullMutex {
  NullMutex()  = default;

  ~NullMutex() = default;

  inline void lock() {}

  inline void unlock() {}

  inline bool try_lock() { 
    return true;
  }
};

class SpinMutex {
 public:
  inline SpinMutex() : flag(false) {}

  ~SpinMutex() = default;

  inline void lock() {
    while (!try_lock()) {
      std::this_thread::yield();
    }
  }

  inline void unlock() {
    flag.clear(std::memory_order_release);
  }

  inline bool try_lock() {
    return !flag.test_and_set(std::memory_order_acq_rel);
  }

 private:
  std::atomic_flag flag;
};

} // namespace jan
