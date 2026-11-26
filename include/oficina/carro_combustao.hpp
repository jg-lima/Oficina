#pragma once
#include "oficina/veiculo.hpp"
#include <string>

class CarroCombustao final : public Veiculo {
public:
    CarroCombustao(std::string placa, int litrosOleo);
    ~CarroCombustao() override;

    std::string tipo() const override;
    std::string servicos() const override;
    int custoRevisao() const override;

    static int vivos()   { return vivos_; }
    static int criados() { return criados_; }

private:
    int litrosOleo_;
    static inline int vivos_ = 0;
    static inline int criados_ = 0;
};
