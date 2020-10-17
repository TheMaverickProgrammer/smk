// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_VIEW_HPP
#define SMK_VIEW_HPP

#include <glm/glm.hpp>
#include <smk/Rectangle.hpp>

namespace smk {

/// Represent the area in the game to be drawn on the screen. To preserve the
/// screen ratio, the view ratio must be the same.
class View {
 public:
  View();
  View(const View&);
  View(View&&);
  explicit View(const smk::Rectangle& rect);
  explicit View(const glm::vec2& center, glm::vec2& size);
  // TODO: explicit View(const glm::mat4& mat);
  virtual ~View();

  View& operator=(const View&);

  void SetCenter(float x, float y);
  void SetCenter(const glm::vec2& center);
  void SetSize(float width, float height);
  void SetSize(const glm::vec2& size);
  void SetRotation(float angle);
  void SetTransform(const glm::mat4& mat);

  const glm::vec2& GetCenter() const;
  const glm::vec2& GetSize() const;
  const float& GetRotation() const;
  const smk::Rectangle GetViewport() const;
  const glm::mat4& GetTransform() const;
  const glm::mat4& GetInverseTransform() const;

  void Move(const glm::vec2& offset);
  void Move(float x, float y);
  void Rotate(float amount);
  void Zoom(float factor);
  void Reset(const smk::Rectangle& rect);

  /*float Left() const { return x_ - width_ / 2; };     /// <
  float Right() const { return x_ + width_ / 2; };    /// <
  float Top() const { return y_ - height_ / 2; };     /// <
  float Bottom() const { return y_ + height_ / 2; };  /// < */

 private:
  glm::vec2 center_{}; 
  glm::vec2 size_{};
  float rotation_{0};
  smk::Rectangle viewport_{0, 0, 1, 1};
  mutable glm::mat4 transform_{};
  mutable glm::mat4 inverse_transform_{};
  mutable bool transform_updated_{false};
  mutable bool invtransform_updated_{false};
};

inline View& View::operator=(const View& rhs) {
  center_ = rhs.center_;
  size_ = rhs.size_;
  rotation_ = rhs.rotation_;
  viewport_ = rhs.viewport_;
  transform_ = rhs.transform_;
  inverse_transform_ = rhs.inverse_transform_;
  transform_updated_ = rhs.transform_updated_;
  invtransform_updated_ = rhs.invtransform_updated_;

  return *this;
}

}  // namespace smk

#endif /* end of include guard: SMK_VIEW_HPP */
