#pragma once
#include <string>
#include <ctime>

// clock è più accurato di time in questo caso
// time va bene per calcolare una durata in secondi

// la durata misurata varia tuttavia a seconda del carico della cpu
// non c'è garanzia che due chiamate uguali successive diano valori strettamente monotoni crescenti
// la funzione clock() calcola i colpi di clock ma questi possono variare a seconda del carico della cpu
// clock() è definita per dirti quanto tempo di cpu è usato
// usare più thread e più processi su un single core fa crescere il tempo di cpu
// thred addormentati e thread su più core usano meno tempo di cpu

class DurationLogger {
private:
    std::string name;
    std::clock_t c_start;
    std::clock_t c_end;
    double c_duration;
public:
    DurationLogger(const std::string& name);
    ~DurationLogger();
};
