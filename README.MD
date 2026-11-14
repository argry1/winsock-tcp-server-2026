# Winsock TCP Server

Учебный TCP-сервер на C (Windows, Winsock).

## Что делает
- Создаёт TCP-сокет, привязывает к 0.0.0.0:8080
- Принимает одного клиента
- Читает данные, отвечает "Hello from server!"

## Сборка
    cl main.c ws2_32.lib              # MSVC
    gcc main.c -o server.exe -lws2_32 # MinGW

## Запуск
    server.exe

## Проверка
    telnet 127.0.0.1 8080
    (ввести текст, получить ответ)