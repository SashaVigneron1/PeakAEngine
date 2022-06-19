#pragma once

class b2World;
class ContactListener;
class BoxCollider;
class RigidBody;

class PhysicsHandler final
{
public:
	PhysicsHandler();
	~PhysicsHandler();

	PhysicsHandler(const PhysicsHandler& other) = delete;
	PhysicsHandler(PhysicsHandler&& other) = delete;
	PhysicsHandler& operator=(const PhysicsHandler& other) = delete;
	PhysicsHandler& operator=(PhysicsHandler&& other) = delete;

	void UpdatePhysics() const;

	void AddRigidBody(RigidBody* rigidBody, int type, bool fixedRotation, float gravityScale);
	void RemoveRigidBody(RigidBody* rigidBody);

private:
	std::unique_ptr<b2World> m_pPhysicsWorld;
	std::unique_ptr<ContactListener> m_pContactListener;

	std::vector<RigidBody*> m_pRigidBodies;
};

