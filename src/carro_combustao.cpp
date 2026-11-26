#include "oficina/carro_combustao.hpp"
#include <utility>

CarroCombustao::CarroCombustao(std::string placa, int litrosOleo)
    : Veiculo(std::move(placa)), litrosOleo_(litrosOleo) {
    ++vivos_;
    ++criados_;
}

CarroCombustao::~CarroCombustao() { --vivos_; }

std::string CarroCombustao::tipo() const { return "carro a combustao"; }

std::string CarroCombustao::servicos() const {
    return "troca de " + std::to_string(litrosOleo_) + "L de oleo, filtro e velas";
}

int CarroCombustao::custoRevisao() const { return 150 + 40 * litrosOleo_; }
