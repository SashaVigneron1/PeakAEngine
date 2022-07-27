#pragma once

enum class GameMessageType
{
    Unknown,
    GameStart,
    GameTurn,
    GameOver,
    GameLeft,
    GameSettings,
    PlayerState,
    PowerUpSpawn,
    WorldSetup,
    WorldData,
    ShipSpawn,
    ShipInput,
    ShipData,
    ShipDeath,

    PlayerJoin,
    PlayerLeave,
    ObjectMove,

};

class GameNetworkMessage
{
public:
    GameNetworkMessage();
    GameNetworkMessage(GameMessageType type, unsigned data);
    GameNetworkMessage(GameMessageType type, const std::string& data);
    GameNetworkMessage(GameMessageType type, const std::vector<uint8_t>& data);
    GameNetworkMessage(const std::vector<uint8_t>& data);
    ~GameNetworkMessage();

    GameMessageType MessageType() const { return m_type; }
    void MessageType(GameMessageType type) { m_type = type; }

    inline const std::vector<uint8_t>& RawData() { return m_data; }
    inline void RawData(const std::vector<uint8_t>& data) { m_data = data; }

    std::string StringValue();
    unsigned UnsignedValue();

    std::vector<uint8_t> Serialize() const;

private:
    GameMessageType m_type;
    std::vector<uint8_t> m_data;
};