// Copyright (C) 2017 J�r�me Leclercq
// This file is part of the "Erewhon Shared" project
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Shared/BaseApplication.hpp>
#include <iostream>

namespace ewn
{
	BaseApplication::~BaseApplication() = default;

	bool BaseApplication::Run()
	{
		for (const auto& reactorPtr : m_reactors)
		{
			reactorPtr->Poll([&](bool outgoing, std::size_t clientId, Nz::UInt32 data) { HandlePeerConnection(outgoing, clientId, data); },
			                 [&](std::size_t clientId, Nz::UInt32 data) { HandlePeerDisconnection(clientId, data); },
			                 [&](std::size_t clientId, Nz::NetPacket&& packet) { HandlePeerPacket(clientId, std::move(packet)); });
		}

		return Application::Run();
	}

	void BaseApplication::SetupNetwork(std::size_t peerPerReactor, const Nz::IpAddress& ipAddress)
	{
		m_peerPerReactor = peerPerReactor;

		m_reactors.emplace_back(std::make_unique<NetworkReactor>(0, ipAddress, peerPerReactor));
	}
}
