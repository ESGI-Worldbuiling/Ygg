#include "YggCpp/LSys.hpp"
//#include "glm/gtx/transform.hpp"

namespace Ygg {
    /*std::string LSys::generateExpression(Ygg::LSysData props) {
        std::unordered_map<std::string, std::string> rulesMap;
        for (const auto& rule : props.rules) {
            rulesMap.insert({rule.substr(0, 1), rule.substr(2)});
        }
        std::string finalAxiom = props.axiom;
        for (int i = 0; i < props.iterations; i++) {
            std::string newAxiom;
            for (char ch : finalAxiom) {
                std::string chStr(1, ch);
                if (rulesMap.find(chStr) != rulesMap.end()) {
                    newAxiom += rulesMap[chStr];
                } else {
                    newAxiom += ch;
                }
            }
            finalAxiom = std::move(newAxiom);
        }
        return finalAxiom;
    }

    std::vector<glm::vec3> LSys::generateTree(Ygg::LSysData props) {
        std::string expression = generateExpression(props);
        std::vector<glm::vec3> positionStack;
        std::vector<glm::vec3> positions = {glm::vec3()};
        glm::vec3 nextPos = positions[0];
        glm::vec4 nextVector = glm::vec4(0.0,0.0,1.0,0.0);
        float rad = glm::radians(props.alpha);
        for(auto character: expression) {
            switch (character) {
                case 'F':
                    nextPos += glm::vec3(nextVector);
                    positions.push_back(nextPos);
                    break;
                case '+':
                    nextVector = glm::rotate(glm::mat4(1.0f), rad, glm::vec3(0.0,0.0,1.0)) * nextVector;
                    break;
                case '-':
                    nextVector = glm::rotate(glm::mat4(1.0f), -rad, glm::vec3(0.0,0.0,1.0)) * nextVector;
                    break;
                case '&':
                    nextVector = glm::rotate(glm::mat4(1.0f), -rad, glm::vec3(0.0,1.0,0.0)) * nextVector;
                    break;
                case '^':
                    nextVector = glm::rotate(glm::mat4(1.0f), rad, glm::vec3(0.0,1.0,0.0)) * nextVector;
                    break;
                case '<':
                    nextVector = glm::rotate(glm::mat4(1.0f), -rad, glm::vec3(1.0,0.0,0.0)) * nextVector;
                    break;
                case '>':
                    nextVector = glm::rotate(glm::mat4(1.0f), rad, glm::vec3(1.0,0.0,0.0)) * nextVector;
                    break;
                case '|':
                    // TODO : Add 180° turn
                    break;
                case '[':
                    positionStack.push_back(nextPos);
                    break;
                case ']':
                    nextPos = positionStack.back();
                    positionStack.pop_back();
                    break;
            }
        }
        return positions;
    }*/
}