#include "TerrainGenerator.hpp"
#include <tiny_gltf.h>
#include <iostream>
#include <filesystem>
#include <vendor/PerlinNoise.hpp>
#include "Core/Math.hpp"
#include "Random/PerlinNoise.hpp"
namespace Ygg {

	std::vector<float> TerrainGenerator::generateHeightMap(int sizeX, int sizeY, float height, float scale, float lacunarity, float persistance, uint32_t layerCount) {
		siv::BasicPerlinNoise<float> pn {s_Seed};
		Perlin::HeightMap heightMap(sizeX, sizeY);
		if(scale <= 0) scale = 0.0001f;
		for (uint64_t y = 0; y < sizeY; ++y) {
			for (uint64_t x = 0; x < sizeX; ++x) {
				float& h = heightMap(x,y);
				for (int layer = 0; layer < layerCount; ++layer) {
					float realX = float(x) / scale;
					float realY = float(y) / scale;
					float freq = std::pow(lacunarity, layer);
					float ampl = std::pow(persistance, layer);
					realX *= freq;
					realY *= freq;
					h += pn.noise2D(realX,realY) * ampl;
//					h += pn.noise2D(realX,realY);
				}
				h *= height;
			}
		}
		return heightMap.Heights;
	}

	tinygltf::Model TerrainGenerator::generateGLTFModel(const std::vector<float>& heightMap, int width, int height, float scale, glm::vec4 colorMin, glm::vec4 colorMax) {
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
		std::vector<float> colors;

		float yMin = *std::min_element(heightMap.begin(), heightMap.end());
		float yMax = *std::max_element(heightMap.begin(), heightMap.end());

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
		vertices.reserve(height * width * 3);
		normals.reserve(height * width * 3);
		colors.reserve(height * width * 4);
		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {

				float h = heightMap[y * width + x];
				vertices.push_back(static_cast<float>(x) * scale);
				vertices.push_back(h);
				vertices.push_back(static_cast<float>(y) * scale);

				normals.push_back(0.0f);
				normals.push_back(1.0f);
				normals.push_back(0.0f);

				float t = (h - yMin) / (yMax - yMin);
				auto color = Math::Lerp(colorMin, colorMax, t);
				colors.push_back(color.r);
				colors.push_back(color.g);
				colors.push_back(color.b);
				colors.push_back(color.a);
			}
		}
		indices.reserve(height * width * 6);
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

		tinygltf::Accessor posAccessor, normAccessor,  colorAccessor, indexAccessor;
		tinygltf::Buffer buffer;
		tinygltf::BufferView posView, normView,  colorView, indexView;

		posAccessor.bufferView = 0;
		posAccessor.byteOffset = 0;
		posAccessor.componentType = TINYGLTF_COMPONENT_TYPE_FLOAT;
		posAccessor.count = vertices.size() / 3;
		posAccessor.type = TINYGLTF_TYPE_VEC3;
		posAccessor.maxValues = {float(width - 1) * scale, yMax, float(height - 1) * scale};
		posAccessor.minValues = {0.0f, yMin, 0.0f};

		normAccessor.bufferView = 1;
		normAccessor.byteOffset = 0;
		normAccessor.componentType = TINYGLTF_COMPONENT_TYPE_FLOAT;
		normAccessor.count = normals.size() / 3;
		normAccessor.type = TINYGLTF_TYPE_VEC3;

		colorAccessor.bufferView = 2;
		colorAccessor.byteOffset = 0;
		colorAccessor.componentType = TINYGLTF_COMPONENT_TYPE_FLOAT;
		colorAccessor.count = colors.size() / 4;
		colorAccessor.type = TINYGLTF_TYPE_VEC4;

		indexAccessor.bufferView = 3;
		indexAccessor.byteOffset = 0;
		indexAccessor.componentType = TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT;
		indexAccessor.count = indices.size();
		indexAccessor.type = TINYGLTF_TYPE_SCALAR;

		buffer.data.insert(buffer.data.end(), reinterpret_cast<const unsigned char*>(vertices.data()), reinterpret_cast<const unsigned char*>(vertices.data()) + vertices.size() * sizeof(float));
		buffer.data.insert(buffer.data.end(), reinterpret_cast<const unsigned char*>(normals.data()), reinterpret_cast<const unsigned char*>(normals.data()) + normals.size() * sizeof(float));
		buffer.data.insert(buffer.data.end(), reinterpret_cast<const unsigned char*>(colors.data()), reinterpret_cast<const unsigned char*>(colors.data()) + colors.size() * sizeof(float));
		buffer.data.insert(buffer.data.end(), reinterpret_cast<const unsigned char*>(indices.data()), reinterpret_cast<const unsigned char*>(indices.data()) + indices.size() * sizeof(uint16_t));

		posView.buffer = 0;
		posView.byteOffset = 0;
		posView.byteLength = vertices.size() * sizeof(float);
		posView.target = TINYGLTF_TARGET_ARRAY_BUFFER;

		normView.buffer = 0;
		normView.byteOffset = posView.byteOffset + posView.byteLength;
		normView.byteLength = normals.size() * sizeof(float);
		normView.target = TINYGLTF_TARGET_ARRAY_BUFFER;

		colorView.buffer = 0;
		colorView.byteOffset = normView.byteOffset + normView.byteLength;
		colorView.byteLength = colors.size() * sizeof(float);
		colorView.target = TINYGLTF_TARGET_ARRAY_BUFFER;

		indexView.buffer = 0;
		indexView.byteOffset = colorView.byteOffset + colorView.byteLength;
		indexView.byteLength = indices.size() * sizeof(uint16_t);
		indexView.target = TINYGLTF_TARGET_ELEMENT_ARRAY_BUFFER;

		model.accessors.push_back(posAccessor);
		model.accessors.push_back(normAccessor);
		model.accessors.push_back(colorAccessor);
		model.accessors.push_back(indexAccessor);

		model.bufferViews.push_back(posView);
		model.bufferViews.push_back(normView);
		model.bufferViews.push_back(colorView);
		model.bufferViews.push_back(indexView);

		model.buffers.push_back(buffer);

		tinygltf::Primitive primitive;
		primitive.attributes["POSITION"] = 0;
		primitive.attributes["NORMAL"] = 1;
		primitive.attributes["COLOR_0"] = 2;
		primitive.indices = 3;
		primitive.mode = TINYGLTF_MODE_TRIANGLES;

		mesh.primitives.push_back(primitive);
		model.meshes.push_back(mesh);

		return model;
	}

	Mesh TerrainGenerator::generateMesh(const std::vector<float> &heightMap, int width, int height, float scale, glm::vec4 colorMin, glm::vec4 colorMax) {
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;

		float yMin = *std::min_element(heightMap.begin(), heightMap.end());
		float yMax = *std::max_element(heightMap.begin(), heightMap.end());
		for (uint64_t y = 0; y < height; ++y) {
			for (uint64_t x = 0; x < width; ++x) {
				float h = heightMap[y * width + x];
				float t = (h - yMin) / (yMax - yMin);
				vertices.push_back(Vertex{glm::vec3{float(x)*scale,h, float(y)*scale}, glm::vec3{0,1,0}, Math::Lerp(colorMin, colorMax, t), glm::vec2{float(x)/float(width), float(y)/float(height)}});
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
		return {vertices, indices};
	}

	bool makeWritable(const std::string& filename) {
		// std::filesystem::permissions(filename, std::filesystem::perms::group_write | std::filesystem::perms::others_write | std::filesystem::perms::owner_write | std::filesystem::perms::group_read | std::filesystem::perms::others_read | std::filesystem::perms::owner_read);
		return true;
	}

	bool TerrainGenerator::saveModel(const std::string& filename, const tinygltf::Model& model) {
		tinygltf::TinyGLTF gltf;

		// Make the file writable if it's read-only
		if (!makeWritable(filename)) {
			std::cerr << "Failed to make the file writable: " << filename << std::endl;
			return false;
		}


		bool result{false};

		if(filename.ends_with("gltf"))
			result = gltf.WriteGltfSceneToFile(&model, filename, true, true, true, false);
		else if (filename.ends_with("glb"))
			result = gltf.WriteGltfSceneToFile(&model, filename, true, true, false, true);

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

	void TerrainGenerator::RegenerateSeed() {
		union {
			int is{0};
			unsigned int uis;
		};
		is = rand();
		s_Seed = uis;
	}

} // namespace Ygg
