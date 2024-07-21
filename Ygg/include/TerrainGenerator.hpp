#pragma once

#include <tiny_gltf.h>
#include <vector>
#include <string>
#include <random>
#include "Render/Mesh.hpp"
namespace Ygg {

	class TerrainGenerator {
	public:
		// Génère une carte de hauteur aléatoire pour le terrain
		static std::vector<float> generateHeightMap(int width, int height);

		// Génère un modèle GLTF à partir de la carte de hauteur
		static tinygltf::Model generateGLTFModel(const std::vector<float>& heightMap, int width, int height);

		static Mesh generateMesh(const std::vector<float>& heightMap, int width, int height);

		// Sauvegarde du modèle GLTF dans un fichier
		static bool saveModel(const std::string& filename, const tinygltf::Model& model);

		// Méthode principale pour générer le terrain et sauvegarder le modèle
		static std::vector<float> generate(const std::string& filename);
	};

} // namespace Ygg
