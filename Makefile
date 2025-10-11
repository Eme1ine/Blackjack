# Nom de l'exécutable
TARGET = build/main.exe

# Chemins
SRCDIR = src
INCDIR = include
CONTROLLERDIR = src/Controller
MODELDIR = src/Model
PERSONDIR = src/Model/Person

# Tous les fichiers .cpp
SOURCES := \
  $(wildcard $(SRCDIR)/*.cpp) \
  $(wildcard $(MODELDIR)/*.cpp) \
  $(wildcard $(PERSONDIR)/*.cpp) \
  $(wildcard $(CONTROLLERDIR)/*.cpp)

# Options du compilateur
CXX = g++
CXXFLAGS = -std=c++17 -g -I$(INCDIR) -fdiagnostics-color=always

all: $(TARGET)

$(TARGET): $(SOURCES)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	@echo "Cleaning..."
	@rm -f $(TARGET)
