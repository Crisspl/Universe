#ifndef CAMERA_H
#define CAMERA_H

#include <FHL/Maths/vectors.h>

class Camera
{
public:
	enum class MoveDir
	{
		Forward,
		Backward,
		Right,
		Left
	};

public:
	explicit Camera(const fhl::Vec3f & _pos);

public:
	void move(float _offset, MoveDir _dir);
	void rotate(fhl::Vec2f _offset);
	void setRotation(fhl::Vec2f _rotation);

	const fhl::Vec3f & getPosition() const { return m_position; }
	fhl::Vec3f getCenter() const { return m_position + m_direction; }
	const fhl::Vec3f & getUpVector() const { return m_up; }

	bool hasChanged() const { return m_changed; }

private:
	void update();

private:
	fhl::Vec3f 
		m_position,
		m_direction,
		m_up,
		m_right;
	fhl::Vec2f m_rotation;
	bool m_changed;

	static constexpr fhl::Vec3f s_absUp = fhl::Vec3f::up();
};


#endif
