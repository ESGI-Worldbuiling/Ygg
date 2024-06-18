//
// Created by Sayama on 18/06/2024.
//

#include "Core/Macro.hpp"
#include "Render/Scene.hpp"
#include <exception>

namespace Ygg {
	Scene::Scene(const std::vector<Ref<Mesh>>& meshes)
	{
		for(const auto& m : meshes)
		{
			m_ActiveMesh.insert({m->m_Handle, m});
		}
	}

	Scene::Scene(std::initializer_list<Ref<Mesh>> meshes)
	{
		for(const auto& m : meshes)
		{
			m_ActiveMesh.insert({m->m_Handle, m});
		}
	}

	Ref<Mesh> &Scene::operator[](AssetHandle index) {
		return m_ActiveMesh.at(index);
	}

	const Ref<Mesh> &Scene::operator[](AssetHandle index) const {
		return m_ActiveMesh.at(index);
	}

	Ref<Mesh> &Scene::at(AssetHandle index) {
		YGG_ASSERT(size() > 0, "The Scene is empty.");
		YGG_ASSERT(m_ActiveMesh.contains(index), "The ID '{}' is in the scene.", index.string());
		return m_ActiveMesh.at(index);
	}

	const Ref<Mesh> &Scene::at(AssetHandle index) const {
		YGG_ASSERT(size() > 0, "The Scene is empty.");
		YGG_ASSERT(m_ActiveMesh.contains(index), "The ID '{}' is in the scene.", index.string());
		return m_ActiveMesh.at(index);
	}

	uint64_t Scene::size() const noexcept {
		return m_ActiveMesh.size();
	}

	Scene::SceneIterator Scene::begin() {
		return m_ActiveMesh.begin();
	}
	Scene::ConstSceneIterator Scene::begin() const {
		return m_ActiveMesh.cbegin();
	}
	Scene::ConstSceneIterator Scene::cbegin() const {
		return m_ActiveMesh.cbegin();
	}

	Scene::SceneIterator Scene::end() {
		return m_ActiveMesh.end();
	}

	Scene::ConstSceneIterator Scene::end() const {
		return m_ActiveMesh.cend();
	}

	Scene::ConstSceneIterator Scene::cend() const {
		return m_ActiveMesh.cend();
	}

	void Scene::insert(const Ref<Mesh> &m) {
		m_ActiveMesh.insert_or_assign(m->m_Handle ,m);
	}

	void Scene::erase(AssetHandle handle) {
		if(!m_ActiveMesh.contains(handle)) return;
		m_InactiveMesh.insert({handle, m_ActiveMesh.at(handle)});
		m_ActiveMesh.erase(handle);
	}

	void Scene::NextFrame() {
		m_InactiveMesh.clear();
	}

}// namespace Ygg