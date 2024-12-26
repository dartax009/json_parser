PM_NAME = test
MAIN_NAME = test

#Флаги компиляции
CFLAGS = -Wall -std=gnu11 -O0

#Указание пути расположения внешней библиотеки
L_DIR +=

#Исполняеммый файл внешней библиотеки
CFILES += ../json_parser/json_form_check.c
CFILES += ../json_parser/jsmn/jsmn.c
CFILES += src/handler_field.c

#Передача компилятору пути до внешней библиотеки
INCLUDE_IDE +=

#Подключение стандартных библиотек
LIB += -lpthread

PROJECT_MAIN = src/$(MAIN_NAME).c

#Пути создания исполняемых файлов
B_PROJECT_BUILD = obj/$(PM_NAME)
D_PROJECT_BUILD = debug/$(PM_NAME)

all: clean test debug

.PHONY: test

test: clean_b
	mkdir -p obj
	gcc $(PROJECT_MAIN) $(INCLUDE_IDE) $(CFILES) -DPRINT_ERROR_INFO $(L_DIR) $(LIB) -o $(B_PROJECT_BUILD) $(CFLAGS)

clean_b:
	rm -Rf obj/

clean_d:
	rm -Rf debug/

clean: clean_b clean_d

.PHONY: debug

debug: clean_d
	mkdir -p debug
	gcc -ggdb $(PROJECT_MAIN) $(INCLUDE_IDE) $(CFILES) -DDEBUG_BUILD -DPRINT_ERROR_INFO $(L_DIR) $(LIB) -o $(D_PROJECT_BUILD) $(CFLAGS)

.PHONY: start

start:
	obj/$(PM_NAME)