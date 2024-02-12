#ifndef BCU__MOVE_H_
#define BCU__MOVE_H_

namespace bcu {

template<class T>
class Tmp_ref;

/** @brief Explicit conversion back to the plain reference
*/
template<class T>
T&
obj(Tmp_ref<T> src);

/** @brief Pseudo-reference to temporary objects
*
* A @c Tmp_ref<T> acts almost like a reference to an object of type @c T.
* 
* It has a conversion to a @c T& , so it can be used almost everywhere 
* instead of a variable or a plain reference.
*
* A function getting a @c Tmp_ref<T> as a parameter can feel free to modify 
* at will the object behind the @c Tmp_ref<T> pseudo-reference; however,
* the resulting object must still be destroyable.
*
* The caller should bind a @c Tmp_ref<T> to an object only before calling
* a function for that object. After the function returns, the object
* will be in an unknown state, the only operations that can safely be
* performed on it are the destructor and assignment.
*/
template<class T>
class Tmp_ref {
public:
/** @brief Conversion to plain reference
*/
	operator T&() const
		{return *f_ptr;}
		
/** @brief Conversion to anything @c T is convertible to 
*/
	template<class R>
	operator R()
		{return *f_ptr;}
/** @brief binds a @c Tmp_ref<T> to a given l-value
*/
	explicit Tmp_ref(T* src)
		:f_ptr(src) {}
protected:
	T* f_ptr;
private:
	friend T& obj<T>(Tmp_ref<T> src);
	void operator=(Tmp_ref<T> const&); // not implemented
};

/** @brief Binds a @c Tmp_ref<T> to a given object
* @warning This means that if you pass the resulting @c Tmp_ref<T> to 
* a function, then the original @c src object can be modified at that 
* function's will.
*/
template<class T>
Tmp_ref<T>
tmp_ref(T& src)
{
	return Tmp_ref<T>(&src);
}

/** @brief Temporary return value object
*
* A @c Tmp_obj<T> is both an object of type @c T and a @c Tmp_ref<T>
* bound to it.
*
* A @c Tmp_obj<T> should be returned from a function instead of 
* @c T if a "move constructor" is defined for @c T
*
* @warning Never create a @c const @c Tmp_obj<T> . The object inside is
* never const.
*/
template<class T>
class Tmp_obj :public Tmp_ref<T> {
public:
	Tmp_obj(T const& src)
		:Tmp_ref<T>(&f_obj), f_obj(src) {}

	template<typename R>
	Tmp_obj(R src)
		:Tmp_ref<T>(&f_obj), f_obj(src) {}
		
	Tmp_obj(Tmp_obj<T> const& src)
		:Tmp_ref<T>(&f_obj), f_obj(src) {}

private:
	mutable T f_obj;
};

////////////////////////////////////////////////////////
//
//	Implementation
//
////////////////////////////////////////////////////////

template<class T> inline
T&
obj(Tmp_ref<T> src)
{
	return *src.f_ptr;
}

}; //namespace bcu

#endif
