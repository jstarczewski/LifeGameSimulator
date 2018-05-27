

#include <stdio.h>
#include <time.h>
#include "log.h"

char *messages[] = {
        "Program zakończył pracę bez utworzenia generacji.",
        "Nieodpowiednia ilość argumentów.",
        "Błędny argument: liczba generacji.",
        "Błędny argument: rodzaj sąsiedztwa.",
        "Generacja o podanej nazwie już istnieje.",
        "Błędna zawartość pliku z pierwszą generacją.",
        "Błąd przy zapisie pliku PNG.",
        "Nie udało się zaalokować pamięci dla niezbędnych struktur.",
        "Nie udało sie utworzyć pliku zawierającego pierwszą bądź ostatnią generację",
        "Uruchomienie programu",
        "Wczytywanie pliku z pierwszą generacją",
        "Tworzenie niezbędnych podfolderów",
        "Rozpoczęcie generacji",
        "Generacja zakończona sukcesem",

};

FILE *log_file;
int msg_counter = 1;

int open_log() {
    log_file = fopen("log.txt", "w");
    if (log_file == NULL) {
        printf("Nie udało sie utworzyć pliku log.txt\n");
        return 0;
    }

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char time_string[64];
    strftime(time_string, sizeof(time_string), "%c", tm);
    fprintf(log_file, "Log z dnia %s\n", time_string);
    return 1;

}

void write_message(int msg_index) {
    fprintf(log_file, "%d: %s\n", msg_counter++, messages[msg_index]);
}

void close_log() {
    fclose(log_file);
}

