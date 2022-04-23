

#include "Mchain.hpp"

// Esegue la simulazione della catena, suddividendo "duration" in "steps"
// e registrando lo stato ogni volta che si compie un numero di step pari
// a "prescale"
auto simulazione(Chain &chain, double duration, int steps, int prescale) {
  std::vector<std::vector<punti>> stati_stamp;

  double delta_t{duration / steps};
  if (delta_t > 0.001)
  {
    steps++;
    delta_t = duration /steps;
  }
  
  for (int step = 0; step != steps; ++step) {
    if (step % prescale == 0) {
      stati_stamp.push_back(chain.stato());
    }
    chain.evoluzione(delta_t);
  }
  return stati_stamp;
}

int main() {
  // Molla con:
  // k = 10 N/m
  // l = 1 m
  Hooke hooke{20.0, 1.};

  // Catena con 10 punti materiali:
  // m: 100 g per ogni punto
  // x: un punto ogni 0.5 m (partendo da 0.0)
  // v: tutti i punti hanno v = 0 m/s
  Chain chain(hooke);

  double const p_m{100};
  double p_x{0.0};
  double delta_x{0.5};
  // double p_v{};

  // for (int i = 0; i < chain.size(); i++) {
  //   chain.buttadentro({p_x, p_m, p_v});
  //   p_x += delta_x;
  // }

  for (auto const p_v : {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}) {
    chain.buttadentro({p_m, p_x, p_v});
    p_x += delta_x;
  };

  // Esegue una simulazione:
  // - per una durata di 5 s
  // - suddividendola in 20000 steps
  // - registrando lo stato della catena ogni 100 steps

  double const duration{20.0};
  int const steps{20000};
  int const prescale{100};  // prescale ti da ogni quanti steps darti il risultato

  const auto stati_stamp = simulazione(chain, duration, steps, prescale);

  // Analisi:
  // sulla base degli stati registrati vengono calcolati:
  // - la lunghezza totale della molla ad ogni stato
  // - posizione e velocità del centro di masse della molla ad ogni stato
  // - la media della lunghezza della molla in tutti gli stati campionati

  double sum_length{0.0};

  std::cout << "Report for each of the stored states:\n";
  std::cout << "  length  : center of mass x : center of mass v\n";

  for (const auto &state : stati_stamp) {
    auto length = state.back().posizione - state.front().posizione;
    sum_length += length;   //serve per la media

    double sum_m{0.0};
    double sum_mx{0.0};
    double sum_mv{0.0};

    for (const auto &pps : state) {
      sum_m += pps.massa;
      sum_mx += pps.massa * pps.posizione;
      sum_mv += pps.massa * pps.velocita;
    }

    std::cout << std::setprecision(4) << std::fixed << std::setw(8) << length
              << "  : " << std::setw(14) << (sum_mx / sum_m) << "   : "
              << std::setw(14) << (sum_mv / sum_m) << '\n';
  };

  std::cout << "\nSummary:\n";
  std::cout << "Average length: " << (sum_length / stati_stamp.size()) << '\n';
}
