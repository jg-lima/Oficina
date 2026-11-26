#include "oficina/veiculo.hpp"
#include <ostream>
#include <utility>

Veiculo::Veiculo(std::string placa) : placa_(std::move(placa)) {}

std::string Veiculo::ordemDeServico() const {
    return "Placa: " + placa_ +
           " | Tipo: " + tipo() +
           " | Servicos: " + servicos() +
           " | Custo: " + std::to_string(custoRevisao());
}

std::ostream& operator<<(std::ostream& os, const Veiculo& v) {
    return os << v.ordemDeServico();
}