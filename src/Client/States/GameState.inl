// Copyright (C) 2017 Jérôme Leclercq
// This file is part of the "Erewhon Shared" project
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Client/States/GameState.hpp>

namespace ewn
{
	inline GameState::GameState(StateData& stateData) :
	m_stateData(stateData)
	{
	}

	inline GameState::SpaceshipData& GameState::CreateServerEntity(std::size_t id)
	{
		if (id >= m_serverEntities.size())
			m_serverEntities.resize(id + 1);

		SpaceshipData& data = m_serverEntities[id];
		assert(!data.isValid);

		data.isValid = true;

		return data;
	}

	inline GameState::SpaceshipData& GameState::GetServerEntity(std::size_t id)
	{
		assert(id < m_serverEntities.size());

		SpaceshipData& data = m_serverEntities[id];
		assert(data.isValid);

		return data;
	}
}
