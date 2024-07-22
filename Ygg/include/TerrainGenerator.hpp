#pragma once

#include <tiny_gltf.h>
#include <vector>
#include <string>
#include <random>
#include "Render/Mesh.hpp"
namespace Ygg {

	class TerrainGenerator {
	public:
		static void RegenerateSeed();

		// Génère une carte de hauteur aléatoire pour le terrain
		static std::vector<float> generateHeightMap(int sizeX, int sizeY, float height = 1.0f, float scale = 1.02349723784, float lacunarity = 2.0, float persistance = 0.5, uint32_t layerCount = 3);

		// Génère un modèle GLTF à partir de la carte de hauteur
		static tinygltf::Model generateGLTFModel(const std::vector<float>& heightMap, int width, int height, float scale = 1, glm::vec4 colorMin = {0,0,0,1}, glm::vec4 colorMax = {1,1,1,1});

		static Mesh generateMesh(const std::vector<float>& heightMap, int width, int height, float scale = 1, glm::vec4 colorMin = {0,0,0,1}, glm::vec4 colorMax = {1,1,1,1});

		// Sauvegarde du modèle GLTF dans un fichier
		static bool saveModel(const std::string& filename, const tinygltf::Model& model);

		// Méthode principale pour générer le terrain et sauvegarder le modèle
		static std::vector<float> generate(const std::string& filename);
	private:
		static inline uint32_t s_Seed{93475u};
	};

} // namespace Ygg
