//
// Created by Sayama on 18/06/2024.
//

#pragma once

#include "Mesh.hpp"
#include "Core/UUID.hpp"
#include "Core/SmartPointers.hpp"
#include <vector>
#include <cstdint>

namespace Ygg {

	class Scene {
	public:
		using SceneIterator = std::unordered_map<AssetHandle, Ref<Mesh>>::iterator;
		using ConstSceneIterator = std::unordered_map<AssetHandle, Ref<Mesh>>::const_iterator;
	public:
		Scene() = default;
		~Scene() = default;
		Scene(const std::vector<Ref<Mesh>>& meshes);
		Scene(std::initializer_list<Ref<Mesh>> meshes);

		[[nodiscard]] uint64_t size() const noexcept;

		Ref<Mesh>& operator[](AssetHandle index);
		const Ref<Mesh>& operator[](AssetHandle index) const;

		Ref<Mesh>& at(AssetHandle index);
		const Ref<Mesh>& at(AssetHandle index) const;

		SceneIterator begin();
		ConstSceneIterator begin() const;
		ConstSceneIterator cbegin() const;

		SceneIterator end();
		ConstSceneIterator end() const;
		ConstSceneIterator cend() const;

		void insert(const Ref<Mesh>& m);

		void erase(AssetHandle handle);
	public:
		void NextFrame();
	private:
		std::unordered_map<AssetHandle, Ref<Mesh>> m_ActiveMesh;
		std::unordered_map<AssetHandle, Ref<Mesh>> m_InactiveMesh;
	};

}// namespace Ygg
