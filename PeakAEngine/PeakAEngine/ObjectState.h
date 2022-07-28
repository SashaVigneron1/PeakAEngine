#pragma once

class GameObject;

struct ObjectStateData
{
    int objectTypeId;
    glm::vec2 newPos;
};

class ObjectState
{
public:
    ObjectState(const std::string& displayName, const std::string& id);
    ~ObjectState() = default;
    ObjectState(const ObjectState& other) = delete;
    ObjectState(ObjectState&& other) noexcept = delete;
    ObjectState& operator=(const ObjectState& other) = delete;
    ObjectState& operator=(ObjectState&& other) noexcept = delete;

    virtual void DeserializeObjectStateData(const std::vector<uint8_t>& data);
    virtual std::vector<uint8_t> SerializeObjectStateData();

    std::string GetDisplayName() const { return m_DisplayName; }

    void SetGameObject(GameObject* obj) { m_pGameObject = obj; }
    GameObject* GetGameObject() const { return m_pGameObject; }

    int GetTypeId() const { return m_ObjectTypeId; }
    void SetTypeId(int id) { m_ObjectTypeId = id; }
private:
    std::string m_DisplayName;
    std::string m_PeerId;
    glm::vec2 m_Position;

    int m_ObjectTypeId;
    GameObject* m_pGameObject;
};

