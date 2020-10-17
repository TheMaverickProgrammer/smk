// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_RECTANGLE
#define SMK_RECTANGLE

#include <glm/glm.hpp>
#include <algorithm>

namespace smk {

struct Rectangle {
  float left{0};
  float top{0};
  float right{1};
  float bottom{1};

  float width() const { return right - left; }
  float height() const { return bottom - top; }
};

}  // namespace smk

#endif /* end of include guard: SMK_RECTANGLE */
