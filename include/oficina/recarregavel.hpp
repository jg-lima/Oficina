#pragma once

class Recarregavel {
public:
    virtual ~Recarregavel() = default;
    virtual int tempoRecargaMin() const = 0;
    virtual int capacidadeKwh() const = 0;
};
