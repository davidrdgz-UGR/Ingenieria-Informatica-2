# =============================== Makefile Practica ED 4 ===============================

CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Wall -Wextra

SRC = src
BUILD = build

OBJS = $(BUILD)/main.o \
       $(BUILD)/agendaEvento.o \
       $(BUILD)/Eventos.o

TARGET = practica4

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

# --- reglas individuales ---

$(BUILD)/main.o: $(SRC)/main.cpp include/AgendaEvento.h include/Eventos.h
	@if not exist $(BUILD) mkdir $(BUILD)
	$(CXX) $(CXXFLAGS) -c $(SRC)/main.cpp -o $(BUILD)/main.o

$(BUILD)/agendaEvento.o: $(SRC)/agendaEvento.cpp include/AgendaEvento.h include/Eventos.h
	@if not exist $(BUILD) mkdir $(BUILD)
	$(CXX) $(CXXFLAGS) -c $(SRC)/agendaEvento.cpp -o $(BUILD)/agendaEvento.o

$(BUILD)/Eventos.o: $(SRC)/Eventos.cpp include/Eventos.h
	@if not exist $(BUILD) mkdir $(BUILD)
	$(CXX) $(CXXFLAGS) -c $(SRC)/Eventos.cpp -o $(BUILD)/Eventos.o

clean:
	@if exist $(BUILD) rmdir /s /q $(BUILD)
	@if exist $(TARGET).exe del $(TARGET).exe
