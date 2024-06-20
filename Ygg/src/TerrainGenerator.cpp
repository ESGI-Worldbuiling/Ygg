#include "../include/TerrainGenerator.hpp"
#include <tiny_gltf.h>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
namespace Ygg {

	TerrainGenerator::TerrainGenerator() = default;

	std::vector<float> TerrainGenerator::generateHeightMap(int width, int height) {
		std::vector<float> heightMap(width * height);
		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {
				heightMap[y * width + x] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
			}
		}
		return heightMap;
	}

	tinygltf::Model TerrainGenerator::generateGLTFModel(const std::vector<float>& heightMap, int width, int height) {
		tinygltf::Model model;
		tinygltf::Scene scene;
		scene.name = "TerrainScene";
		model.scenes.push_back(scene);
		model.defaultScene = 0;

		tinygltf::Mesh mesh;
		tinygltf::Node node;
		node.mesh = 0;
		model.nodes.push_back(node);
		model.scenes[0].nodes.push_back(0);

		std::vector<float> vertices;
		std::vector<uint16_t> indices;
		std::vector<float> normals;

		/*std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<float> heightDist(0.0f, 10.0f);
std::uniform_real_distribution<float> normalDist(-1.0f, 1.0f);

/*for (int y = 0; y < height; ++y) {
	for (int x = 0; x < width; ++x) {
		// Generate random heights
		float randomHeight = heightMap[y * width + x] + heightDist(gen);

// Position
vertices.push_back(static_cast<float>(x));
vertices.push_back(randomHeight);
vertices.push_back(static_cast<float>(y));


normals.push_back(normalDist(gen));
normals.push_back(normalDist(gen));
normals.push_back(normalDist(gen));
}
}*/
		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {

				vertices.push_back(static_cast<float>(x));
				vertices.push_back(heightMap[y * width + x]);
				vertices.push_back(static_cast<float>(y));

				normals.push_back(0.0f);
				normals.push_back(1.0f);
				normals.push_back(0.0f);
			}
		}

		for (int y = 0; y < height - 1; ++y) {
			for (int x = 0; x < width - 1; ++x) {
				int topLeft = y * width + x;
				int topRight = topLeft + 1;
				int bottomLeft = topLeft + width;
				int bottomRight = bottomLeft + 1;

				indices.push_back(topLeft);
				indices.push_back(bottomLeft);
				indices.push_back(topRight);

				indices.push_back(topRight);
				indices.push_back(bottomLeft);
				indices.push_back(bottomRight);
			}
		}

		tinygltf::Accessor posAccessor, normAccessor, indexAccessor;
		tinygltf::Buffer buffer;
		tinygltf::BufferView posView, normView, indexView;

		posAccessor.bufferView = 0;
		posAccessor.byteOffset = 0;
		posAccessor.componentType = TINYGLTF_COMPONENT_TYPE_FLOAT;
		posAccessor.count = vertices.size() / 3;
		posAccessor.type = TINYGLTF_TYPE_VEC3;
		posAccessor.maxValues = {8.0f, 10.0f, 16.0f};
		posAccessor.minValues = {-1.0f, -1.0f, -1.0f};

		normAccessor.bufferView = 1;
		normAccessor.byteOffset = 0;
		normAccessor.componentType = TINYGLTF_COMPONENT_TYPE_FLOAT;
		normAccessor.count = normals.size() / 3;
		normAccessor.type = TINYGLTF_TYPE_VEC3;

		indexAccessor.bufferView = 2;
		indexAccessor.byteOffset = 0;
		indexAccessor.componentType = TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT;
		indexAccessor.count = indices.size();
		indexAccessor.type = TINYGLTF_TYPE_SCALAR;

		buffer.data.insert(buffer.data.end(), reinterpret_cast<const unsigned char*>(vertices.data()), reinterpret_cast<const unsigned char*>(vertices.data()) + vertices.size() * sizeof(float));
		buffer.data.insert(buffer.data.end(), reinterpret_cast<const unsigned char*>(normals.data()), reinterpret_cast<const unsigned char*>(normals.data()) + normals.size() * sizeof(float));
		buffer.data.insert(buffer.data.end(), reinterpret_cast<const unsigned char*>(indices.data()), reinterpret_cast<const unsigned char*>(indices.data()) + indices.size() * sizeof(uint16_t));

		posView.buffer = 0;
		posView.byteOffset = 0;
		posView.byteLength = vertices.size() * sizeof(float);
		posView.target = TINYGLTF_TARGET_ARRAY_BUFFER;

		normView.buffer = 0;
		normView.byteOffset = posView.byteOffset + posView.byteLength;
		normView.byteLength = normals.size() * sizeof(float);
		normView.target = TINYGLTF_TARGET_ARRAY_BUFFER;

		indexView.buffer = 0;
		indexView.byteOffset = normView.byteOffset + normView.byteLength;
		indexView.byteLength = indices.size() * sizeof(uint16_t);
		indexView.target = TINYGLTF_TARGET_ELEMENT_ARRAY_BUFFER;

		model.accessors.push_back(posAccessor);
		model.accessors.push_back(normAccessor);
		model.accessors.push_back(indexAccessor);

		model.bufferViews.push_back(posView);
		model.bufferViews.push_back(normView);
		model.bufferViews.push_back(indexView);

		model.buffers.push_back(buffer);

		tinygltf::Primitive primitive;
		primitive.indices = 2;
		primitive.attributes["POSITION"] = 0;
		primitive.attributes["NORMAL"] = 1;
		primitive.mode = TINYGLTF_MODE_TRIANGLES;

		mesh.primitives.push_back(primitive);
		model.meshes.push_back(mesh);

		return model;
	}

	bool makeWritable(const std::string& filename) {
		// Change file permissions to read-write for owner, group, and others
		if (chmod(filename.c_str(), S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH) == -1) {
			std::cerr << "Failed to change file permissions for: " << filename << std::endl;
			return false;
		}
		return true;
	}

	bool TerrainGenerator::saveModel(const std::string& filename, const tinygltf::Model& model) {
		tinygltf::TinyGLTF gltf;

		// Make the file writable if it's read-only
		if (!makeWritable(filename)) {
			std::cerr << "Failed to make the file writable: " << filename << std::endl;
			return false;
		}


		bool result = gltf.WriteGltfSceneToFile(&model, filename, true, true, true, true);
		if (!result) {
			std::cerr << "Failed to save GLTF model to file: " << filename << std::endl;
			return false;
		} else {
			std::cout << "GLTF model saved successfully to file: " << filename << std::endl;
		}

		return true;
	}




	std::vector<float> TerrainGenerator::generate(const std::string& filename) {
		int width = 100;
		int height = 100;
		auto heightMap = generateHeightMap(width, height);
		auto model = generateGLTFModel(heightMap, width, height);
		saveModel(filename, model);
		return heightMap;
	}

} // namespace Ygg
