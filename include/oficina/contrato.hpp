#pragma once
// Contrato do projeto: so static_assert. Se alguma afirmacao falhar,
// o projeto nao compila.

#include "oficina/carro_combustao.hpp"
#include "oficina/carro_eletrico.hpp"
#include "oficina/fila_de_servico.hpp"
#include "oficina/moto.hpp"
#include "oficina/recarregavel.hpp"
#include "oficina/veiculo.hpp"

#include <memory>
#include <type_traits>
#include <vector>

// ---- R5: a base abstrata ----
static_assert(std::is_abstract_v<Veiculo>,
              "(a) Veiculo deve ser abstrata: nao existe revisao de um veiculo generico");
static_assert(std::has_virtual_destructor_v<Veiculo>,
              "(b) Veiculo deve ter destrutor virtual: os veiculos sao destruidos por ponteiro da base");
static_assert(!std::is_copy_constructible_v<Veiculo>,
              "(c) Veiculo nao pode ser construido por copia: base polimorfica nao se copia por valor");
static_assert(!std::is_copy_assignable_v<Veiculo>,
              "(c) Veiculo nao pode ser atribuido por copia: base polimorfica nao se copia por valor");
// Em classe abstrata, is_copy_constructible_v e falso de qualquer jeito (nao se
// constroi objeto dela). A prova real de que a copia foi apagada na base e que
// nenhuma concreta herda um construtor de copia.
static_assert(!std::is_copy_constructible_v<CarroCombustao> &&
                  !std::is_copy_constructible_v<CarroEletrico> &&
                  !std::is_copy_constructible_v<Moto>,
              "(c) nenhum veiculo concreto pode ser copiado: a copia e apagada em Veiculo");

// ---- R6: a interface pura ----
static_assert(sizeof(Recarregavel) == sizeof(void*),
              "(d) Recarregavel nao pode ter dado algum: so o ponteiro da tabela virtual");
static_assert(std::is_abstract_v<Recarregavel>,
              "(d) Recarregavel deve ser abstrata: e um contrato, nao um objeto");

// ---- R7: as concretas nao sao abstratas e sao final ----
static_assert(!std::is_abstract_v<CarroCombustao> && std::is_final_v<CarroCombustao>,
              "(e) CarroCombustao deve ser concreta e final");
static_assert(!std::is_abstract_v<CarroEletrico> && std::is_final_v<CarroEletrico>,
              "(e) CarroEletrico deve ser concreta e final");
static_assert(!std::is_abstract_v<Moto> && std::is_final_v<Moto>,
              "(e) Moto deve ser concreta e final");

// ---- R7: as concretas convertem para a base (heranca publica) ----
static_assert(std::is_convertible_v<CarroCombustao*, Veiculo*>,
              "(f) CarroCombustao deve converter para Veiculo: a heranca tem de ser publica");
static_assert(std::is_convertible_v<CarroEletrico*, Veiculo*>,
              "(f) CarroEletrico deve converter para Veiculo: a heranca tem de ser publica");
static_assert(std::is_convertible_v<Moto*, Veiculo*>,
              "(f) Moto deve converter para Veiculo: a heranca tem de ser publica");

// ---- R8: heranca multipla, uma afirmacao por base ----
static_assert(std::is_base_of_v<Veiculo, CarroEletrico>,
              "(g) CarroEletrico deve derivar de Veiculo");
static_assert(std::is_base_of_v<Recarregavel, CarroEletrico>,
              "(g) CarroEletrico deve derivar de Recarregavel");
static_assert(std::is_convertible_v<CarroEletrico*, Recarregavel*>,
              "(g) CarroEletrico deve converter para Recarregavel: a heranca tem de ser publica");

// ---- R9: heranca privada, o par de sinais opostos ----
static_assert(std::is_base_of_v<std::vector<std::unique_ptr<Veiculo>>, FilaDeServico>,
              "(h) FilaDeServico deve derivar do vector: e feita com ele");
static_assert(!std::is_convertible_v<FilaDeServico*, std::vector<std::unique_ptr<Veiculo>>*>,
              "(h) FilaDeServico nao pode converter para o vector: nao e um vector, a heranca e privada");
