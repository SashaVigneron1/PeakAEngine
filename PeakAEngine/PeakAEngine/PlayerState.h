#pragma once

class GameObject;

struct PlayerStateData 
{
    glm::vec2 newPos;
};

class PlayerState
{
public:
    PlayerState(const char* displayName = "", bool controlInput = false);
    ~PlayerState();

    void DeserializePlayerStateData(const std::vector<uint8_t>& data);
    std::vector<uint8_t> SerializePlayerStateData();

    GameObject* GetGameObject() const { return m_pGameObject; }

    void SetPeerId(const std::string& id) { m_PeerId = id; }
    std::string GetPeerId() const { return m_PeerId; }

    void SetDisplayName(const std::string& name) { m_DisplayName = name; }
    std::string GetDisplayName() const { return m_DisplayName; }

private:
    // State properties
    std::string m_DisplayName;
    std::string m_PeerId;

    glm::vec2 m_OldPos;

    GameObject* m_pGameObject;
};