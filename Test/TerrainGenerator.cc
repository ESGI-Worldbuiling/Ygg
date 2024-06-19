//
// Created by Enola on 19/06/2024.
//
#include "../Ygg/include/TerrainGenerator.hpp"
#include <gtest/gtest.h>
#include <fstream>

TEST(TerrainTest, GenerateHeightMap) {
	Ygg::TerrainGenerator terrainGenerator;
	int width = 50;
	int height = 10;
	auto heightMap = terrainGenerator.generateHeightMap(width, height);

	EXPECT_EQ(heightMap.size(), width * height);
	for (auto height : heightMap) {
		EXPECT_GE(height, 0.0f);
		EXPECT_LE(height, 1.0f);
	}
}

TEST(TerrainTest, GenerateGLTFModel) {
	Ygg::TerrainGenerator terrainGenerator;
	int width = 10;
	int height = 10;
	auto heightMap = terrainGenerator.generateHeightMap(width, height);
	auto model = terrainGenerator.generateGLTFModel(heightMap, width, height);

	EXPECT_FALSE(model.scenes.empty());
	EXPECT_FALSE(model.meshes.empty());
	EXPECT_FALSE(model.buffers.empty());
}

TEST(TerrainTest, SaveModel) {
	Ygg::TerrainGenerator terrainGenerator;
	std::string filename = "../../../../test_terrain.gltf";
	int width = 10;
	int height = 10;
	auto heightMap = terrainGenerator.generateHeightMap(width, height);
	auto model = terrainGenerator.generateGLTFModel(heightMap, width, height);
	bool saveResult = terrainGenerator.saveModel(filename, model);
	EXPECT_TRUE(saveResult) << "Failed to save model to file: " << filename;
	std::ifstream file(filename, std::ios::in | std::ios::binary);
	EXPECT_TRUE(file.is_open()) << "Failed to open file: " << filename;
	file.close();

	std::remove(filename.c_str());
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}