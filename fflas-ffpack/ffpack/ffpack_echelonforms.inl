/* -*- mode: C++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
// vim:sts=4:sw=4:ts=4:noet:sr:cino=>s,f0,{0,g0,(0,\:0,t0,+0,=s

/* ffpack_echelon.h
 * Copyright (C) 2009, 2010 Clement Pernet
 *
 * Written by Clement Pernet <Clement.Pernet@imag.fr>
 *
 *
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
 *.
 */

#ifndef __FFLASFFPACK_ffpack_echelon_forms_INL
#define __FFLASFFPACK_ffpack_echelon_forms_INL

#define __FFLASFFPACK_GAUSSJORDAN_BASECASE 12

template <class Field>
inline size_t FFPACK::ColumnEchelonForm (const Field& F, const size_t M, const size_t N,
								  typename Field::Element_ptr A, const size_t lda,
								  size_t* P, size_t* Qt, const bool transform,
								  const FFPACK_LU_TAG LuTag)
{
	size_t r;
	if (LuTag == FFPACK::FfpackSlabRecursive)
		r = LUdivine (F, FFLAS::FflasNonUnit, FFLAS::FflasNoTrans, M, N, A, lda, P, Qt);
	else
		r = PLUQ (F, FFLAS::FflasNonUnit, M, N, A, lda, Qt, P);

	if (transform){
		ftrtri (F, FFLAS::FflasUpper, FFLAS::FflasNonUnit, r, A, lda);
		ftrmm (F, FFLAS::FflasLeft, FFLAS::FflasUpper, FFLAS::FflasNoTrans, FFLAS::FflasNonUnit, r, N-r, F.mOne, A, lda, A+r, lda);
	}

	return r;
}

template <class Field>
inline size_t FFPACK::RowEchelonForm (const Field& F, const size_t M, const size_t N,
							   typename Field::Element_ptr A, const size_t lda,
							   size_t* P, size_t* Qt, const bool transform,
							   const FFPACK_LU_TAG LuTag)
{
	size_t r;
	if (LuTag == FFPACK::FfpackSlabRecursive)
		r = LUdivine (F, FFLAS::FflasNonUnit, FFLAS::FflasTrans,  M, N, A, lda, P, Qt);
	else
		r = PLUQ (F, FFLAS::FflasUnit, M, N, A, lda, P, Qt);

	if (transform){
		ftrtri (F, FFLAS::FflasLower, FFLAS::FflasNonUnit, r, A, lda);
		ftrmm (F, FFLAS::FflasRight, FFLAS::FflasLower, FFLAS::FflasNoTrans, FFLAS::FflasNonUnit, M-r, r, F.mOne, A, lda, A+r*lda, lda);
	}

	return r;
}

template <class Field, class Cut, class Param>
inline size_t FFPACK::pColumnEchelonForm (const Field& F, const size_t M, const size_t N,
								  typename Field::Element_ptr A, const size_t lda,
								  size_t* P, size_t* Qt, const bool transform,
                                  const FFPACK_LU_TAG LuTag,
                                  const FFLAS::ParSeqHelper::Parallel<Cut,Param>& PSH)
 {
	size_t r;
	r = pPLUQ (F, FFLAS::FflasNonUnit, M, N, A, lda, Qt, P, PSH.numthreads());

	if (transform){
		ftrtri (F, FFLAS::FflasUpper, FFLAS::FflasNonUnit, r, A, lda, PSH);
		ftrmm (F, FFLAS::FflasLeft, FFLAS::FflasUpper, FFLAS::FflasNoTrans, FFLAS::FflasNonUnit, r, N-r, F.mOne, A, lda, A+r, lda, PSH);
	}

	return r;
}

template <class Field, class Cut, class Param>
inline size_t
FFPACK::pReducedColumnEchelonForm (const Field& F, const size_t M, const size_t N,
								  typename Field::Element_ptr A, const size_t lda,
								  size_t* P, size_t* Qt, const bool transform,
								  const FFPACK_LU_TAG LuTag,
                                  const FFLAS::ParSeqHelper::Parallel<Cut,Param>& PSH)
{
	size_t r;
	r = pColumnEchelonForm (F, M, N, A, lda, P, Qt, transform, LuTag, PSH);

	if (transform){
		ftrtri (F, FFLAS::FflasLower, FFLAS::FflasUnit, r, A, lda, PSH);
		ftrmm (F, FFLAS::FflasRight, FFLAS::FflasLower, FFLAS::FflasNoTrans, FFLAS::FflasUnit, M-r, r, F.one, A, lda, A+r*lda, lda, PSH);
		ftrtrm (F, FFLAS::FflasNonUnit, r, A, lda, PSH);
	} else {
		ftrsm (F, FFLAS::FflasRight, FFLAS::FflasLower, FFLAS::FflasNoTrans, FFLAS::FflasUnit, M-r, r, F.one, A, lda, A+r*lda, lda, PSH);
			//FFLAS::fidentity (F, r, r, A, lda);
			//applyP (F, FFLAS::FflasLeft, FFLAS::FflasTrans, r, 0,(int) r, A, lda, Qt);
	}
	return r;
}


template <class Field>
inline size_t
FFPACK::ReducedColumnEchelonForm (const Field& F, const size_t M, const size_t N,
								  typename Field::Element_ptr A, const size_t lda,
								  size_t* P, size_t* Qt, const bool transform,
								  const FFPACK_LU_TAG LuTag)
{
	size_t r;
	r = ColumnEchelonForm (F, M, N, A, lda, P, Qt, transform, LuTag);

	if (LuTag == FfpackSlabRecursive){
			// Putting Echelon in compressed triangular form : M = Q^T M
		for (size_t i=0; i<r; ++i){
			if ( Qt[i]> (size_t) i ){
				FFLAS::fswap( F, i,
							  A + Qt[i]*lda, 1,
							  A + i*lda, 1 );
			}
		}
	}
	if (transform){
		ftrtri (F, FFLAS::FflasLower, FFLAS::FflasUnit, r, A, lda);
		ftrmm (F, FFLAS::FflasRight, FFLAS::FflasLower, FFLAS::FflasNoTrans, FFLAS::FflasUnit, M-r, r, F.one, A, lda, A+r*lda, lda);
		ftrtrm (F, FFLAS::FflasNonUnit, r, A, lda);
	} else {
		ftrsm (F, FFLAS::FflasRight, FFLAS::FflasLower, FFLAS::FflasNoTrans, FFLAS::FflasUnit, M-r, r, F.one, A, lda, A+r*lda, lda);
			//FFLAS::fidentity (F, r, r, A, lda);
			//applyP (F, FFLAS::FflasLeft, FFLAS::FflasTrans, r, 0,(int) r, A, lda, Qt);
	}
	return r;
}



template <class Field>
inline size_t
FFPACK::ReducedRowEchelonForm (const Field& F, const size_t M, const size_t N,
							   typename Field::Element_ptr A, const size_t lda,
							   size_t* P, size_t* Qt, const bool transform,
							   const FFPACK_LU_TAG LuTag)
{
	if (LuTag == FfpackGaussJordan && transform){
		for (size_t i=0; i<N; i++)
			Qt[i] = i;
		for (size_t i=0; i<M; i++)
			P[i] = i;
		return Protected::GaussJordan(F, M, N, A, lda, 0, 0, N, P, Qt);
	}
	size_t r;
	r = RowEchelonForm (F, M, N, A, lda, P, Qt, transform, LuTag);
	if (LuTag == FfpackSlabRecursive){
			// Putting Echelon in compressed triangular form : M = M Q
		for (size_t i=0; i<r; ++i)
			if ( Qt[i]> i )
				FFLAS::fswap (F, i, A + Qt[i], lda, A + i, lda );
	}

	if (transform){
		ftrtri (F, FFLAS::FflasUpper, FFLAS::FflasUnit, r, A, lda);
		ftrmm (F, FFLAS::FflasLeft, FFLAS::FflasUpper, FFLAS::FflasNoTrans, FFLAS::FflasUnit, r, N-r, F.one, A, lda, A+r, lda);

		ftrtrm (F, FFLAS::FflasUnit, r, A, lda);
	} else {
		ftrsm (F, FFLAS::FflasLeft, FFLAS::FflasUpper, FFLAS::FflasNoTrans, FFLAS::FflasUnit, r, N-r, F.one, A, lda, A+r, lda);
			//FFLAS::fidentity (F, r, r, A, lda);
            //applyP(F, FFLAS::FflasRight, FFLAS::FflasNoTrans, r, 0, (int)r, A, lda, Qt);
	}
	return r;
}

template <class Field>
inline size_t
FFPACK::Protected::GaussJordan (const Field& F, const size_t M, const size_t N,
								typename Field::Element_ptr A, const size_t lda,
								const size_t colbeg, const size_t rowbeg, const size_t colsize,
								size_t* P, size_t* Q)
{
	if (rowbeg == M) return 0;
	if (colsize == 1){
		for (size_t i=rowbeg; i<M; ++i){
			if (!F.isZero(*(A+i*lda+colbeg))){
				P[rowbeg] = i;
				if (i!= rowbeg){
					F.assign(*(A+rowbeg*lda+colbeg),*(A+i*lda+colbeg));
					F.assign(*(A+i*lda+colbeg), F.zero);
				}
				typename Field::Element invpiv;
				F.inv(invpiv, *(A+rowbeg*lda + colbeg));
				F.assign(*(A+rowbeg*lda+colbeg), invpiv);
				F.negin(invpiv);
				FFLAS::fscalin(F,rowbeg,invpiv,A+colbeg,lda);
				FFLAS::fscalin(F,M-rowbeg-1,invpiv,A+colbeg+(rowbeg+1)*lda,lda);
				return 1;
			}
		}
		P[rowbeg]=colbeg;
		return 0;
	}

	if (colsize <= __FFLASFFPACK_GAUSSJORDAN_BASECASE){

		// write_field(F,std::cerr<<"BaseCase A = "<<std::endl, A+rowbeg*lda+colbeg, M-rowbeg, colsize, lda);
		// write_field(F,std::cerr<<"BaseCase A (tot) = "<<std::endl, A, M, N, lda);
		typename Field::Element_ptr A12 = A+colbeg;
		typename Field::Element_ptr A22 = A12+rowbeg*lda;
			/* [ I | Y1 |   ] [ X1     ]       [ I |  T1| S1 ]
			 * [   | Y2 |   ] [ X2 I   ] P A = [   |I T2| S2 ] Q^T
			 * [   | Y3 | I ] [ X3   I ]       [   |    | S3 ]
			 */

			/* Computes [ Y2 T2 ] in [ A22 A23 ]
			 *          [ Y3    ]    [ A32 A33 ]
			 */
		size_t R = ReducedRowEchelonForm (F, M-rowbeg, colsize, A22, lda, P+rowbeg, Q+colbeg, true, FfpackSlabRecursive);
		// write_field(F,std::cerr<<"Sortie RedRowEch A (tot) = "<<std::endl, A, M, N, lda);

		typename Field::Element_ptr A13 = A12+R;
		typename Field::Element_ptr A23 = A22+R;

			// Apply row permutation on [ A12 A13 ]
		for (size_t i=0; i<R; i++)
			Q[colbeg+i] += colbeg;
		for (size_t i=R; i<colsize; i++)
			Q[colbeg+i] = colbeg+i;
		for (size_t i=rowbeg; i<M; i++)
			P[i] += rowbeg;

		applyP (F, FFLAS::FflasRight, FFLAS::FflasTrans, rowbeg, colbeg, colbeg+R, A, lda, Q);
		// write_perm(std::cerr<<"Q = ",Q,N);
		// write_field(F,std::cerr<<"Apres applyP A (tot) = "<<std::endl, A, M, N, lda);

			// T1 <- A13 + A12 T2 in A13
		fgemm (F, FFLAS::FflasNoTrans, FFLAS::FflasNoTrans, rowbeg, colsize-R, R,
			   F.mOne, A12, lda, A23, lda, F.one, A13, lda);

			// Y1 <- - A12 Y2 in A12
		typename Field::Element_ptr tmp = FFLAS::fflas_new (F, rowbeg, R);
		FFLAS::fassign (F, rowbeg, R, A12, lda, tmp, R);
		fgemm (F, FFLAS::FflasNoTrans, FFLAS::FflasNoTrans, rowbeg, R, R,
			   F.mOne, tmp, R, A22, lda, F.zero, A12, lda);
		FFLAS::fflas_delete (tmp);
		// write_field(F,std::cerr<<"Sortie BaseCase A = "<<std::endl, A+rowbeg*lda+colbeg, M-rowbeg, colsize, lda);
		// write_field(F,std::cerr<<"Sortie BaseCase A (tot) = "<<std::endl, A, M, N, lda);

		return R;
	}
	size_t recsize = colsize / 2;

	// Recurive call on slice A*1
	size_t r1 = GaussJordan (F, M, N, A, lda, colbeg, rowbeg, recsize, P, Q);

	typename Field::Element_ptr A11 = A+colbeg;
	typename Field::Element_ptr A12 = A11+recsize;
	typename Field::Element_ptr A22 = A12+rowbeg*lda;
	typename Field::Element_ptr A21 = A11+rowbeg*lda;
	typename Field::Element_ptr A31 = A21+r1*lda;
	typename Field::Element_ptr A32 = A22+r1*lda;

	/**
	 *  ---------------------
	 * | I  | A11 | A12 |    |
	 * |----|-----|-----|----|
	 * |    |I | *| A22 |    |
	 * |    |0 | 0| A22 |    |
	 * |----|-----|-----|----|
	 * |    | 0   | A32 |    |
	 * |----|-----|-----|----|
	 *
	 * where the transformation matrix is stored at the pivot column position
	 */
	// Apply row permutation on A*2
	applyP (F, FFLAS::FflasLeft, FFLAS::FflasNoTrans, colsize - recsize, rowbeg, rowbeg+r1, A12, lda, P);

	// A12 <- A12 + A11 * A22
	fgemm (F, FFLAS::FflasNoTrans, FFLAS::FflasNoTrans, rowbeg, colsize - recsize, r1,
	       F.one, A11, lda, A22, lda, F.one, A12, lda);

	// A32 <- A32 + A31 * A22
	fgemm (F, FFLAS::FflasNoTrans, FFLAS::FflasNoTrans, M-rowbeg-r1, colsize - recsize, r1,
	       F.one, A31, lda, A22, lda, F.one, A32, lda);

	// A22 <- A21*A22
	typename Field::Element_ptr tmp = FFLAS::fflas_new (F, r1, colsize-recsize);
	FFLAS::fassign (F, r1, colsize-recsize, A22, lda, tmp, colsize-recsize);
	fgemm (F, FFLAS::FflasNoTrans, FFLAS::FflasNoTrans, r1, colsize-recsize, r1,
	       F.one, A21, lda, tmp, colsize-recsize, F.zero, A22, lda);
	FFLAS::fflas_delete (tmp);

	// Recurive call on slice A*2
	size_t r2 = GaussJordan (F, M, N, A, lda, colbeg + recsize, rowbeg + r1, colsize - recsize, P, Q);

	// Apply permutation on A*1
	applyP (F, FFLAS::FflasLeft, FFLAS::FflasNoTrans, r1, rowbeg+r1, rowbeg+r1+r2, A11, lda, P);

	typename Field::Element_ptr U11 = A11;
	typename Field::Element_ptr U12 = A12;
	typename Field::Element_ptr U21 = A31;
	typename Field::Element_ptr U22 = A32;
	typename Field::Element_ptr U31 = U21+r2*lda;
	typename Field::Element_ptr U32 = U31+recsize;

	// U11 <- U11 + U12 * U21
	fgemm (F, FFLAS::FflasNoTrans, FFLAS::FflasNoTrans, rowbeg+r1, r1, r2,
	       F.one, U12, lda, U21, lda, F.one, U11, lda);

	// U31 <- U31 + U32 * U21
	fgemm (F, FFLAS::FflasNoTrans, FFLAS::FflasNoTrans, M-rowbeg-r1-r2, r1, r2,
	       F.one, U32, lda, U21, lda, F.one, U31, lda);

	// U21 <- U22*U21
	tmp = FFLAS::fflas_new (F, r2, r1);
	FFLAS::fassign (F, r2, r1, U21, lda, tmp, r1);

	fgemm (F, FFLAS::FflasNoTrans, FFLAS::FflasNoTrans, r2, r1, r2,
	       F.one, U22, lda, tmp, r1, F.zero, U21, lda);
	FFLAS::fflas_delete(tmp);

	//Permute the non pivot columns to the end
	if (r1 < recsize && r2){
		size_t ncol = recsize -r1;
		size_t nrow = rowbeg + r1;
		typename Field::Element_ptr NZ1 = A11+r1;

		tmp = FFLAS::fflas_new (F, nrow, ncol);
		FFLAS::fassign (F, nrow, ncol, NZ1, lda, tmp, ncol);
			// Risky copy with overlap, but safe with the naive
			// implementation of fassign
			//! @bug safe ???
		FFLAS::fassign (F, M, r2, A12, lda, NZ1, lda);
		NZ1 +=  r2;
		FFLAS::fassign (F, nrow, ncol, tmp, ncol, NZ1, lda);
		FFLAS::fflas_delete (tmp);

		FFLAS::fzero(F,M-rowbeg-r1,recsize-r1,NZ1+(rowbeg+r1)*lda,lda);

        // TODO: only work locally in dimension recsize-r1+r2
		size_t * MathQ = new size_t[N];
		LAPACKPerm2MathPerm(MathQ, Q, N);
		size_t * temp = new size_t[ncol];
		for (size_t i=colbeg+r1, j=0; j<ncol; i++,j++)
			temp[j] = MathQ[i];
		for (size_t i=colbeg+r1, j=colbeg+recsize; i < colbeg+r1+r2; i++,j++)
			MathQ[i] = MathQ[j];
		for (size_t i=colbeg + r1+r2, j=0; i < colbeg+recsize+r2; i++,j++)
			MathQ[i] = temp[j];
		delete[] temp;
		MathPerm2LAPACKPerm(Q, MathQ, N);

		delete[] MathQ;
	}
	return r1+r2;
}

namespace FFPACK{

	/*********************************************/
	/* Accessors to Triangular and Echelon forms */
	/*********************************************/
template <class Field>
inline void
getTriangular (const Field& F, const FFLAS::FFLAS_UPLO Uplo,
			   const FFLAS::FFLAS_DIAG diag,
			   const size_t M, const size_t N, const size_t R,
			   typename Field::ConstElement_ptr A, const size_t lda,
			   typename Field::Element_ptr T, const size_t ldt,
			   const bool OnlyNonZeroVectors)
{
	typename Field::ConstElement_ptr Ai = A;
	typename Field::Element_ptr Ti = T;
	if (Uplo == FFLAS::FflasUpper){
		for (size_t i=0; i<R; i++, Ai += lda, Ti += ldt){
				//!@todo just one triangular fzero+fassign ?
			if (diag == FFLAS::FflasNonUnit){
				FFLAS::fzero(F,i,Ti,1);
				FFLAS::fassign (F, N-i, Ai+i, 1, Ti+i, 1);
			}
			else {
				FFLAS::fzero(F,i,Ti,1);
				F.assign (*(Ti+i), F.one);
				FFLAS::fassign (F, N-i-1, Ai+i+1, 1, Ti+i+1, 1);
			}
		}
		if (!OnlyNonZeroVectors)
			FFLAS::fzero(F,M-R,N,Ti,ldt);
	} else {
		size_t maxcol = (OnlyNonZeroVectors ? R : N);
		for (size_t i=0; i<R; i++, Ai += lda, Ti += ldt){
			if (diag == FFLAS::FflasNonUnit){
				FFLAS::fassign (F, i+1, Ai, 1, Ti, 1);
				FFLAS::fzero(F,maxcol-i-1,Ti+i+1,1);
			}
			else {
				FFLAS::fassign (F, i, Ai, 1, Ti, 1);
				F.assign (Ti[i], F.one);
				FFLAS::fzero(F,maxcol-i-1,Ti+i+1,1);
			}
		}
			//Ti = T+R*ldt;
		FFLAS::fassign(F, M-R, R, Ai, lda, Ti, ldt);
		if (!OnlyNonZeroVectors)
			FFLAS::fzero(F, M-R, N-R, Ti+R, ldt);
	}
}
template <class Field>
inline void
getTriangular (const Field& F, const FFLAS::FFLAS_UPLO Uplo,
			   const FFLAS::FFLAS_DIAG diag,
			   const size_t M, const size_t N, const size_t R,
			   typename Field::Element_ptr A, const size_t lda)
{
	typename Field::Element_ptr Ai = A;
	if (Uplo == FFLAS::FflasUpper){
		for (size_t i=0; i<R; i++, Ai += lda){
				//!@todo just one triangular fzero+fassign ?
			FFLAS::fzero(F,i,Ai,1);
			if (diag == FFLAS::FflasUnit)
				F.assign (Ai[i], F.one);
		}
		FFLAS::fzero(F,M-R,N,Ai,lda);
	} else {
		for (size_t i=0; i<R; i++, Ai += lda){
			if (diag == FFLAS::FflasUnit)
				F.assign (Ai[i], F.one);
			FFLAS::fzero(F,N-i-1,Ai+i+1,1);
		}
		FFLAS::fzero(F, M-R, N-R, Ai+R, lda);
	}
}

inline void
PLUQtoEchelonPermutation (const size_t N, const size_t R, const size_t * P, size_t * outPerm)
{
	size_t * MP = new size_t[N];
	size_t * invMP = new size_t[N];
	LAPACKPerm2MathPerm (MP, P, N);
	for (size_t i=0; i<N; ++i)
		invMP[MP[i]] = i;
	std::sort(MP,MP+R);
	for (size_t i=0;i<R; ++i)
		MP[i] = invMP [MP [i]];
	MathPerm2LAPACKPerm (outPerm, MP, R);
	delete[] MP;
	delete[] invMP;
}

template <class Field>
inline void
getEchelonForm (const Field& F, const FFLAS::FFLAS_UPLO Uplo,
				const FFLAS::FFLAS_DIAG diag,
				const size_t M, const size_t N, const size_t R, const size_t* P,
				typename Field::ConstElement_ptr A, const size_t lda,
				typename Field::Element_ptr T, const size_t ldt,
				const bool OnlyNonZeroVectors,
				const FFPACK_LU_TAG LuTag)
{
	if (LuTag == FfpackSlabRecursive){
		typename Field::ConstElement_ptr Ai = A;
		typename Field::Element_ptr Ti = T;
		if (Uplo == FFLAS::FflasUpper){ // Extracting a row echelon form
			for (size_t i=0; i<R; i++, Ai += lda, Ti += ldt){
				size_t piv = P[i];
				FFLAS::fzero(F,piv,Ti,1);
				if (diag == FFLAS::FflasNonUnit)
					FFLAS::fassign (F, N-piv, Ai+piv, 1, Ti+piv, 1);
				else {
					F.assign (Ti[piv], F.one);
					FFLAS::fassign (F, N-piv-1, Ai+piv+1, 1, Ti+piv+1, 1);
				}
			}
			if (!OnlyNonZeroVectors)
				FFLAS::fzero(F,M-R,N,Ti,ldt);
		} else { // Extracting a column echelon form
			for (size_t i=0; i<R; i++, Ai++, Ti++){
				size_t piv = P[i];
				FFLAS::fzero(F,piv,Ti,ldt);
				if (diag == FFLAS::FflasNonUnit)
					FFLAS::fassign (F, M-piv, Ai+piv*lda, lda, Ti+piv*ldt, ldt);
				else {
					F.assign (*(Ti+piv*ldt), F.one);
					FFLAS::fassign (F, M-piv-1, Ai+(piv+1)*lda, lda, Ti+(piv+1)*ldt, ldt);
				}
			}
			if (!OnlyNonZeroVectors)
				FFLAS::fzero(F,M,N-R,Ti,ldt);
		}
	} else { // TileRecursive
		getTriangular (F, Uplo, diag, M, N, R, A, lda, T, ldt, OnlyNonZeroVectors);
		if (Uplo == FFLAS::FflasLower){
			applyP (F, FFLAS::FflasLeft, FFLAS::FflasTrans, OnlyNonZeroVectors ? R : N, 0, M, T, ldt, P);

			size_t * LPerm = new size_t[R];
			PLUQtoEchelonPermutation (M, R, P, LPerm);

			applyP (F, FFLAS::FflasRight, FFLAS::FflasNoTrans, M, 0, R, T, ldt, LPerm);

			delete[] LPerm;
		} else{
			applyP (F, FFLAS::FflasRight,FFLAS::FflasNoTrans, OnlyNonZeroVectors ? R : M, 0, N, T, ldt, P);

			size_t * LPerm = new size_t[R];
			PLUQtoEchelonPermutation (N, R, P, LPerm);

			applyP (F, FFLAS::FflasLeft,FFLAS::FflasNoTrans, N, 0, R, T, ldt, LPerm);

			delete[] LPerm;
		}
	}
}
template <class Field>
inline void
getEchelonForm (const Field& F, const FFLAS::FFLAS_UPLO Uplo,
				const FFLAS::FFLAS_DIAG diag,
				const size_t M, const size_t N, const size_t R, const size_t* P,
				typename Field::Element_ptr A, const size_t lda,
				const FFPACK_LU_TAG LuTag)
{
	if (LuTag == FfpackSlabRecursive){
		typename Field::Element_ptr Ai = A;
		if (Uplo == FFLAS::FflasUpper){ // row echelon form
			for (size_t i=0; i<R; i++, Ai += lda){
				size_t piv = P[i];
				FFLAS::fzero(F,piv,Ai,1);
				if (diag == FFLAS::FflasUnit)
					F.assign (Ai[piv], F.one);
			}
			FFLAS::fzero(F,M-R,N,Ai,lda);
		} else { // Extracting a column echelon form
			for (size_t i=0; i<R; i++, Ai++){
				size_t piv = P[i];
				FFLAS::fzero(F,piv,Ai,lda);
				if (diag == FFLAS::FflasUnit)
					F.assign (*(Ai+piv*lda), F.one);
			}
			FFLAS::fzero(F,M,N-R,Ai,lda);
		}
	} else { // TileRecursive
		getTriangular (F, Uplo, diag, M, N, R, A, lda);

		if (Uplo == FFLAS::FflasLower){
			applyP (F, FFLAS::FflasLeft, FFLAS::FflasTrans, N, 0, M, A, lda, P);

			size_t * LPerm = new size_t[R];
			PLUQtoEchelonPermutation (M, R, P, LPerm);

			applyP (F, FFLAS::FflasRight, FFLAS::FflasNoTrans, M, 0, R, A, lda, LPerm);

			delete[] LPerm;
		} else {
			applyP (F, FFLAS::FflasRight,FFLAS::FflasNoTrans, M, 0, N, A, lda, P);

			size_t * LPerm = new size_t[R];
			PLUQtoEchelonPermutation (N, R, P, LPerm);

			applyP (F, FFLAS::FflasLeft,FFLAS::FflasNoTrans, N, 0, R, A, lda, LPerm);

			delete[] LPerm;
		}
	}
}

template <class Field>
inline void
getEchelonTransform (const Field& F, const FFLAS::FFLAS_UPLO Uplo,
					 const FFLAS::FFLAS_DIAG diag,
					 const size_t M, const size_t N, const size_t R, const size_t* P, const size_t * Q,
					 typename Field::ConstElement_ptr A, const size_t lda,
					 typename Field::Element_ptr T, const size_t ldt,
					 const FFPACK_LU_TAG LuTag)
{
	FFLAS::FFLAS_DIAG oppDiag = (diag == FFLAS::FflasNonUnit) ? FFLAS::FflasUnit : FFLAS::FflasNonUnit;
	FFLAS::FFLAS_UPLO oppUpLo = (Uplo == FFLAS::FflasUpper) ? FFLAS::FflasLower: FFLAS::FflasUpper;
	size_t Tdim = (Uplo == FFLAS::FflasUpper) ? M : N;
	size_t MaxPidx = (LuTag == FfpackTileRecursive) ? Tdim : R;

	getTriangular (F, oppUpLo, oppDiag, M, N, R, A, lda, T, ldt, true);

	FFLAS::fidentity (F, Tdim-R, Tdim-R, T + R*ldt +R, ldt);

	if (oppUpLo == FFLAS::FflasUpper){ // Transform is upper triangular
		FFLAS::fzero (F, Tdim - R, R, T + R*ldt, ldt);

		applyP (F, FFLAS::FflasLeft, FFLAS::FflasTrans, Tdim, 0, MaxPidx, T, ldt, P);

		if (LuTag==FfpackTileRecursive){
			size_t * LPerm = new size_t[R];
			PLUQtoEchelonPermutation (M, R, Q, LPerm);

			applyP (F, FFLAS::FflasRight, FFLAS::FflasNoTrans, N, 0, R, T, ldt, LPerm);

			delete[] LPerm;
		}
	} else { // Transform is lower triangular
		FFLAS::fzero (F, R, Tdim - R, T + R, ldt);

		applyP (F, FFLAS::FflasRight, FFLAS::FflasNoTrans, Tdim, 0, MaxPidx, T, ldt, P);

		if (LuTag==FfpackTileRecursive){
			size_t * LPerm = new size_t[R];
			PLUQtoEchelonPermutation (N, R, Q, LPerm);

			applyP (F, FFLAS::FflasLeft, FFLAS::FflasNoTrans, M, 0, R, T, ldt, LPerm);

			delete[] LPerm;
		}
	}
}
template <class Field>
inline void
getReducedEchelonForm (const Field& F, const FFLAS::FFLAS_UPLO Uplo,
					   const size_t M, const size_t N, const size_t R, const size_t* P,
					   typename Field::ConstElement_ptr A, const size_t lda,
					   typename Field::Element_ptr T, const size_t ldt,
					   const bool OnlyNonZeroVectors,
					   const FFPACK_LU_TAG LuTag)
{
	size_t MaxPidx = (LuTag == FfpackSlabRecursive) ? R : ((Uplo == FFLAS::FflasUpper)?N:M);

	FFLAS::fidentity (F, R, R, T, ldt);

	if (Uplo == FFLAS::FflasUpper){  // Extracting a reduced row echelon form
		FFLAS::fassign(F, R, N-R, A+R, lda, T+R, ldt);

		applyP (F, FFLAS::FflasRight, FFLAS::FflasNoTrans, R, 0, MaxPidx, T, ldt, P);

		if (!OnlyNonZeroVectors)
			FFLAS::fzero (F, M-R, N, T + R*ldt, ldt);

		if (LuTag==FfpackTileRecursive){
			size_t * LPerm = new size_t[R];
			PLUQtoEchelonPermutation (N, R, P, LPerm);

			applyP (F, FFLAS::FflasLeft, FFLAS::FflasNoTrans, N, 0, R, T, ldt, LPerm);

			delete[] LPerm;
		}

	} else { // Extracting a reduced column echelon form
		FFLAS::fassign(F, M-R, R, A+R*lda, lda, T+R*ldt, ldt);

		applyP (F, FFLAS::FflasLeft, FFLAS::FflasTrans, R, 0, MaxPidx, T, ldt, P);

		if (!OnlyNonZeroVectors)
			FFLAS::fzero (F, M, N-R, T + R, ldt);

		if (LuTag==FfpackTileRecursive){
			size_t * LPerm = new size_t[R];
			PLUQtoEchelonPermutation (M, R, P, LPerm);

			applyP (F, FFLAS::FflasRight, FFLAS::FflasNoTrans, M, 0, R, T, ldt, LPerm);

			delete[] LPerm;
		}
	}
}
template <class Field>
inline void
getReducedEchelonForm (const Field& F, const FFLAS::FFLAS_UPLO Uplo,
					   const size_t M, const size_t N, const size_t R, const size_t* P,
					   typename Field::Element_ptr A, const size_t lda,
					   const FFPACK_LU_TAG LuTag)
{
	size_t MaxPidx = (LuTag == FfpackSlabRecursive) ? R : ((Uplo == FFLAS::FflasUpper)?N:M);
	FFLAS::fidentity (F, R, R, A, lda);
	if (Uplo == FFLAS::FflasUpper){  // Extracting a reduced row echelon form
		applyP (F, FFLAS::FflasRight, FFLAS::FflasNoTrans, R, 0, MaxPidx, A, lda, P);

		FFLAS::fzero (F, M-R, N, A + R*lda, lda);

		if (LuTag==FfpackTileRecursive){
			size_t * LPerm = new size_t[R];
			PLUQtoEchelonPermutation (N, R, P, LPerm);

			applyP (F, FFLAS::FflasLeft, FFLAS::FflasNoTrans, N, 0, R, A, lda, LPerm);

			delete[] LPerm;
		}

	} else { // Extracting a reduced column echelon form
		applyP (F, FFLAS::FflasLeft, FFLAS::FflasTrans, R, 0, MaxPidx, A, lda, P);

		FFLAS::fzero (F, M, N-R, A + R, lda);

		if (LuTag==FfpackTileRecursive){
			size_t * LPerm = new size_t[R];
			PLUQtoEchelonPermutation (M, R, P, LPerm);

			applyP (F, FFLAS::FflasRight, FFLAS::FflasNoTrans, M, 0, R, A, lda, LPerm);

			delete[] LPerm;
		}
	}
}

template <class Field>
inline void
getReducedEchelonTransform (const Field& F, const FFLAS::FFLAS_UPLO Uplo,
							const size_t M, const size_t N, const size_t R, const size_t* P, const size_t* Q,
							typename Field::ConstElement_ptr A, const size_t lda,
							typename Field::Element_ptr T, const size_t ldt,
							const FFPACK_LU_TAG LuTag)
{
	FFLAS::FFLAS_UPLO oppUpLo = (Uplo == FFLAS::FflasUpper) ? FFLAS::FflasLower: FFLAS::FflasUpper;
	size_t Tdim = (Uplo == FFLAS::FflasUpper) ? M : N;
	size_t MaxPidx = (LuTag == FfpackTileRecursive) ?  Tdim : R;

	FFLAS::fidentity (F, Tdim-R, Tdim-R, T + R*ldt +R, ldt);

	if (oppUpLo == FFLAS::FflasUpper){ // Transform is upper triangular
		FFLAS::fassign (F, R, N, A, lda, T, ldt);

		FFLAS::fzero (F, Tdim - R, R, T + R*ldt, ldt);

		applyP (F, FFLAS::FflasLeft, FFLAS::FflasTrans, Tdim, 0, MaxPidx, T, ldt, P);

		if (LuTag==FfpackTileRecursive){
			size_t * LPerm = new size_t[R];
			PLUQtoEchelonPermutation (M, R, Q, LPerm);

			applyP (F, FFLAS::FflasRight, FFLAS::FflasNoTrans, Tdim, 0, R, T, ldt, LPerm);

			delete[] LPerm;
		}
	} else { // Triangular is lower triangular
		FFLAS::fassign (F, M, R, A, lda, T, ldt);

		FFLAS::fzero (F, R, Tdim - R, T + R, ldt);

		applyP (F, FFLAS::FflasRight, FFLAS::FflasNoTrans, Tdim, 0, MaxPidx, T, ldt, P);

		if (LuTag==FfpackTileRecursive){
			size_t * LPerm = new size_t[R];
			PLUQtoEchelonPermutation (N, R, Q, LPerm);

			applyP (F, FFLAS::FflasLeft, FFLAS::FflasNoTrans, Tdim, 0, R, T, ldt, LPerm);

			delete[] LPerm;
		}
	}
}

} // FFPACK
#endif  // __FFLASFFPACK_ffpack_echelon_forms_INL
