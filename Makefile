# Compilador e flags de compilação
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Iinclude

# Diretórios do projeto
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

# Nome do executável exigido pela especificação
TARGET = $(BIN_DIR)/tp1.out

# Busca automática por todos os arquivos .cpp na pasta src/
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

# Regra principal
all: $(TARGET)

# Linkagem do executável final
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Compilação dos arquivos fonte (.cpp) em código objeto (.o)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Executa o programa compilado diretamente
run: $(TARGET)
	./$(TARGET)

# Regra para execução com Valgrind
valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 ./$(TARGET)

# Criação dos diretórios caso não existam
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Limpeza dos arquivos compilados
clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/*

.PHONY: all clean run valgrind