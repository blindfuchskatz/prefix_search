#pragma once

#include "Logger.h"
#include "PrefixSearchAlgorithm.h"

#include <memory>
#include <vector>

class PrefixSearchRegistry
{
public:
    explicit PrefixSearchRegistry(size_t cores,
                                  std::unique_ptr<logger::Logger> logger);

    const std::vector<std::unique_ptr<algo::PrefixSearchAlgorithm>> &
    getAlgorithm() const;

private:
    std::vector<std::unique_ptr<algo::PrefixSearchAlgorithm>> _algoList;
};