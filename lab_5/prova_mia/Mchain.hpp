#include <algorithm>
#include <cmath>
#include <vector>
#include <iomanip>
#include <iostream>

struct punti {
  double massa{};
  double posizione{};
  double velocita{};
};

class Hooke {
 private:
  double costante{};
  double lung_riposo{};

 public:
  Hooke(double k, double l) : costante{k}, lung_riposo{l} {};
  //Hooke(double costante, double lung_riposo) : costante{costante} , lung_riposo{lung_riposo} {};
  //altro costruttore

  double operator()(punti const& p1, punti const& p2) const {
    double forza{};
    double all{};
    double dist{};
    dist = abs(p1.posizione - p2.posizione);
    all = abs(dist - lung_riposo);
    //std::cout <<dist << "  " <<lung_riposo <<std::endl ;  //prova 
    forza = all * costante;
    if (abs(p1.posizione - p2.posizione) > lung_riposo)  // molla allungata
    {
      forza = -abs(forza);
    }  // forza attrattiva negativa
    else {
      forza = abs(forza);
    }              // molla contratta
    return forza;  // forza repulsiva positiva
  }
};

class Chain {
  Hooke molla;
  std::vector<punti> situa_punti;

  //  punti solve(punti const& punto, double forza, double delta_t)
  //  const {/*...*/}

 public:
  Chain(Hooke const& molla) : molla{molla} {};
  void buttadentro(punti const& punto) { situa_punti.push_back(punto); }

  int size() const { return situa_punti.size(); };

  std::vector<punti> const& stato() const { return situa_punti; }

  void evoluzione(double delta_t) { 
    std::vector<punti> situa_punti_f; //creo un altro vettore per salvare lo stato dopo delta_t
     double pos_f{}, vel_f{}, acc{};
    for (int i = 0; i < size(); i++)  // for loop per ogni massa
    {
     
  //da spostare
      // massa, velocità, posizone li prendo dal vettore
      punti p1, p2, p3;

    if (i == 0)
    {
    p1 = situa_punti[i];
    p2 = situa_punti[i +1];
    acc = - molla(p1, p2)/p1.massa;
    } else if (i == size())
    {
    p1 = situa_punti[i-1];
    p2 = situa_punti[i];
    acc = molla(p2, p1)/p2.massa;
    } else {
      p1 = situa_punti[i-1];
      p2 = situa_punti[i];
      p3 = situa_punti[i+1];
     //std::cout <<p1.posizione-p2.posizione <<" " <<molla(p1, p2) <<std::endl;
      double acc_sx = molla(p1, p2)/p2.massa;
      double acc_dx = molla(p2, p3)/p2.massa;
      acc = acc_sx + acc_dx;
    }
    vel_f = situa_punti[i].velocita + acc*delta_t;
    pos_f = situa_punti[i].posizione + (situa_punti[i].velocita * delta_t) + (0.5*acc* pow(delta_t, 2));
    punti punto_f {situa_punti[i].massa, pos_f, vel_f};
    situa_punti_f.push_back(punto_f);

    //prova
    //std::cout <<punto_f.massa <<" " <<punto_f.posizione <<" " <<punto_f.velocita << " " <<acc <<std::endl;

  };
    situa_punti = situa_punti_f;
};
};

/*
if (i == 0) {       //in questo caso calcolo su p1 e il punto dopo è p2
        p1 = situa_punti[i];
        p2 = situa_punti[i + 1];
        acc_dx = -molla(p1, p2) / p1.massa;
        acc = acc_dx;
        vel_f = p1.velocita + (acc * delta_t);
        pos_f = p1.posizione + (p1.velocita * delta_t) +
                (0.5 * acc * delta_t * delta_t);
      } else if (i == size() - 1) {   //in questo caso calcolo su p1 e il punto prima è p2
        p1 = situa_punti[i];
        p2 = situa_punti[i - 1];
        acc_sx = molla(p1, p2) / p1.massa;
        acc = acc_sx;
        vel_f = p1.velocita + (acc * delta_t);
        pos_f = p1.posizione + (p1.velocita * delta_t) +
                (0.5 * acc * delta_t * delta_t);
      } else {
        p1 = situa_punti[i - 1];
        p2 = situa_punti[i];
        p3 = situa_punti[i + 1];
        acc_sx = molla(p1, p2) / p2.massa;
        acc_dx = molla(p2, p3) / p2.massa;
        acc = acc_sx - acc_dx;
        vel_f = p2.velocita + (acc * delta_t);
        pos_f = p2.posizione + (p2.velocita * delta_t) +
                (0.5 * acc * delta_t * delta_t);
      }
      p1 = situa_punti[i];
      punti punto_finale{ p1.massa, pos_f, vel_f};
      situa_punti_f.push_back(punto_finale);
    //std::cout <<pos_f <<" " <<vel_f <<" " <<acc <<" " <<situa_punti.size() <<std::endl;          //cout di prova
    }
  situa_punti = situa_punti_f;
  */