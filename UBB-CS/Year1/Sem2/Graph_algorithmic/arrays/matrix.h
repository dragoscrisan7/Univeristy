#ifndef BCU__MATRIX_H__
#define BCU__MATRIX_H__

///////////////////////////////////////////////////////////////////////
//
//	Matrices
//
///////////////////////////////////////////////////////////////////////

#include "except.h"
#include "ptr_own.h"
#include "vector.h"

namespace bcu {

template<class T>
class Matrix_const_ref;

template<class T>
class Matrix_ref;

template<class T>
class Matrix;

template<class T>
class Matrix {
public:
	Matrix();
	Matrix(Matrix<T> const& src);
	Matrix<T> const& operator=(Matrix<T> const& src);
	// TODO: add template copy constructor and assignment for compatible 
	// types
	Matrix(Int32 row, Int32 col);
	void init_size(Int32 row, Int32 col);

	Int32 nr_row() const;
	Int32 nr_col() const;
	T& operator() (Int32 i, Int32 j);
	const T& operator() (Int32 i, Int32 j) const;
	Vector_const_ref<T> row(Int32 r) const;
	Vector_const_ref<T> col(Int32 c) const;
	Matrix_const_ref<T> transpose() const;
	Vector_ref<T> row(Int32 r);
	Vector_ref<T> col(Int32 c);
	Matrix_ref<T> transpose();
private:
	friend class Matrix_ref<T>;
	friend class Matrix_const_ref<T>;
	Ptr_own_array<T> f_ptr;
	Int32 f_nr_row;
	Int32 f_nr_col;
};

template<class T>
class Matrix_ref {
public:
	Matrix_ref();
	Matrix_ref(Matrix<T>& m);
	Matrix_ref(T* start, Int32 nr_row, Int32 nr_col);
	Matrix_ref(T* start, Int32 nr_row, Int32 nr_col, 
		Int32 incr_row, Int32 incr_col);

	void operator=(Matrix_const_ref<T>& src);
	void operator=(Matrix_ref<T> src);
	void assign(Matrix_ref<T> src);
	T& operator() (Int32 r, Int32 c) const;
	Int32 nr_row() const;
	Int32 nr_col() const;
	Vector_ref<T> row(Int32 r) const;
	Vector_ref<T> col(Int32 c) const;
	Matrix_ref transpose() const;
private:
	T* f_start;
	Int32 f_nr_row;
	Int32 f_nr_col;
	Int32 f_incr_row;
	Int32 f_incr_col;
	friend class Matrix_const_ref<T>;
	void operator=(const Matrix_ref&); // should not be used; too confusing
};

template<class T>
class Matrix_const_ref {
public:
	Matrix_const_ref();
	Matrix_const_ref(Matrix<T> const& m);
	Matrix_const_ref(const T* start, Int32 nr_row, Int32 nr_col);
	Matrix_const_ref(const T* start, Int32 nr_row, Int32 nr_col, 
		Int32 incr_row, Int32 incr_col);
	Matrix_const_ref(Matrix_ref<T> const& src);
	void assign(Matrix_const_ref<T> src);
	const T& operator() (Int32 r, Int32 c) const;
	Int32 nr_row() const;
	Int32 nr_col() const;
	Vector_const_ref<T> row(Int32 r) const;
	Vector_const_ref<T> col(Int32 c) const;
	Matrix_const_ref<T> transpose() const;
private:
	const T* f_start;
	Int32 f_nr_row;
	Int32 f_nr_col;
	Int32 f_incr_row;
	Int32 f_incr_col;
	void operator=(const Matrix_const_ref&); // should not be used; too confusing
};

///////////////////////////////////////////////////////////////////
//
//	Implementation
//
///////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------
//
//	Matrix

template<class T> inline
Matrix<T>::Matrix()
	: f_nr_row(0)
	, f_nr_col(0)
{
	// empty
}

template<class T> inline
Matrix<T>::Matrix(Matrix<T> const& src)
	:f_ptr(new T[src.nr_row()*src.nr_col()])
	, f_nr_row(src.nr_row())
	, f_nr_col(src.nr_col())
{
	Int32 const size=src.nr_row()*src.nr_col();
	for(Int32 i=0 ; i<size ; ++i){
		f_ptr[i]=src.f_ptr[i];
	}
}

template<class T> inline
Matrix<T> const& 
Matrix<T>::operator=(Matrix<T> const& src)
{
	init_size(src.nr_row(), src.nr_col());
	Int32 const size=src.nr_row()*src.nr_col();
	for(Int32 i=0 ; i<size ; ++i){
		f_ptr[i]=src.f_ptr[i];
	}
	return *this;
}

template<class T> inline
Matrix<T>::Matrix(Int32 row, Int32 col)
	:f_ptr(new T[row*col])
	, f_nr_row(row)
	, f_nr_col(col)
{
	// empty
}

template<class T> inline
void
Matrix<T>::init_size(Int32 row, Int32 col)
{
	Ptr_own_array<T> temp(new T[row*col]);
	f_ptr.free();
	f_ptr.take(temp.ptr());
	temp.drop();
	f_nr_row=row;
	f_nr_col=col;
}

template<class T> inline
T&
Matrix<T>::operator() (Int32 i, Int32 j)
{
	bcu_assert(Dbg_precond, i>=0 && i<f_nr_row && j>=0 && j<f_nr_col);
	return f_ptr[i*f_nr_col+j];
}

template<class T> inline
const T&
Matrix<T>::operator() (Int32 i, Int32 j) const
{
	bcu_assert(Dbg_precond, i>=0 && i<f_nr_row && j>=0 && j<f_nr_col);
	return f_ptr[i*f_nr_col+j];
}

template<class T> inline
Int32 
Matrix<T>::nr_row() const
{
	return f_nr_row;
}

template<class T> inline
Int32 
Matrix<T>::nr_col() const
{
	return f_nr_col;
}

template<class T> inline
Vector_const_ref<T>
Matrix<T>::row(Int32 r) const
{
	bcu_assert(Dbg_precond, 0<=r && r<f_nr_row);
	return Vector_const_ref<T>(f_ptr.ptr()+r*f_nr_col, f_nr_col);
}

template<class T> inline
Vector_ref<T>
Matrix<T>::row(Int32 r)
{
	bcu_assert(Dbg_precond, 0<=r && r<f_nr_row);
	return Vector_ref<T>(f_ptr.ptr()+r*f_nr_col, f_nr_col);
}

template<class T> inline
Vector_const_ref<T>
Matrix<T>::col(Int32 c) const
{
	bcu_assert(Dbg_precond, 0<=c && c<f_nr_col);
	return Vector_const_ref<T>(f_ptr.ptr()+c, f_nr_row, f_nr_col);
}

template<class T> inline
Vector_ref<T> 
Matrix<T>::col(Int32 c)
{
	bcu_assert(Dbg_precond, 0<=c && c<f_nr_col);
	return Vector_ref<T>(f_ptr.ptr()+c, f_nr_row, f_nr_col);
}

template<class T> inline
Matrix_const_ref<T>
Matrix<T>::transpose() const
{
	return Matrix_const_ref<T>(f_ptr.ptr(), f_nr_col, f_nr_row, 1, f_nr_col);
}

template<class T> inline
Matrix_ref<T>
Matrix<T>::transpose()
{
	return Matrix_ref<T>(f_ptr.ptr(), f_nr_col, f_nr_row, 1, f_nr_col);
}

//----------------------------------------------
//
//	Matrix_ref

template<class T> inline
Matrix_ref<T>::Matrix_ref()
	:f_start(0)
	, f_nr_row(0)
	, f_nr_col(0)
	, f_incr_row(0)
	, f_incr_col(0)
{
	// empty
}

template<class T> inline
Matrix_ref<T>::Matrix_ref(Matrix<T>& m)
	:f_start(m.f_ptr.ptr())
	, f_nr_row(m.f_nr_row)
	, f_nr_col(m.f_nr_col)
	, f_incr_row(m.f_nr_col)
	, f_incr_col(1)
{
	// empty
}

template<class T> inline
Matrix_ref<T>::Matrix_ref(T* start, Int32 nr_row, Int32 nr_col)
	:f_start(start)
	, f_nr_row(nr_row)
	, f_nr_col(nr_col)
	, f_incr_row(nr_col)
	, f_incr_col(1)
{
	// empty
}

template<class T> inline
Matrix_ref<T>::Matrix_ref(T* start, Int32 nr_row, Int32 nr_col, 
		Int32 incr_row, Int32 incr_col)
	:f_start(start)
	, f_nr_row(nr_row)
	, f_nr_col(nr_col)
	, f_incr_row(incr_row)
	, f_incr_col(incr_col) 
{
	// empty
}

template<class T> inline
void
Matrix_ref<T>::operator=(Matrix_const_ref<T>& src)
{
	bcu_assert(Dbg_precond, src.nr_row()==nr_row() &&
		src.nr_col() == nr_col() );
	for(Int32 i=0 ; i<nr_row() ; ++i){
		for(Int32 j=0 ; j<nr_col() ; ++j){
			operator()(i,j)=src(i,j);
		}
	}
}

template<class T> inline
void
Matrix_ref<T>::operator=(Matrix_ref<T> src)
{
	bcu_assert(Dbg_precond, src.nr_row()==nr_row() &&
		src.nr_col() == nr_col() );
	for(Int32 i=0 ; i<nr_row() ; ++i){
		for(Int32 j=0 ; j<nr_col() ; ++j){
			operator()(i,j)=src(i,j);
		}
	}
}


template<class T> inline
T& 
Matrix_ref<T>::operator() (Int32 r, Int32 c) const
{
	bcu_assert(Dbg_precond, r>=0 && r<f_nr_row && c>=0 && c<f_nr_col);
	return f_start[r*f_incr_row+c*f_incr_col];
}

template<class T> inline
Int32 
Matrix_ref<T>::nr_row() const
{
	return f_nr_row;
}

template<class T> inline
Int32 
Matrix_ref<T>::nr_col() const
{
	return f_nr_col;
}

template<class T> inline
Vector_ref<T>
Matrix_ref<T>::row(Int32 r) const
{
	bcu_assert(Dbg_precond, 0<=r && r<f_nr_row);
	return Vector_ref<T>(f_start+r*f_incr_row, f_nr_col, f_incr_col);
}

template<class T> inline
Vector_ref<T>
Matrix_ref<T>::col(Int32 c) const
{
	bcu_assert(Dbg_precond, 0<=c && c<f_nr_col);
	return Vector_ref<T>(f_start+c*f_incr_col, f_nr_row, f_incr_row);
}

template<class T> inline
Matrix_ref<T>
Matrix_ref<T>::transpose() const
{
	return Matrix_ref(f_start, f_nr_col, f_nr_row, f_incr_col, f_incr_row);
}

//-----------------------------------------------------
//
//	Matrix_const_ref

template<class T> inline
Matrix_const_ref<T>::Matrix_const_ref()
	:f_start(0)
	, f_nr_row(0)
	, f_nr_col(0)
	, f_incr_row(0)
	, f_incr_col(0)
{
	// empty
}

template<class T> inline
Matrix_const_ref<T>::Matrix_const_ref(const Matrix<T>& m)
	:f_start(m.f_ptr.ptr())
	, f_nr_row(m.f_nr_row)
	, f_nr_col(m.f_nr_col)
	, f_incr_row(m.f_nr_col)
	, f_incr_col(1)
{
	// empty
}

template<class T> inline
Matrix_const_ref<T>::Matrix_const_ref(const T* start, Int32 nr_row, Int32 nr_col)
	:f_start(start)
	, f_nr_row(nr_row)
	, f_nr_col(nr_col)
	, f_incr_row(nr_col)
	, f_incr_col(1)
{
	// empty
}

template<class T> inline
Matrix_const_ref<T>::Matrix_const_ref(const T* start, Int32 nr_row, Int32 nr_col, Int32 incr_row, Int32 incr_col)
	:f_start(start)
	, f_nr_row(nr_row)
	, f_nr_col(nr_col)
	, f_incr_row(incr_row)
	, f_incr_col(incr_col)
{
	//empty
}

template<class T> inline
Matrix_const_ref<T>::Matrix_const_ref(const Matrix_ref<T>& src)
	:f_start(src.f_start)
	, f_nr_row(src.f_nr_row)
	, f_nr_col(src.f_nr_col)
	, f_incr_row(src.f_incr_row)
	, f_incr_col(src.f_incr_col)
{
	// empty
}

template<class T> inline
const T&
Matrix_const_ref<T>::operator() (Int32 r, Int32 c) const
{
	bcu_assert(Dbg_precond, r>=0 && r<f_nr_row && c>=0 && c<f_nr_col);
	return f_start[r*f_incr_row+c*f_incr_col];
}

template<class T> inline
Int32
Matrix_const_ref<T>::nr_row() const
{
	return f_nr_row;
}

template<class T> inline
Int32
Matrix_const_ref<T>::nr_col() const
{
	return f_nr_col;
}

template<class T> inline
Vector_const_ref<T>
Matrix_const_ref<T>::row(Int32 r) const
{
	bcu_assert(Dbg_precond, 0<=r && r<f_nr_row);
	return Vector_const_ref<T>(f_start+r*f_incr_row, f_nr_col, f_incr_col);
}

template<class T> inline
Vector_const_ref<T>
Matrix_const_ref<T>::col(Int32 c) const
{
	bcu_assert(Dbg_precond, 0<=c && c<f_nr_col);
	return Vector_const_ref<T>(f_start+c*f_incr_col, f_nr_row, f_incr_row);
}

template<class T> inline
Matrix_const_ref<T>
Matrix_const_ref<T>::transpose() const
{
	return Matrix_const_ref<T>(f_start, f_nr_col, f_nr_row, f_incr_col, f_incr_row);
}

}; // namespace bcu

#endif
