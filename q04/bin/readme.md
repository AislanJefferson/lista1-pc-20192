
(dev) Considere um programa em java que usa um banco de dados chave-valor que implementa a interface Map (https://docs.oracle.com/javase/8/docs/api/java/util/Map.html). Operações que alteram o estado desse banco (p.ex put e remove) são bastante lentas; uma vez que os dados modificações precisam ser enviados para o disco de maneira síncrona. Operações de leitura são mais rápidas (entretanto, mais lentas que em uma implementação de Map, digamos HashMap, que mantém os dados em memória). Você deve implementar um cache como um Decorator --- em resumo, uma nova implementação de Map que repassa algumas chamadas para o banco de dados Map) ---- para acelerar o desempenho. Essa sua implementação precisa ser thread-safe e não relaxar a consistência da estrutura de dados. Múltiplas threads podem acessar o eu CacheMap. O construtor do seu Map deve receber três parâmetros: 1) uma referência para banco de dados Map, 2) um número inteiro que indica a quantidade máxima de pares chave-valor que podem ser mantidos em memória por sua implementação; e 3) um inteiro que indica o tempo máximo, em segundos, que o banco pode ficar sem ser atualizado. Da interface de Map, implemente os seguintes métodos:
clear
containsKey
get
isEmpty
put
remove(key, object)
size

//dbMap é uma referência para um Map em disco. assuma que //qualquer operação sobre o map pode ser muito lenta. A razão de //existir de CacheMap é evitar ao máximo operações sobre dbMap. O //objeto apontado por dbMap é usado somente por uma instância de //CacheMap

public class CacheMap(int cacheSize, int timeoutSecs, Map dbMap)


