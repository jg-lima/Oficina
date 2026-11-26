# Oficina — Trabalho prático da Unidade II

POO · UFPB · 2026.2 · Prof. Carlos Eduardo C. F. Batista · João Gabriel Lima de Lucena - 20250019797

## O tema

O projeto modela a oficina mecânica da Unidade I, agora vista pelos veículos que ela atende.
Todo veículo que entra na oficina tem placa e passa por uma revisão, mas o que se revisa e quanto
custa depende do tipo: um carro a combustão troca óleo, filtro e velas; uma moto revisa corrente
e pastilhas; um carro elétrico revisa a bateria. Por isso `Veiculo` é abstrata, e cada tipo
concreto responde à sua maneira. A ordem de serviço tem sempre o mesmo formato, montado pela
base com o conteúdo de cada derivada.

Alguns veículos, além de serem veículos, cumprem um contrato a mais: podem ser ligados no
carregador da oficina. Esse contrato é a interface `Recarregavel`, cumprida pelo carro elétrico.
Os veículos aguardam atendimento numa `FilaDeServico`, feita com um `std::vector`, mas que só
deixa entrar pelo fim (`+=`) e sair pela frente (`atenderProximo`) — ninguém fura a fila nem tira um carro do meio dela.

## Como compilar e rodar

Requer CMake 3.16+ e um compilador C++17.

```bash
make            # configura e compila (pasta build/)
make roda       # compila e executa a demonstração
make verifica   # portão: compila com -Werror, roda e confere que a última linha é vivos=0
make limpa      # apaga a pasta build/
```

## As classes

| Classe | Papel no domínio | Forma de herança |
|---|---|---|
| `Veiculo` | Base abstrata: placa, ordem de serviço (moldura não-virtual) e as puras `tipo`, `servicos`, `custoRevisao` | base abstrata, não copiável |
| `Recarregavel` | Contrato "pode ser ligado no carregador": `tempoRecargaMin`, `capacidadeKwh` | interface pura (sem dados) |
| `CarroCombustao` | Revisão com troca de óleo, filtro e velas | pública de `Veiculo`, `final` |
| `CarroEletrico` | Revisão da bateria; cumpre o contrato de recarga | pública de `Veiculo` **e** de `Recarregavel` (múltipla), `final` |
| `Moto` | Revisão de corrente, pastilhas e óleo | pública de `Veiculo`, `final` |
| `FilaDeServico` | Fila de atendimento: entra pelo fim com `+=`, sai pela frente com `atenderProximo` | **privada** de `std::vector<std::unique_ptr<Veiculo>>` |

O cabeçalho `include/oficina/contrato.hpp` prova essas formas com `static_assert`: se alguma
for quebrada, o projeto não compila.

## Saída de `make roda`

```
=== 1. o acervo polimorfico ===
  Placa: ABC1D23 | Tipo: carro a combustao | Servicos: troca de 4L de oleo, filtro e velas | Custo: 310
  Placa: ELE2E45 | Tipo: carro eletrico | Servicos: bateria de 60kWh, recarga em 163 min | Custo: 380
  Placa: MOT3O67 | Tipo: moto | Servicos: corrente, pastilhas e oleo | Custo: 110
=== 2. os operadores ===
  fila com 3 veiculos (entraram com +=)
  Placa: MOT9Z99 | Tipo: moto | Servicos: corrente, pastilhas e oleo | Custo: 95
  Placa: ELE8Y88 | Tipo: carro eletrico | Servicos: bateria de 40kWh, recarga em 109 min | Custo: 320
  Placa: CMB7X77 | Tipo: carro a combustao | Servicos: troca de 3L de oleo, filtro e velas | Custo: 270
  atendido: Placa: MOT9Z99 | Tipo: moto | Servicos: corrente, pastilhas e oleo | Custo: 95
  restam 2 veiculos na fila
=== 3. os contadores ===
  carregador: bateria de 50kWh, pronta em 136 min
  dentro do escopo: 3 veiculos na pilha vivos=3 criados=9
  depois do escopo: destrutores rodaram vivos=0
vivos=0
```
