BUILD := build
.PHONY: all roda verifica limpa

all:
	cmake -S . -B $(BUILD)
	cmake --build $(BUILD)

roda: all
	./$(BUILD)/oficina

verifica: all
	@ultima=$$(./$(BUILD)/oficina | tail -n 1); \
	if [ "$$ultima" = "vivos=0" ]; then echo "verifica: OK"; \
	else echo "verifica: FALHOU (ultima linha: '$$ultima')"; exit 1; fi

limpa:
	rm -rf $(BUILD)
