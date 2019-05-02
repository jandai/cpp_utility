
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

#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <algorithm>

namespace jan {

template<typename T>
inline T to(const std::string& s) {
  T val;
  std::stringstream ss(s);
  ss >> val;
  return val;
}

template<typename T = std::string>
inline std::vector<T> split(const std::string& str, char delim) {
  std::stringstream ss(str);
  std::vector<T> vec;
  std::string line;
  while (std::getline(ss, line, delim)) {
    vec.emplace_back(to<T>(line));
  }
  return vec;
}

template<typename Container>
inline std::string join(const Container& container, const char* delim = " ") {
  auto b = std::begin(container); // for c-style like array
  auto e = std::end(container);
  if (0 == std::distance(b, e)) {
    return { };
  }

  std::stringstream ss;
  std::copy(b, e, std::ostream_iterator<decltype(*b)>(ss, delim));

  auto str = ss.str();
  return str.substr(0, str.length() - 1);
}

template<typename Container>
inline std::string join(const Container& container, const char delim = ' ') {
  std::string s(1, delim);
  return join(container, s.c_str());
}

inline std::string& trim_left(std::string& str, const std::string& charlist = " \r\n\t") {
  str.erase(0, str.find_first_not_of(charlist));
  return str;
}

inline std::string& trim_right(std::string& str, const std::string& charlist = " \r\n\t") {
  str.erase(str.find_last_not_of(charlist) + 1);
  return str;
}

inline std::string& trim(std::string& str, const std::string& charlist = " \r\n\t") {
  trim_left(str, charlist);
  return trim_right(str, charlist);
}

}