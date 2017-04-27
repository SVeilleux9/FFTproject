#include <climits>
#include <cmath>
#include <complex>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

uint32_t reverseBits(uint32_t i) {
  register uint32_t mask = 0x55555555; // 0101...
  i = ((i & mask) << 1) | ((i >> 1) & mask);
  mask = 0x33333333; // 0011...
  i = ((i & mask) << 2) | ((i >> 2) & mask);
  mask = 0x0f0f0f0f; // 00001111...
  i = ((i & mask) << 4) | ((i >> 4) & mask);
  mask = 0x00ff00ff; // 0000000011111111...
  i = ((i & mask) << 8) | ((i >> 8) & mask);
  // 00000000000000001111111111111111 no need for mask
  i = (i << 16) | (i >> 16);
  return i;
}

int lg(uint32_t i) {
  int count = -1;
  while (i) {
    i = i >> 1;
    count++;
  }
  return count;
}

// Russian peasant algorithm
int pown(const int p) {
  uint32_t w = p;
  w |= w >> 1;
  w |= w >> 2;
  w |= w >> 4;
  w |= w >> 8;
  w |= w >> 16;
  uint32_t mask = w & ~(w >> 1);

  int a = 1;
  while (mask) {
    a = a * a;
    if (mask & p)
      a *= 2;
    mask >>= 1;
  }

  return a;
}

void iterativeFFT(const vector<complex<double> >& primal,
                  vector<complex<double> >& dual,
                  const int P) {
  const int N = primal.size();
  const bool inverse = P < 0;
  const int absP = inverse ? -P : P;

  // bottom level of iteration tree
  for (int i = 0; i < N; i++){
    int revi = reverseBits(i) >> (32 - absP);
    dual[i] = primal[revi];
  }

  // there are absP levels above the bottom
  for (int p = 1; p <= absP; p++) {
    // complex root of unity
    const int unityStep = 0x1 << p;
    const double theta = (inverse ? -1 : 1) * 2 * M_PI / unityStep; // INVERSE
    const complex<double> unityRoot(cos(theta), sin(theta));
    //cout << unityRoot << endl;

    // each higher level doubles the step size
    for (int offset = 0; offset < N; offset += unityStep) {
      complex<double> omega = 1;

      // combine within a step segment (note only iterate over half step)
      for (int k = 0; k < unityStep/2; k++) {
        const complex<double> u = dual[offset + k];

        const complex<double> t = omega * dual[offset + k + unityStep/2];
        omega *= unityRoot;

        dual[offset + k] = u + t;
        dual[offset + k + unityStep/2] = u - t;
      }
    }
  }

  if (inverse) // INVERSE
    for (int j = 0; j < N; j++)
      dual[j] /= N;
}

int main(int argc, char *argv[]) {
	double data[] = {
		1.000000, -0.104528, -0.978148, 0.309017, 0.913545, -0.500000, -0.809017, 0.669131, 
		0.669131, -0.809017, -0.500000, 0.913545, 0.309017, -0.978148, -0.104528, 1.000000
	};

	int N = sizeof(data)/sizeof(data[0]);
	int P = log(N)/log(2);


	// random coefficients for a polynomial (primal)
	vector<complex<double> > primal(N, 0);
	for (int i = 0; i < N; i++)
		primal[i] = data[i];

	// transformed dual
	vector<complex<double> > dual(N, 0);

	iterativeFFT(primal, dual, P); // primal -> dual

	for (int i = 0; i < N; i++)
		cout << i << "\t" << abs(dual[i]) << endl;


	exit(0);
}
