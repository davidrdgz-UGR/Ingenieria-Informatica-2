# =============================== Makefile Practica ED 3 ===============================

CXX = g++
CXXFLAGS = -std=c++11 -Iinclude -Wall -Wextra

SRC = src
BUILD = build

OBJS = $(BUILD)/main.o \
       $(BUILD)/AgendaContactos.o \
       $(BUILD)/contactos.o

TARGET = agendaContactos

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

# --- reglas individuales ---

$(BUILD)/main.o: $(SRC)/main.cpp include/AgendaContactos.h include/contactos.h
	@if not exist $(BUILD) mkdir $(BUILD)
	$(CXX) $(CXXFLAGS) -c $(SRC)/main.cpp -o $(BUILD)/main.o

$(BUILD)/AgendaContactos.o: $(SRC)/AgendaContactos.cpp include/AgendaContactos.h include/contactos.h
	@if not exist $(BUILD) mkdir $(BUILD)
	$(CXX) $(CXXFLAGS) -c $(SRC)/AgendaContactos.cpp -o $(BUILD)/AgendaContactos.o

$(BUILD)/contactos.o: $(SRC)/contactos.cpp include/contactos.h
	@if not exist $(BUILD) mkdir $(BUILD)
	$(CXX) $(CXXFLAGS) -c $(SRC)/contactos.cpp -o $(BUILD)/contactos.o

clean:
	@if exist $(BUILD) rmdir /s /q $(BUILD)
	@if exist $(TARGET).exe del $(TARGET).exe
