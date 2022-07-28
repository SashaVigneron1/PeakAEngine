#pragma once

enum class GameMessageType
{
    Unknown,

    PlayerJoin,
    PlayerLeave,

    ObjectCreated,
    ObjectUpdated,
    ObjectDestroyed,

    AskForObjects,
};

class GameNetworkMessage
{
public:
    GameNetworkMessage();
    GameNetworkMessage(GameMessageType type, const std::string& objName, unsigned data);
    GameNetworkMessage(GameMessageType type, const std::string& objName, const std::string& data);
    GameNetworkMessage(GameMessageType type, const std::string& objName, const std::vector<uint8_t>& data);
    GameNetworkMessage(const std::vector<uint8_t>& data);
    ~GameNetworkMessage();

    GameMessageType MessageType() const { return m_type; }
    void MessageType(GameMessageType type) { m_type = type; }

    inline const std::vector<uint8_t>& RawData() { return m_data; }
    inline void RawData(const std::vector<uint8_t>& data) { m_data = data; }

    std::string StringValue();
    unsigned UnsignedValue();

    std::vector<uint8_t> Serialize() const;
    std::string ObjectName() const { return m_ObjectName; }

private:
    GameMessageType m_type;
    std::vector<uint8_t> m_data;
    int m_ObjectNameLength;
    std::string m_ObjectName;
};