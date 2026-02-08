#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace DGE
{
	class Camera2D
	{
	private:
		glm::vec2 pos_;
		float zoom_;
		float near_;
		float far_;
		float width_;
		float height_;
		glm::mat4 transform;

	public:
		Camera2D(glm::vec2 pos, float zoom, float width, float height, float near, float far) : pos_(pos), zoom_(zoom),
			near_(near), far_(far), width_(width), height_(height), transform(1.f)
		{
			calculateTransformationMatrix();
		};
		~Camera2D()
		{
		};

		inline void calculateTransformationMatrix() { 
			transform = glm::mat4(1.0f);
			transform = glm::scale(transform, glm::vec3(zoom_, zoom_, 1.0f));
			transform = glm::translate(transform, glm::vec3(-pos_.x, -pos_.y, 0.0f));
			glm::mat4 projection = glm::ortho(0.f, (float)width_, 0.0f, (float)height_, near_, far_);
			transform = projection * transform;
		}

		inline void setPosition(glm::vec2 newPos) { pos_ = newPos; calculateTransformationMatrix(); }
		inline void setZoom(float zoom) { zoom_ = glm::max(zoom, 0.01f); calculateTransformationMatrix(); }
		inline void move(glm::vec2 displacement) { pos_ += displacement; calculateTransformationMatrix(); }
		inline void zoom(float zoom) { setZoom(zoom_+zoom); }
		inline glm::vec2 getPos() const { return pos_; }
		inline glm::mat4 getTransform() const { return transform; }
		inline float getZoom() const { return zoom_; }
	};
}