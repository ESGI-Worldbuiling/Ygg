#pragma once

#include <tiny_gltf.h>
#include <vector>
#include <string>
#include <random>
#include "Render/Mesh.hpp"
namespace Ygg {

	class TerrainGenerator {
	public:
		// Constructeur par défaut
		TerrainGenerator();

		// Génère une carte de hauteur aléatoire pour le terrain
		std::vector<float> generateHeightMap(int width, int height);

		// Génère un modèle GLTF à partir de la carte de hauteur
		tinygltf::Model generateGLTFModel(const std::vector<float>& heightMap, int width, int height);

		Mesh generateMesh(const std::vector<float>& heightMap, int width, int height);

		// Sauvegarde du modèle GLTF dans un fichier
		bool saveModel(const std::string& filename, const tinygltf::Model& model);

		// Méthode principale pour générer le terrain et sauvegarder le modèle
		std::vector<float> generate(const std::string& filename);
	};

} // namespace Ygg
