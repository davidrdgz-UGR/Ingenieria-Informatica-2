# ===============================    Makefile Practica ED 2 ===============================
CXX = g++
CXXFLAGS = -std=c++11 -Iinclude -Wall -Wextra

SRC = src
BUILD = build

OBJS = $(BUILD)/main.o \
       $(BUILD)/agendaEventos.o \
       $(BUILD)/evento.o

TARGET = agenda

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

# --- reglas individuales ---

$(BUILD)/main.o: $(SRC)/main.cpp include/agendaEventos.h include/Evento.h
	@if not exist $(BUILD) mkdir $(BUILD)
	$(CXX) $(CXXFLAGS) -c $(SRC)/main.cpp -o $(BUILD)/main.o

$(BUILD)/agendaEventos.o: $(SRC)/agendaEventos.cpp include/agendaEventos.h include/Evento.h
	@if not exist $(BUILD) mkdir $(BUILD)
	$(CXX) $(CXXFLAGS) -c $(SRC)/agendaEventos.cpp -o $(BUILD)/agendaEventos.o

$(BUILD)/evento.o: $(SRC)/evento.cpp include/Evento.h
	@if not exist $(BUILD) mkdir $(BUILD)
	$(CXX) $(CXXFLAGS) -c $(SRC)/evento.cpp -o $(BUILD)/evento.o
