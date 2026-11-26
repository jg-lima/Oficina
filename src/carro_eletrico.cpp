#include "oficina/carro_eletrico.hpp"
#include <utility>

CarroEletrico::CarroEletrico(std::string placa, int kwh)
    : Veiculo(std::move(placa)), kwh_(kwh) {
    ++vivos_;
    ++criados_;
}

CarroEletrico::~CarroEletrico() { --vivos_; }

std::string CarroEletrico::tipo() const { return "carro eletrico"; }

std::string CarroEletrico::servicos() const {
    return "bateria de " + std::to_string(kwh_) + "kWh, recarga em " +
           std::to_string(tempoRecargaMin()) + " min";
}

int CarroEletrico::custoRevisao() const { return 200 + 3 * kwh_; }

int CarroEletrico::tempoRecargaMin() const { return kwh_ * 60 / 22; }  // carregador de 22 kW

int CarroEletrico::capacidadeKwh() const { return kwh_; }
