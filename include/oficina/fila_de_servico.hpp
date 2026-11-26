#pragma once
#include "oficina/veiculo.hpp"
#include <memory>
#include <utility>
#include <vector>

// A fila da oficina e FEITA DE um vector, mas nao E um vector:
// so se entra pelo fim (+=) e so se consulta ou percorre.
class FilaDeServico : private std::vector<std::unique_ptr<Veiculo>> {
    using Base = std::vector<std::unique_ptr<Veiculo>>;

public:
    using Base::begin;
    using Base::end;
    using Base::size;
    using Base::empty;

    FilaDeServico& operator+=(std::unique_ptr<Veiculo> v) {
        push_back(std::move(v));
        return *this;
    }
};
