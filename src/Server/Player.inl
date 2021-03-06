// Copyright (C) 2017 Jérôme Leclercq
// This file is part of the "Erewhon Server" project
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Server/Player.hpp>
#include <Nazara/Network/NetPacket.hpp>
#include <Shared/Protocol/Packets.hpp>

namespace ewn
{
	inline Arena* Player::GetArena() const
	{
		return m_arena;
	}

	inline const std::string & Player::GetName() const
	{
		return m_login;
	}

	inline bool Player::IsAuthenticated() const
	{
		return m_authenticated;
	}

	inline void Player::Disconnect(Nz::UInt32 data)
	{
		m_networkReactor.DisconnectPeer(m_peerId, data);
	}

	template<typename T>
	void Player::SendPacket(const T& packet)
	{
		const auto& command = m_commandStore.GetOutgoingCommand<T>();
		
		Nz::NetPacket data;
		m_commandStore.SerializePacket(data, packet);

		m_networkReactor.SendData(m_peerId, command.channelId, command.flags, std::move(data));
	}
}
