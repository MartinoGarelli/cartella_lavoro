#include <algorithm>
#include <cmath>
#include <vector>

struct PPState  // struct dei punti
{
  double m{};  // massa
  double x{};  // posizione
  double v{};  // velocità
};

class Hooke {
  double m_k{};  // costante elastica
  double m_l{};  // lunghezza riposo
 public:
  Hooke(double k, double l) : m_k{k}, m_l{l} {};  // costruttore

  double operator()(PPState const& p1, PPState const& p2) const {
    double force{};
    double dl{};
    if (abs(p1.x - p2.x) > m_l)  // molla allungata
    {
      dl = abs(p1.x - p2.x) - m_l;
      force = dl * m_k;  // forza attrattiva positiva
    } else {
      dl = m_l - abs(p1.x - p2.x);  // molla contratta
      force = -dl * m_k;
    }  // forza repulsiva negativa
    return force;
  }
};

class Chain {
  Hooke m_inter;
  std::vector<PPState> m_ppses;

 private:
  // a(t) = ΣF(t)
  // v(t + Δt) = v(t) + a(t) ⋅ Δt
  // x(t + Δt) = x(t) + v(t) ⋅ Δt + 0.5 ⋅ a(t) Δt2
  // ΣF sommatoria su un punto

  PPState solve(PPState const& pps, double f, double delta_t) const {
    // if (delta_t < 0.001) {
    //   double acc = f / delta_t;
    //   double vel = pps.v * delta_t;
    //   double x_final = pps.x + vel * delta_t + 0.5 * acc * delta_t * delta_t;
    //   return {pps.m, x_final, vel};
    // } 
    // else {
    //   throw std::runtime_error("intervallo troppo largo");
    // }

  double acc = f / delta_t;
      double vel = pps.v * delta_t;
      double x_final = pps.x + (vel * delta_t) + (0.5 * acc * delta_t * delta_t);
      return {pps.m, x_final, vel};
    
  };

 public:
  Chain(Hooke const& inter) : m_inter{inter} {};  // costruttore
  void push_back(PPState const& pps) {
    m_ppses.push_back(pps);
  };  // pps nome del punto da prendere

  int size() const { return m_ppses.size(); };

  void evolve(double delta_t) {
    for (unsigned long int i = 0; i < m_ppses.size(); i++) {
      // if (delta_t > 0.001) {
      //   int inter = 1;
      //   while (delta_t / inter > 0.0001) {
      //     ++inter;
      //   };
      //   delta_t = {delta_t / inter};
      // }
      solve(m_ppses[i], f.Hooke(PPState i, PPState i), delta_t);
    }
  }
    std::vector<PPState> const& state() const { return m_ppses; }
  
  };