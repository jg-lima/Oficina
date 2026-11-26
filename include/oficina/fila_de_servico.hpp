#pragma once
#include "oficina/veiculo.hpp"
#include <memory>
#include <utility>
#include <vector>

// A fila da oficina e FEITA DE um vector, mas nao E um vector:
// so se entra pelo fim (+=) e so se sai pela frente (atenderProximo).
class FilaDeServico : private std::vector<std::unique_ptr<Veiculo>> {
    using Base = std::vector<std::unique_ptr<Veiculo>>;

public:
    using Base::begin;
    using Base::end;
    using Base::size;
    using Base::empty;

    // entra no fim da fila; a fila passa a ser a dona do veiculo
    FilaDeServico& operator+=(std::unique_ptr<Veiculo> v) {
        push_back(std::move(v));
        return *this;
    }

    // tira o primeiro da fila para atendimento e entrega a posse a quem chamou;
    // com a fila vazia, devolve um ponteiro nulo
    std::unique_ptr<Veiculo> atenderProximo() {
        if (empty()) {
            return nullptr;
        }
        std::unique_ptr<Veiculo> proximo = std::move(front());
        erase(Base::begin());
        return proximo;
    }
};
