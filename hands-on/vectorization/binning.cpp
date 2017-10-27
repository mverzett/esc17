#include<random>
#include<iostream>
#include<fstream>
#include<iomanip>
#include<array>
#include<cmath>
#include<cassert>
#include <chrono>
#include "../architecture/benchmark.h"
#include "simpleSinCos.h"
#include <omp.h>

std::mt19937 eng;
std::mt19937 eng2;
std::uniform_real_distribution<double> rgen(0.,1.);

template<typename T>
void put(std::ostream& co, T x) {
  unsigned const char * out = (unsigned const char *)(&x);
  for(int i=0; i<sizeof(T); ++i) co<< out[i];
}


int main() {

  constexpr int N=1<<16;
  std::cout << "working with batch of " << N << " particles" << std::endl;


  struct Point { float phi,r; };
  struct Points {
    std::array<Point,N> p;
  };
  struct PointsSoA {
    std::array<float,N> phi;
    std::array<float,N> r;
  };


  PointsSoA points;
  
  auto start = std::chrono::high_resolution_clock::now();
  auto delta = start - start;
  constexpr int nthreads = 2;
  omp_set_num_threads(nthreads);
  omp_set_dynamic(0);
  constexpr int NBin = 100;
  constexpr float binWidth = 2./NBin;
  constexpr float binWInv = 1./binWidth;
  struct Hist {
    Hist(){}
    Hist& operator+(const Hist& other) {
      #pragma omp parallel for
      for(int i=0; i<=NBin; i++) {
	for(int j=0; i<=NBin; i++) {
	  this->bin[i][j] = other.bin[i][j];
	}
      }
      return *this;
    }
    int bin[NBin+1][NBin+1] = {0};
  };
  Hist h;
  for(size_t i=0; i<N; i++) {
    points.phi[i] = -M_PI +2.*M_PI*rgen(eng);
    points.r  [i] =  rgen(eng);
  }

  //outer loop just to make timing "macroscopical"
  for (int j=0; j<10000; ++j) {

    // for(auto & p : points.p) {
    //   p.phi = -M_PI +2.*M_PI*rgen(eng);
    //   p.r =  rgen(eng);
    // }
    for(int i=0; i <= NBin;i++){
      for(int k=0; k <= NBin;k++) {
	h.bin[i][k] = 0;
      }
    }

    delta -= (std::chrono::high_resolution_clock::now()-start);
    benchmark::touch(points);
    // the real loop
    const float *points_phi = &points.phi[0];
    const float *points_r = &points.r[0];
    std::array<Hist, nthreads> histos; 
    constexpr int iblock = N/nthreads;
#pragma omp parallel 
    {
      int ithread = omp_get_thread_num();
      // size_t start = ithread*iblock;
      // size_t stop = (ithread+1)*iblock; 
      // if(ithread == (nthreads-1)) stop=N;
      int xs[N] = {0};
      int ys[N] = {0};
#pragma omp for schedule(static) nowait
      for(size_t i=0; i<N; i++) {
	float sin, cos;
	simpleSinCos(points_phi[i], sin, cos);
	auto x = points_r[i]*cos; //std::cos(points.phi[i]);
	auto y = points_r[i]*sin; //std::sin(points.phi[i]);
	xs[i] = (x+1.f)*binWInv;
	ys[i] = (y+1.f)*binWInv;
	} 

#pragma omp for schedule(static)
      for(size_t i=0; i<N; i++) {
	++histos[ithread].bin[xs[i]][ys[i]];
      }
  }

    for(int i=0; i<nthreads; i++) h = h+histos[0];
    //   // if(xs[i] / nthreads == thread_id)
    // }
  // }
    benchmark::keep(h);
    delta += (std::chrono::high_resolution_clock::now()-start);
//    std::cout << '.';
   }
   std::cout <<" Computation took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(delta).count()
              << " ms" << std::endl;

   return 0;
}
