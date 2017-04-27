#include "Camera.h"

#include <FHL/Maths/mathsFuncs.h>

Camera::Camera(const fhl::Vec3f & _pos) :
	m_position(_pos),
	m_direction(fhl::Vec3f::forward()),
	m_up(fhl::Vec3f::up()),
	m_right(fhl::Vec3f::right()),
	m_rotation(fhl::Vec2f::left() * 90.f)
{
}

void Camera::move(float _offset, MoveDir _dir)
{
	if (_dir == MoveDir::Forward)
		m_position += m_direction * _offset;
	else if (_dir == MoveDir::Backward)
		m_position -= m_direction * _offset;
	else if (_dir == MoveDir::Right)
		m_position += m_right * _offset;
	else
		m_position -= m_right * _offset;
}

void Camera::rotate(fhl::Vec2f _offset)
{
	static const float sensitivity = 0.05f;

	m_rotation += _offset * sensitivity;
	update();
}

void Camera::setRotation(fhl::Vec2f _rotation)
{
	m_rotation = _rotation;
	update();
}

void Camera::update()
{
	m_direction = fhl::Vec3f(
		std::cos(fhl::toRadians(m_rotation.y)) * std::cos(fhl::toRadians(m_rotation.x)),
		std::sin(fhl::toRadians(m_rotation.y)),
		std::cos(fhl::toRadians(m_rotation.y)) * std::sin(fhl::toRadians(m_rotation.x))
	);
	m_direction = m_direction.normalized();
	m_right = m_direction.cross(s_absUp).normalized();
	m_up = m_right.cross(m_direction).normalized();
}

