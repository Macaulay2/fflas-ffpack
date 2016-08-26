/* -*- mode: C++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
// vim:sts=4:sw=4:ts=4:noet:sr:cino=>s,f0,{0,g0,(0,\:0,t0,+0,=s


/* Copyright (c) FFLAS-FFPACK
* Written by Clement Pernet <clement.pernet@imag.fr>
* ========LICENCE========
* This file is part of the library FFLAS-FFPACK.
*
* FFLAS-FFPACK is free software: you can redistribute it and/or modify
* it under the terms of the  GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
* ========LICENCE========
*/
#define  __FFLASFFPACK_FORCE_SEQ

#include "fflas-ffpack/fflas-ffpack-config.h"
#include <iostream>
#include <givaro/modular.h>

#include "fflas-ffpack/fflas-ffpack.h"
#include "fflas-ffpack/utils/timer.h"
#include "fflas-ffpack/utils/Matio.h"
#include "fflas-ffpack/utils/args-parser.h"


using namespace std;

int main(int argc, char** argv) {
  
	size_t iter = 1;
	size_t    n    = 500;
	std::string file = "";
  	static int variant =0;
	size_t b = 150;
	Argument as[] = {
		{ 'b', "-b B", "Set the bitsize of the random characteristic.",  TYPE_INT , &b },
		{ 'n', "-n N", "Set the dimension of the matrix.",               TYPE_INT , &n },
		{ 'i', "-i R", "Set number of repetitions.",                     TYPE_INT , &iter },
		{ 'f', "-f FILE", "Set the input file (empty for random).",  TYPE_STR , &file },
		{ 'a', "-a algorithm", "Set the algorithmic variant", TYPE_INT, &variant },

		END_OF_ARGUMENTS
	};

  FFLAS::parseArguments(argc,argv,as);
  typedef Givaro::ZRing<Givaro::Integer> Field;
  FFPACK::FFPACK_CHARPOLY_TAG CT;
  switch (variant){
      case 0: CT = FFPACK::FfpackLUK; break;
      case 1: CT = FFPACK::FfpackKG; break;
      case 2: CT = FFPACK::FfpackDanilevski; break;
      case 3: CT = FFPACK::FfpackKGFast; break;
      case 4: CT = FFPACK::FfpackKGFastG; break;
      case 5: CT = FFPACK::FfpackHybrid; break;
      case 6: CT = FFPACK::FfpackArithProg; break;
      default: CT = FFPACK::FfpackLUK; break;
  }
  typedef Field::Element Element;

  Field F;
  FFLAS::Timer chrono;
  double time=0.0;

  Element *A;
  size_t bs=1;
  size_t size=b;
  for (size_t i=0;i<iter;++i){

	  if (!file.empty()){
		A = read_field (F, file.c_str(), &n, &n);
    }
    else{
      A = FFLAS::fflas_new<Element>(n*n);
      Field::RandIter G(F,size);
      for (size_t j=0; j< (size_t)n*n; ++j)
	G.random(*(A+j));
    }

    std::vector<Field::Element> cpol(n);
    chrono.clear();
    chrono.start();
    FFPACK::CharPoly (F, cpol, n, A, n, CT);
    chrono.stop();

    time+=chrono.usertime();
   
    bs = FFPACK::bitsize (n,n,A,n);
    FFLAS::fflas_delete( A);

  }
  
	// -----------
	// Standard output for benchmark - Alexis Breust 2014/11/14
  std::cerr << "n: "<<n<<" bitsize: "<<bs<<" Time: " << time / double(iter)
	    << " Gflops: " << "Irrelevant";
  FFLAS::writeCommandString(std::cerr, as) << std::endl;

  return 0;
}
