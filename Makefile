# Nome do executável
EXEC = ordena

# Compilador e flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2

# Arquivos-fonte
SRC = main.cpp \
      metodo1.cpp \
      metodo2.cpp \
      metodo3.cpp \
      registro.cpp \
      arquivo.cpp \
      ordenacaoInterna.cpp \
      selecaoSubstituicao.cpp \
      quicksortExterno.cpp

# Arquivos objeto
OBJ = $(SRC:.cpp=.o)

# Regra padrão
all: $(EXEC)

# Linkagem final
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Limpa objetos e executável
clean:
	rm -f $(OBJ) $(EXEC)

# Limpa arquivos temporários gerados em tempo de execução
clean-temp:
	rm -f fita_in_*.txt fita_out_*.txt quicksort_temp.txt resultado.txt temp.txt

# Recompila tudo do zero
rebuild: clean all
