#pragma once

#include "oficina/veiculo.hpp"
#include <string>

class Moto final : public Veiculo {
public:
    Moto(std::string placa, int cilindradas);
    ~Moto() override;

    std::string tipo() const override;
    std::string servicos() const override;
    int custoRevisao() const override;

    static int vivos()   { return vivos_; }
    static int criados() { return criados_; }

private:
    int cilindradas_;
    static inline int vivos_ = 0;
    static inline int criados_ = 0;
};
