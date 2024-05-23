#include "TreeGenerator.hpp"
#include "Core/Logger.hpp"

namespace Ygg {
    void TreeGenerator::generate(Ygg::TreeGenerator::TreeGeneratorData props) {
        std::unordered_map<std::string, std::string> rulesMap;
        for (const auto& rule: props.rules) {
            rulesMap.insert({rule.substr(0,1), rule.substr(2, rule.size() - 1)});
        }
        std::string finalAxiom;
        for(int i = 0; i <= props.iterations;i++) {
            std::string newAxiom = finalAxiom;
            for (auto it = rulesMap.begin(); it != rulesMap.end(); ++it) {
                std::string::size_type pos = 0;
                while((pos = newAxiom.find(it->first, pos)) != std::string::npos) {
                    newAxiom.replace(pos, it->first.length(), it->second);
                    pos += it->second.length();
                }
                finalAxiom = std::move(newAxiom);
            }
        }
    }
}