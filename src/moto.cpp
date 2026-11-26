#include "oficina/moto.hpp"

#include <utility>

Moto::Moto(std::string placa, int cilindradas)
    : Veiculo(std::move(placa)), cilindradas_(cilindradas) {
    ++vivos_;
    ++criados_;
}

Moto::~Moto() { --vivos_; }

std::string Moto::tipo() const {
    return "moto";
}

std::string Moto::servicos() const {
    return "corrente, pastilhas e oleo";
}

int Moto::custoRevisao() const {
    return 80 + cilindradas_ / 10;
}
