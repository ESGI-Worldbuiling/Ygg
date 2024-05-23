#pragma once

namespace Ygg {
    class TreeGenerator {
    public:
        struct TreeGeneratorData {
            std::string axiom;
            std::vector<std::string> rules;
            int iterations;
            float alpha;
        };

        void generate(TreeGeneratorData props);
    };
}