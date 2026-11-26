#include "oficina/contrato.hpp"  // R14: se uma afirmacao falhar, nao compila

#include <iostream>
#include <memory>
#include <vector>

namespace {

int somaVivos() {
    return CarroCombustao::vivos() + CarroEletrico::vivos() + Moto::vivos();
}

int somaCriados() {
    return CarroCombustao::criados() + CarroEletrico::criados() + Moto::criados();
}

// O carregador da oficina so aceita quem cumpre o contrato Recarregavel:
// nao sabe (nem precisa saber) que tipo de veiculo esta ligado nele.
void ligarNoCarregador(const Recarregavel& r) {
    std::cout << "  carregador: bateria de " << r.capacidadeKwh() << "kWh, pronta em "
              << r.tempoRecargaMin() << " min\n";
}

}  // namespace

int main() {
    // ---------- 1. o acervo polimorfico (R10, R11) ----------
    {
        std::cout << "=== 1. o acervo polimorfico ===\n";
        std::vector<std::unique_ptr<Veiculo>> acervo;
        acervo.push_back(std::make_unique<CarroCombustao>("ABC1D23", 4));
        acervo.push_back(std::make_unique<CarroEletrico>("ELE2E45", 60));
        acervo.push_back(std::make_unique<Moto>("MOT3O67", 300));

        // percorrido por ponteiro base: cada veiculo responde pela sua virtual
        for (const auto& v : acervo) {
            std::cout << "  " << v->ordemDeServico() << '\n';
        }
    }  // o vector destroi os unique_ptr, que destroem os veiculos

    // ---------- 2. os operadores (R12) ----------
    {
        std::cout << "=== 2. os operadores ===\n";
        FilaDeServico fila;
        fila += std::make_unique<Moto>("MOT9Z99", 150);
        (fila += std::make_unique<CarroEletrico>("ELE8Y88", 40))
            += std::make_unique<CarroCombustao>("CMB7X77", 3);  // += devolve a propria fila

        std::cout << "  fila com " << fila.size() << " veiculos (entraram com +=)\n";
        for (const auto& v : fila) {
            std::cout << "  " << *v << '\n';  // operator<< livre
        }

        // o primeiro da fila sai para atendimento: a posse passa da fila para 'atendido'
        std::unique_ptr<Veiculo> atendido = fila.atenderProximo();
        std::cout << "  atendido: " << *atendido << '\n';
        std::cout << "  restam " << fila.size() << " veiculos na fila\n";
    }  // 'atendido' e a fila destroem os veiculos que ainda tem

    // ---------- 3. os contadores (R13) ----------
    std::cout << "=== 3. os contadores ===\n";
    {
        CarroCombustao carro("TST1A11", 4);
        CarroEletrico eletrico("TST2B22", 50);
        Moto moto("TST3C33", 125);
        ligarNoCarregador(eletrico);  // o eletrico usado pelo contrato, sem cast
        std::cout << "  dentro do escopo: 3 veiculos na pilha vivos=" << somaVivos()
                  << " criados=" << somaCriados() << '\n';
    }
    std::cout << "  depois do escopo: destrutores rodaram vivos=" << somaVivos() << '\n';
    std::cout << "vivos=" << somaVivos() << '\n';
}
