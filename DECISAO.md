# Decisões de projeto

## 1. Por que a base é abstrata?
Na oficina não faz  sentido revisar um veículo sem especificar o tipo de veiculo que será revisado, porque o que vai ser mexido e quanto vai custar só dá pra saber quando o veículo chega e você vê o que ele é, por exemplo: carro a combustão (óleo, filtro, velas), moto (corrente, pastilhas) ou carro elétrico (bateria). Por isso tipo(), servicos() e custoRevisao() ficam como virtuais puros em Veiculo. Se custoRevisao() tivesse uma implementação padrão tipo return 0;, alguém poderia criar um veículo novo, esquecer de implementar o método, o código compilaria de boa e a oficina soltaria ordem de serviço de graça sem ninguém notar. Deixando puro, se faltar implementação o compilador já barra na hora. O que Veiculo já deixa pronto é a moldura: ordemDeServico() não é virtual e mantém sempre o mesmo padrão visual e estrutural, puxando o conteúdo específico de cada tipo.

## 2. Por que cada herança é da forma que é?

Cada tipo de herança foi escolhido conforme o papel da classe no sistema. A herança pública em CarroCombustao, CarroEletrico e Moto a partir de Veiculo existe porque cada um deles é de fato um veículo da oficina, então precisa poder entrar em qualquer lugar que espere um Veiculo, seja no acervo, na fila ou na ordem de serviço. Já em CarroEletrico, a herança múltipla de Veiculo e Recarregavel faz sentido porque ele é um veículo e, além disso, cumpre o contrato de poder ir pra tomada ou ir pro carregador; ser recarregável não é a identidade base dele, mas uma capacidade que ele atende, e como recarregavel não guarda estado nem dados, não gera conflito ou duplicação de atributos. Por fim, a herança privada de FilaDeServico a partir do vetor veiculo acontece porque a fila apenas usa um vetor por baixo dos panos, mas não é um vector. Se alguém pudesse tratar a fila como um vector comum, conseguiria inserir itens no meio e bagunçar a ordem. Por isso só reexponho o que faz sentido pra fila, que são begin, end, size e empty pra percorrer e ver quantos estão esperando, deixando de fora insert e emplace pra ninguém furar fila, erase e pop_back pra ninguém sair sem ser atendido, operator[] e at pra não mexer em item por índice solto e clear pra não limpar tudo de uma vez, restando apenas o += como entrada no final.

## 3. Quem é dono de quê?

Cada veículo criado com make_unique tem um único dono por vez, e isso está escrito no tipo do ponteiro que guarda o veículo, o ponteiro único unique_ptr: ele não pode ser copiado, só transferido de um dono para outro. No acervo da seção 1, quem manda no tempo de vida dos veículos é o vetor. Na seção 2, a responsabilidade passa para a FilaDeServico: o += recebe o ponteiro por valor, então quem coloca um veículo na fila entrega a posse para ela. Quando um veículo é atendido, o atenderProximo() devolve o ponteiro, e a posse sai da fila e passa para quem chamou. Quando o vetor ou a fila saem de escopo, os unique_ptr são destruídos e acionam o destrutor virtual de Veiculo, limpando as classes derivadas corretamente. Na seção 3, os objetos ficam na pilha e o próprio escopo do bloco cuida de destruir tudo quando fecha. Com isso, não existe nenhum delete solto no código e o vivos=0 no final confirma que todos os destrutores rodaram como esperado.

## 4. Por que cada operador é membro ou livre?

A escolha entre operador livre ou membro depende diretamente de quem está à esquerda da operação. O operator<< precisa ser livre porque o operando da esquerda é a classe ostream, que não é uma classe minha, então não tenho como sair adicionando métodos dentro dela; ele apenas pega ordemDeServico(), envia para o stream e devolve o próprio ostream para permitir encadeamento. Já o operator+= é membro de FilaDeServico porque o alvo à esquerda é a própria fila, que tem seu estado alterado ao receber um veículo no final, e seguindo o padrão dos operadores de atribuição composta ele retorna FilaDeServico&, uma referência para a própria fila —, o que permite encadear (fila += a) += b da mesma forma que o += nativo da linguagem.

## Uso de assistentes de IA

Usei duas inteligencias artificiais:

Claude (Anthropic): montou o roteiro do trabalho a partir do enunciado, revisou cada arquivo que eu escrevi compilando sob o portão de avisos e explicou os erros do compilador. Também escreveu partes do código e o README.

Gemini (Google): usei para revisar alguns arquivos e tirar dúvidas quando o limite de uso do Claude acabou.

Erros:

Gemini: sugeriu colocar override em ordemDeServico(). Isso está errado, porque essa função é a moldura do R11: ela não é virtual de propósito e nenhuma derivada deve reescrevê-la. Com override, o código nem compilaria, já que não existe função virtual para sobrescrever.

Claude: sugeriu provar que a base não é copiável com !std::is_copy_constructible_v<Veiculo>. Essa afirmação passa sempre, porque uma classe abstrata nunca pode ser construída, com ou sem = delete. Descobri sso apagando o construtor e vi que a afirmação continuava passando. A correção foi afirmar também que nenhuma das classes concretas é copiável, se a base deixasse copiar elas herdariam a cópia.


Claude: na revisão ele apontou que a interface Recarregavel nunca era usada como contrato e que a fila não tinha como atender ninguém, o que contradizia a minha resposta 2.