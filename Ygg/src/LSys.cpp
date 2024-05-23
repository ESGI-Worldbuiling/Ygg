#include "YggCpp/LSys.hpp"

namespace Ygg {
    std::string LSys::generateExpression(Ygg::LSysData props) {
        std::unordered_map<std::string, std::string> rulesMap;
        for (const auto& rule: props.rules) {
            rulesMap.insert({rule.substr(0,1), rule.substr(2, rule.size() - 1)});
        }
        std::string finalAxiom = props.axiom;
        for(int i = 0; i < props.iterations;i++) {
            std::string newAxiom = finalAxiom;
            for (auto & it : rulesMap) {
                std::string::size_type pos = 0;
                while((pos = newAxiom.find(it.first, pos)) != std::string::npos) {
                    newAxiom.replace(pos, it.first.length(), it.second);
                    pos += it.second.length();
                }
                finalAxiom = std::move(newAxiom);
            }
        }
        return finalAxiom;
    }
}