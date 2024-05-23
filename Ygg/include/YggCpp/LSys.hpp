#pragma once

namespace Ygg {
    struct LSysData {
        std::string axiom;
        std::vector<std::string> rules;
        int iterations;
    };

    class LSys {
    public:
        std::string generateExpression(LSysData props);
    };
}