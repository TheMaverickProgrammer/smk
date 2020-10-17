// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include <smk/View.hpp>
#include <glm/gtc/constants.hpp>

namespace smk {

View::View() {
  Reset({0, 0, 1000, 1000});
}

View::View(const View& rhs) {
  this->operator=(rhs);
}

View::View(const smk::Rectangle& rect) {
  Reset(rect);
}

View::View(const glm::vec2& center, glm::vec2& size)
    : center_(center), size_(size) {}

/*View::View(const glm::mat4& mat) {
  SetTransform(mat);
}*/

View::~View() {}

View::View(View&& other) {
  std::swap(center_, other.center_);
  std::swap(size_, other.size_);
  std::swap(rotation_, other.rotation_);
  std::swap(viewport_, other.viewport_);
  std::swap(transform_updated_, other.transform_updated_);
  std::swap(invtransform_updated_, other.invtransform_updated_);
}

/// @brief Set the center position of the in-game view.
/// param x The center of the view along the horizontal axis.
/// param y The center of the view along the vertical axis.
void View::SetCenter(float x, float y) {
  center_ = {x, y};
  transform_updated_ = invtransform_updated_ = false;
}

/// @brief Set the center position of the in-game view.
/// param center The center of the view.
void View::SetCenter(const glm::vec2& center) {
  SetCenter(center.x, center.y);
}

/// @brief Set the size of the in-game view.
/// param width The size of the view along the horizontal axis.
/// param height The size of the view along the vertical axis.
void View::SetSize(float width, float height) {
  size_ = {width, height};
  transform_updated_ = invtransform_updated_ = false;
}

/// @brief Set the size of the in-game view.
/// param size The size of the view.
void View::SetSize(const glm::vec2& size) {
  SetSize(size.x, size.y);
}

void View::SetRotation(float angle) {
  rotation_ = static_cast<float>(fmod(angle, 360));

  if (rotation_ < 0)
    rotation_ += 360.f;

  transform_updated_ = invtransform_updated_ = false;
}

/*
// TODO: https://www.gamedev.net/forums/topic/644571-calculating-frustum-corners-from-a-projection-matrix/
// calculate edges, find the min-max box, then find the rotation
void View::SetTransform(const glm::mat4& mat) {
}
*/

const glm::vec2& View::GetCenter() const {
  return center_;
}

const glm::vec2& View::GetSize() const {
  return size_;
}

const float& View::GetRotation() const {
  return rotation_;
}

const smk::Rectangle View::GetViewport() const {
  return viewport_;
}

const glm::mat4& View::GetTransform() const {
  if (!transform_updated_) {
    float angle = rotation_ * glm::pi<float>() / 180.f;
    float cosine = static_cast<float>(std::cos(angle));
    float sine = static_cast<float>(std::sin(angle));
    float tx = -center_.x * cosine - center_.y * sine + center_.x;
    float ty = center_.x * sine - center_.y * cosine + center_.y;

    // Projection components
    float a = 2.f / size_.x;
    float b = -2.f / size_.y;
    float c = -a * center_.x;
    float d = -b * center_.y;

    // Rebuild the projection matrix from 3x3 matrix
    /*transform_ =
        glm::mat3{a * cosine, a * sine, a * tx + c, -b * sine, b * cosine,
                  b * ty + d, 0.f,      0.f,        1.f};*/
    transform_ = glm::mat4(1.0f);

    transform_updated_ = true;
  }

  return transform_;
}

const glm::mat4& View::GetInverseTransform() const {
  if (!invtransform_updated_) {
    inverse_transform_ = glm::inverse(transform_);
    invtransform_updated_ = true;
  }

  return inverse_transform_;
}

void View::Move(const glm::vec2& offset) {
  SetCenter(center_ + offset);
}

void View::Move(float x, float y) {
  SetCenter(center_ + glm::vec2{x, y});
}

void View::Rotate(float amount) {
  SetRotation(rotation_ + amount);
}

void View::Zoom(float factor) {
  SetSize(size_ * factor);
}

void View::Reset(const smk::Rectangle& rect) {
  center_ = {rect.left + rect.width() / 2.f, rect.top + rect.height() / 2.f};
  size_ = {rect.width(), rect.height()};
  rotation_ = 0.f;
  transform_updated_ = invtransform_updated_ = false;
}

}  // namespace smk
