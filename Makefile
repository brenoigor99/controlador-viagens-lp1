CXX = g++
CXXFLAGS = -Wall -std=c++17

SRC = src/main.cpp \
      src/modelos/Cidade/Cidade.cpp \
      src/modelos/Trajeto/Trajeto.cpp \
      src/modelos/Transporte/Transporte.cpp \
      src/modelos/Passageiro/Passageiro.cpp \
      src/modelos/Viagem/Viagem.cpp \
      src/modelos/ControladorDeTransito/ControladorDeTransito.cpp \
      src/repositories/Repositorio.cpp \
      src/usecases/MenuPrincipal.cpp

TARGET = bin/ControladorViagens

all: $(TARGET)

$(TARGET): $(SRC)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run:
	@./$(TARGET)

clean:
	rm -f $(TARGET)