#pragma once
#include <iosfwd>
#include <string>

class Veiculo {
public:
    virtual ~Veiculo() = default;                       // R5: destrutor virtual
    Veiculo(const Veiculo&) = delete;                   // R5: não copia
    Veiculo& operator=(const Veiculo&) = delete;

    std::string ordemDeServico() const;                 // R11: NÃO virtual, é a moldura

    virtual std::string tipo() const = 0;               // R5: puras
    virtual std::string servicos() const = 0;
    virtual int custoRevisao() const = 0;

    const std::string& placa() const { return placa_; }
protected:
    explicit Veiculo(std::string placa);
private:
    std::string placa_;
};

std::ostream& operator<<(std::ostream& os, const Veiculo& v);   // R12: livre
