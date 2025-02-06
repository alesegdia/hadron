#include "body.h"

namespace hadron {


void *Body::GetUserData() {
    return m_userdata;
}

void Body::SetUserData(void *userData) {
    m_userdata = userData;
}

bool Body::IsDirty()
{
    return m_dirty;
}


const hadron::Vec2& Body::GetPosition()
{
	return m_currentPosition;
}

void Body::SetPosition(float x, float y)
{
	SetPosition(Vec2(x, y));
}

void Body::SetPosition(const Vec2& new_position)
{
	// might be worth to check if newpos != currentpos or might not
	if (!m_dirty)
	{
		m_dirty = true;
		m_previousPosition = m_currentPosition;
	}

	m_currentPosition = new_position;
	m_aabb.x = new_position.x;
	m_aabb.y = new_position.y;
}

void Body::Destroy()
{
	if (m_alive)
	{
		std::cout << "WARNING: trying to destroy an already dead body" << std::endl;
	}
	m_alive = false;
}

void Body::ClearDirty()
{
	m_dirty = false;
}

Body::Body() : m_aabb(AABB(0, 0, 0, 0))
{
	Internal_SetPosition(0, 0);
}

Body::Body(float x, float y, float w, float h) : m_aabb(AABB(x, y, w, h))
{
	Internal_SetPosition(x, y);
}

Body::Body(const AABB& aabb) : m_aabb(aabb)
{
	Internal_SetPosition(aabb.x, aabb.y);
}

const hadron::AABB& Body::GetLocalAABB() const
{
	return m_aabb;
}

void Body::GetLocalAABB(const AABB& other)
{
	this->m_aabb = other;
}

void Body::Internal_SetPosition(float x, float y)
{
	m_currentPosition.x = x;
	m_currentPosition.y = y;
	m_aabb.x = x;
	m_aabb.y = y;
}

}
