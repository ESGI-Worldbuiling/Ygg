#pragma once
#include <glm/glm.hpp>

namespace Ygg {
    struct LSysData {
        std::string axiom;
        std::vector<std::string> rules;
        int iterations;
        float alpha;
    };

    const std::array<char, 6> operators = {
            '+',
            '-',
            '>',
            '<',
            '&',
            '^'
    };

    class LSys {
    public:
        std::string generateExpression(LSysData props);
        std::vector<glm::vec3> generateTree(LSysData props);
    };
}