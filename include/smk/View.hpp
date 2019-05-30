// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_VIEW_HPP
#define SMK_VIEW_HPP

namespace smk {

class View {
 public:
  void SetCenter(float x, float y);
  void SetSize(float width, float height);

  float Left() const { return x_ - width_ / 2; };
  float Right() const { return x_ + width_ / 2; };
  float Top() const { return y_ - height_ / 2; };
  float Bottom() const { return y_ + height_ / 2; };

 public:
  float x_ = 0;
  float y_ = 0;
  float width_ = 0;
  float height_ = 0;
};

}  // namespace smk

#endif /* end of include guard: SMK_VIEW_HPP */