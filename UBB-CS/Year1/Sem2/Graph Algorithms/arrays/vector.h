//////////////////////////////////////////////////////////////////
//
//	bcu library
//
//	Containers: vectors and vector references
//
/////////////////////////////////////////////////////////////////

#ifndef BCU__VECTOR_H_
#define BCU__VECTOR_H_

#include "except.h"
#include "debug.h"
#include "ptr_own.h"
#include "move.h"

namespace bcu {

class Size_alloc {
public:
	Size_alloc()
		:f_alloc(0) {}
	explicit Size_alloc(bcu::Int32 alloc)
		:f_alloc(alloc) {}
	void set_alloc(Int32 alloc)
		{f_alloc=alloc;}
	Int32 alloc() const
		{return f_alloc;}


	bool needs_realloc(bcu::Int32 new_alloc) const
		{return (new_alloc>f_alloc || new_alloc<4*f_alloc);}
	Int32 get_realloc(Int32 new_alloc);
private:
	Int32 f_alloc;
};


template<class T>
class Vector;

template<class T, Int32 alloc>
class Vector_static;

template<class T>
class Vector_ref;

template<class T>
class Vector_const_ref;

/// @brief A vector of elements of type T
///
/// A vector of elements of type T. The vector is dynamically allocated,
/// therefore its number of elements can be changed at any time, although
/// that can cause reallocation, implying copying all elements and changing 
/// their addresses.
///
/// Note that type T must be copyable and must have default constructor.
template<class T>
class Vector {
public:
	Vector();
	~Vector() throw();
	Vector(const Vector<T>& );
	void operator=(Vector<T> const& src);

	explicit Vector(Int32 size);
	Vector(Int32 size, Int32 alloc);
	
	template<class Tx>
	explicit Vector(Vector_const_ref<Tx> src)
		:f_alloc(src.size()), f_n(src.size()), 
		f_tab(new T[f_alloc.alloc()])
		{
			for(int i=0 ; i<src.size() ; ++i){
				f_tab[i]=src[i];
			}
		}

	template<class Tx>
	void operator=(Vector_const_ref<Tx> src)
		{
			set_size(src.size());
			for(int i=0 ; i<src.size() ; ++i){
				f_tab[i]=src[i];
			}
		}
 
	void init_size(Int32 size);
	void set_size(Int32 new_size);
	void alloc(Int32 alloc);
	void set_size_alloc(Int32 size, Int32 alloc);

	const T& operator [] (Int32 idx) const;
	T& operator [] (Int32 idx);
	Int32 size() const;

	void append(const T& el);
	void insert(Int32 idx, const T& el);
	void insert_blank(Int32 idx, Int32 count);
	void remove(Int32 idx, Int32 count=1);

	void move(Int32 dest_idx, Int32 src_idx, 
		Int32 count);
private:
	Size_alloc f_alloc;
	Int32 f_n;
	Ptr_own_array<T> f_tab;

	friend class Vector_ref<T>;
	friend class Vector_const_ref<T>;
};

template<class T, int alloc>
class Vector_static {
public:
	Vector_static();
	Vector_static(Vector_static<T, alloc> const& src);
	void operator=(Vector_static<T, alloc> const& src);

	explicit Vector_static(int size);
	template<class Tx>
	Vector_static(Vector_const_ref<Tx> src);

	const T& operator[](Int32 idx) const;
	T& operator[](Int32 idx);
	Int32 size() const;
	void set_size(Int32 new_size);
private:
	T f_tab[alloc];
	Int32 f_n;
};

template<class T>
class Vector_ref {
public:
	Vector_ref(T* start, Int32 size, Int32 incr=1);
	Vector_ref(Vector<T>& vec);
	void operator=(Vector_const_ref<T> const& src);
	void operator=(Vector_ref<T> const& src);
	template<class Tv>
	void operator=(Vector<Tv> const& src);
	void assign(const Vector_ref<T>& src);
	T& operator [] (Int32 idx) const;
	Int32 size() const;
	Vector_ref<T> reverse() const;
	Vector_ref<T> range(Int32 left, Int32 right) const;
	Vector_ref<T> every(Int32 count) const;
private:
	T* f_start;
	Int32 f_size;
	Int32 f_incr;
	friend class Vector_const_ref<T>;
};

template<class T>
class Vector_const_ref {
public:
	Vector_const_ref(const T* start, Int32 size, Int32 incr=1);
	Vector_const_ref(const Vector_ref<T>& src);
	Vector_const_ref(const Vector<T>& vec);
	void assign(const Vector_const_ref<T>& src);
	const T& operator [] (Int32 idx) const;
	Int32 size() const;
	Vector_const_ref<T> reverse() const;
	Vector_const_ref<T> range(Int32 left, Int32 right) const;
	Vector_const_ref<T> every(Int32 count) const;
private:
	const T* f_start;
	Int32 f_size;
	Int32 f_incr;
	void operator=(const Vector_const_ref<T>&); // should not be used; too confusing
};


///////////////////////////////////////////////////////////////////
//
//	Inline and tempate implementation
//
//
///////////////////////////////////////////////////////////////////

//--------------------------------------------------------------
//
//	Vector
//

/// Creates an empty vector
template <class T> inline
Vector<T>::Vector()
	:f_n(0), f_tab(0)
{}

/// @brief Creates a vector of given size
/// @param size initial number of elements
///
/// Creates a vector of given size. The elements are default constructed.
template <class T> inline
Vector<T>::Vector(Int32 size)
	:f_alloc(size), f_n(size), f_tab(new T[size])
{}

template <class T> inline
Vector<T>::Vector(Int32 size, Int32 alloc)
	:f_alloc(alloc), f_n(size), f_tab(new T[alloc])
{}

template <class T> inline
Vector<T>::Vector(const Vector<T>& src)
	:f_alloc(src.f_n), f_n(src.f_n), f_tab(new T[src.f_n])
{
	for(int i=0;i<f_n;++i){
		f_tab[i]=src.f_tab[i];
	}
}

template <class T> inline
void
Vector<T>::operator = (const Vector<T>& src)
{
	if(f_alloc.needs_realloc(src.size())){
		Int32 alloc=f_alloc.get_realloc(src.size());
		Ptr_own_array<T> temp(new T[alloc]);
		for(int i=0 ; i<src.size() ; ++i){
			temp[i]=src[i];
		}
		f_alloc.set_alloc(alloc);
		f_n=src.size();
		f_tab.swap(temp);
	} else {
		f_n=src.size();
		for(int i=0 ; i<f_n ; ++i){
			f_tab[i]=src[i];
		}
	}
}

template <class T> inline
Vector<T>::~Vector() throw()
{}

template<class T> inline
const T& 
Vector<T>::operator[](Int32 idx) const
{
	bcu_assert(Dbg_precond, idx>=0 && idx<f_n);
	return f_tab[idx];
}

template <class T> inline
T& 
Vector<T>::operator[](Int32 idx)
{
	bcu_assert(Dbg_precond, idx>=0 && idx<f_n);
	return f_tab[idx];
}

template <class T> inline
Int32 
Vector<T>::size() const
{
	return f_n;
}

template <class T> inline
void 
Vector<T>::init_size(Int32 size)
{
	Ptr_own_array<T> temp(new T[size]);
	f_tab.swap(temp);
	f_n=size;
	f_alloc.set_alloc(size);
}

template <class T> inline
void Vector<T>::set_size(Int32 new_size)
{
	if(f_alloc.needs_realloc(new_size)){
		Int32 alloc=f_alloc.get_realloc(new_size);
		Ptr_own_array<T> temp(new T[alloc]);
		for(int i=0 ; i<new_size && i<f_n ; ++i){
			temp[i] = tmp_ref(f_tab[i]);
		}
		f_tab.swap(temp);
		f_alloc.set_alloc(alloc);
	}
	f_n=new_size;
}

template <class T> inline
void 
Vector<T>::append(const T& el)
{
	set_size(size()+1);
	operator[](size()-1)=el;
}

template <class T> inline
void 
Vector<T>::insert(Int32 idx, const T& el)
{
	bcu_assert(Dbg_precond, idx>=0 && idx<size());
	int i;
	set_size(size()+1);
	for(i=size()-1 ; i>idx ; --i){
		f_tab[i] = tmp_ref(f_tab[i-1]);
	}
	f_tab[idx]=el;
}

template <class T> inline
void 
Vector<T>::insert_blank(Int32 idx, Int32 count)
{
	int i;
	set_size(size()+count);
	int const start=idx+count;
	for(i=size()-1 ; i>=start ; --i){
		f_tab[i] = tmp_ref(f_tab[i-count]);
	}
}

template <class T> inline
void 
Vector<T>::remove(Int32 idx, Int32 count)
{
	int i;
	for(i=idx+count ; i<size() ; ++i){
		f_tab[i-count] = tmp_ref(f_tab[i]);
	}
	set_size(size()-count);
}

template <class T>
void 
Vector<T>::move(Int32 dest_idx,
	Int32 src_idx,
	Int32 count)
{
	int i;
	T* p;
	T* q;
	p=f_tab+src_idx;
	q=f_tab+dest_idx;
	if(src_idx>dest_idx) {
		for(i=0 ; i<count ; ++i,++p,++q)
			*q=*p;
	} else {
		for(i=0,p+=count,q+=count ; i<count ; ++i)
			*--q=*--p;
	}
}

//--------------------------------------------------
//
//	Vector_ref
//
//

template<class T> inline
Vector_ref<T>::Vector_ref(T* start, Int32 size, Int32 incr)
	:f_start(start), f_size(size), f_incr(incr) 
{
	// nothing else
}

template<class T> inline
Vector_ref<T>::Vector_ref(Vector<T>& v)
	:f_start(v.f_tab.ptr()), f_size(v.f_n), f_incr(1)
{
	// nothing else
}

template <class T> inline
void
Vector_ref<T>::operator = (Vector_const_ref<T> const& src)
{
	bcu_assert(Dbg_precond, src.size()==size());
	for(int i=0 ; i<size() ; ++i){
		f_start[i]=src[i];
	}
}

template <class T> inline
void
Vector_ref<T>::operator = (Vector_ref<T> const& src)
{
	bcu_assert(Dbg_precond, src.size()==size());
	for(int i=0 ; i<size() ; ++i){
		f_start[i]=src[i];
	}
}

template <class T>
template<class Tv> inline
void
Vector_ref<T>::operator = (Vector<Tv> const& src)
{
	bcu_assert(Dbg_precond, src.size()==size());
	for(int i=0 ; i<size() ; ++i){
		f_start[i]=src[i];
	}
}

template<class T> inline
void
Vector_ref<T>::assign(const Vector_ref<T>& src)
{
	f_start=src.f_start;
	f_size=src.f_size;
	f_incr=src.f_incr;
}

template<class T> inline
T& 
Vector_ref<T>::operator [] (Int32 idx) const
{
	bcu_assert(Dbg_precond, idx>=0 && idx<f_size);
	return f_start[idx*f_incr];
}

template<class T> inline
Int32
Vector_ref<T>::size() const
{
	return f_size;
}

template<class T> inline
Vector_ref<T>
Vector_ref<T>::reverse() const
{
	return Vector_ref(f_start+(f_size-1)*f_incr, f_size, -f_incr);
}

template<class T> inline
Vector_ref<T>
Vector_ref<T>::range(Int32 left, Int32 right) const
{
	bcu_assert(Dbg_precond, 0<=left && left<=right && right<=f_size); 
	return Vector_ref(f_start+left*f_incr, right-left, f_incr);
}

template<class T> inline
Vector_ref<T>
Vector_ref<T>::every(Int32 count) const
{
	return Vector_ref<T>(f_start, (f_size+count-1)/count, f_incr*count);
}


//----------------------------------------------------------------
//
//	Vector_const_ref
//

template<class T> inline
Vector_const_ref<T>::Vector_const_ref(const T* start, Int32 size, Int32 incr)
	:f_start(start), f_size(size), f_incr(incr) 
{
	// nothing
}

template<class T> inline
Vector_const_ref<T>::Vector_const_ref(const Vector_ref<T>& src)
	:f_start(src.f_start), f_size(src.f_size), f_incr(src.f_incr)
{
	// nothing
}

template<class T> inline
Vector_const_ref<T>::Vector_const_ref(const Vector<T>& vec)
	:f_start(vec.f_tab.ptr()), f_size(vec.f_n), f_incr(1)
{
	// nothing
}

template<class T> inline
void
Vector_const_ref<T>::assign(const Vector_const_ref<T>& src)
{
	f_start=src.f_start;
	f_size=src.f_size;
	f_incr=src.f_incr;
}

template<class T> inline
const T& 
Vector_const_ref<T>::operator [] (Int32 idx) const
{
	bcu_assert(Dbg_precond, idx>=0 && idx<f_size);
	return f_start[idx*f_incr];
}

template<class T> inline
Int32 
Vector_const_ref<T>::size() const
{
	return f_size;
}

template<class T> inline
Vector_const_ref<T>
Vector_const_ref<T>::reverse() const
{
	return Vector_const_ref(f_start+(f_size-1)*f_incr, f_size, -f_incr);
}

template<class T> inline
Vector_const_ref<T>
Vector_const_ref<T>::range(Int32 left, Int32 right) const
{
	bcu_assert(Dbg_precond, 0<=left && left<=right && right<=f_size);
	return Vector_const_ref(f_start+left*f_incr, right-left, f_incr);
}

template<class T> inline
Vector_const_ref<T>
Vector_const_ref<T>::every(Int32 count) const
{
	return Vector_const_ref<T>(f_start, (f_size+count-1)/count, f_incr*count);
}


//----------------------------------------------------------------
//
//	Vector_static
//

#if 0

template<class T, int alloc>
Vector_static<T,alloc>::Vector_static()
:f_n(0)
{
	// nothing else
}

template<typename T, int alloc>
Vector_static<T,alloc>::Vector_static(int size)
:f_n(size)
{
	bcu_assert(Dbg_precond, size<=alloc);
}

template<typename T, int alloc>
Vector_static<T,alloc>::Vector_static(Vector_static<T,alloc> const& src)
:f_n(src.f_n)
{
	for(int i=0 ; i<f_n ; ++i){
		f_tab[i]=src[i];
	}
}

template<typename T, int alloc>
Vector_static<T,alloc>::operator Vector_ref<T> ()
{
	return Vector_ref<T>(f_tab, f_n, 1);
}

template<typename T, int alloc>
Vector_static<T,alloc>::operator Vector_const_ref<T> () const
{
	return Vector_const_ref<T>(f_tab, f_n, 1);
}

template<typename T, int alloc>
const T& 
Vector_static<T,alloc>::operator[](Int32 idx) const
{
	bcu_assert(Dbg_precond, 0<=idx && idx<f_n);
	return f_tab[idx];
}

template<typename T, int alloc>
T& 
Vector_static<T,alloc>::operator[](Int32 idx)
{
	bcu_assert(Dbg_precond, 0<=idx && idx<f_n);
	return f_tab[idx];
}

template<typename T, int alloc>
Int32 
Vector_static<T,alloc>::size() const
{
	return f_n;
}

template<typename T, int alloc>
void 
Vector_static<T,alloc>::set_size(Int32 new_size)
{
	bcu_assert(Dbg_precond, 0<=new_size && new_size<=alloc);
	f_n=new_size;
}

#endif

}; // namespace bcu



#endif
