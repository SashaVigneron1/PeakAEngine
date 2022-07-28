#include "PeakAEnginePCH.h"
#include "GameNetworkMessage.h"


GameNetworkMessage::GameNetworkMessage() 
    : m_type(GameMessageType::Unknown)
    , m_ObjectNameLength{}
{
}

GameNetworkMessage::~GameNetworkMessage()
{
}

GameNetworkMessage::GameNetworkMessage(GameMessageType type, const std::string& objName, unsigned data)
{
    m_type = type;
    m_ObjectName = objName;
    m_ObjectNameLength = (int)m_ObjectName.length();
    m_data.resize(sizeof(unsigned));
    CopyMemory(m_data.data(), &data, sizeof(data));
}

GameNetworkMessage::GameNetworkMessage(GameMessageType type, const std::string& objName, const std::string& data)
{
    m_type = type;
    m_ObjectName = objName;
    m_ObjectNameLength = (int)m_ObjectName.length();
    m_data.resize(data.length() * sizeof(char));
    CopyMemory(m_data.data(), reinterpret_cast<const uint8_t*>(data.c_str()), m_data.size());
}

GameNetworkMessage::GameNetworkMessage(GameMessageType type, const std::string& objName, const std::vector<uint8_t>& data)
{
    m_type = type;
    m_ObjectName = objName;
    m_ObjectNameLength = (int)m_ObjectName.length();
    m_data = data;
}

std::string GameNetworkMessage::StringValue()
{
    if (!m_data.empty())
    {
        auto stringData = reinterpret_cast<char*>(m_data.data());
        return std::string(stringData, stringData + (m_data.size() / sizeof(char)));
    }

    return "";
}

unsigned
GameNetworkMessage::UnsignedValue()
{
    if (!m_data.empty())
    {
        return *(reinterpret_cast<unsigned*>(m_data.data()));
    }

    return 0;
}



GameNetworkMessage::GameNetworkMessage(const std::vector<uint8_t>& data)
{
    if (data.size() < (sizeof(GameMessageType) + sizeof(uint8_t)))
    {
        // Invalid message
        return;
    }

    size_t objNameSize{};
    CopyMemory(&objNameSize, data.data(), sizeof(size_t));

    m_ObjectName.resize(objNameSize);
    CopyMemory(m_ObjectName.data(), data.data() + sizeof(size_t), objNameSize);

    CopyMemory(&m_type, data.data() + sizeof(size_t) + objNameSize, sizeof(GameMessageType));

    m_data.resize(data.size() - sizeof(size_t) - objNameSize - sizeof(GameMessageType));
    CopyMemory(m_data.data(), data.data() + sizeof(size_t) + objNameSize + sizeof(GameMessageType), m_data.size());
}

std::vector<uint8_t>
GameNetworkMessage::Serialize() const
{
    if (m_type == GameMessageType::Unknown || m_data.empty())
    {
        return std::vector<uint8_t>();
    }

    size_t length = sizeof(size_t) + m_ObjectName.size() + sizeof(GameMessageType) + m_data.size();
    uint8_t* buffer = new uint8_t[length];

    size_t objNameSize = m_ObjectName.size();
    CopyMemory(buffer, &objNameSize, sizeof(size_t));
    CopyMemory(buffer + sizeof(size_t), m_ObjectName.data(), objNameSize);
    CopyMemory(buffer + sizeof(size_t) + objNameSize, &m_type, sizeof(GameMessageType));
    CopyMemory(buffer + sizeof(size_t) + objNameSize + sizeof(GameMessageType), m_data.data(), m_data.size());

    auto packet = std::vector<uint8_t>(buffer, buffer + length);

    delete[] buffer;

    return packet;
}