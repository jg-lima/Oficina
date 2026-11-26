#pragma once

#include "oficina/recarregavel.hpp"
#include "oficina/veiculo.hpp"
#include <string>

class CarroEletrico final : public Veiculo, public Recarregavel {
public:
    CarroEletrico(std::string placa, int kwh);
    ~CarroEletrico() override;

    std::string tipo() const override;
    std::string servicos() const override;
    int custoRevisao() const override;

    int tempoRecargaMin() const override;
    int capacidadeKwh() const override;

    static int vivos()   { return vivos_; }
    static int criados() { return criados_; }

private:
    int kwh_;
    static inline int vivos_ = 0;
    static inline int criados_ = 0;
};
