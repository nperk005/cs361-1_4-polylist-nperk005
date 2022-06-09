#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <initializer_list>
#include <list>

#include "term.h"


/**
   This class implements a polynomial of the form
    c0 + c1 x + c2 x^2 + c3 x^3 + ...

*/


class Polynomial {
public:

  list<Term>::iterator itr;
  list<Term>::const_iterator citr;
  
  /**
   * Create a bad/invalid polynomial of degree -1.
   * 
   * Arithmetic operations are not permitted on this bad value
   * and may cause a program to crash.  Nonetheless, this value
   * is useful as a way of signalling invalid results.
   * 
   */
  Polynomial();

  /**
   * Create a polynomial representing a linear or constant formula ax + b.
   */
  Polynomial (int b, int a = 0);

  terms.push_back(b);
  /**
   * Create a polynomial containing a collections of terms.
   * 
   * @//param terms a set of terms
   */
  Polynomial (std::initializer_list<Term> terms);

  /**
   * Create a polynomial with the given coefficients.
   * E.g.,
   *   double c[] = {1, 2, 3};
   *   Polynomial p (3, c);
   * creates a polynomial p representing: 1 + 2*x + 3*x^2
   *
   * @param nCoeff number of coefficients in the input array
   * @param coeff  the coefficients of the new polynomial, starting
   *               with power 0.
   */
  Polynomial (int nCoeff, int coeff[]);


  /**
   * Get the coefficient of the term with the indicated power.
   * @param power the power of a term
   * @return the corresponding coefficient, or zero if power < 0 or if
   *          power > getDegree()
   */
  int getCoeff(int power) const;

  /**
   *  The degree of a polynomial is the largest exponent of x with a
   *  non-zero coefficient. E.g.,
   *     x^3 + 2x + 1  has degree 3
   *     42            has degree 0   (42 == 42 * x^0)
   *     0             is a special case and is regarded as degree -1
   *
   * @return the degree of this polynomial
   */
  int getDegree() const;

  /**
   * Add a polynomial to this one, returning their sum.
   *
   * @param p another polynomial
   * @return the sum of the two polynomials
   */
  Polynomial operator+ (const Polynomial& p) const;

  /**
   * Multiply this polynomial by a scalar.
   * @param scale the value by which to multiply each term in this polynomial
   * @return the polynomial resulting from this multiplication
   */
  Polynomial operator* (int scale) const;

  /**
   * Multiply this polynomial by a Term.
   * @param Term the value by which to multiply each term in this polynomial
   * @return the polynomial resulting from this multiplication
   */
  Polynomial operator* (Term term) const;


  /**
   * Multiply this polynomial by a scalar, altering this polynomial.
   * @param scale the value by which to multiply each term in this polynomial
   */
  void operator*= (int scale);


  /**
   * Divide one polynomial by another, if possible.
   *
   * @param p the demoninator, the polynomial being divided into this one
   * @return the polynomial resulting from this division or the bad
   *         value Polynomial() if p cannot be divided into this polynomial
   *         to get a quotient polynomial with integer coefficients and no remainder.
   */
  Polynomial operator/ (const Polynomial& p) const;


  /**
   * Compare this polynomial for equality against another.
   *
   * @param p another polynomial
   * @return true iff the polynomials have the same degree and their corresponding
   *           coefficients are equal.
   */
  bool operator== (const Polynomial& p) const;


private:
   /**
    * @brief The degree of the polynomial.
    * 
    * This is the largest power of x having a non-zero coefficient, or
    * zero if the polynomial has all zero coefficients.) Note that
    * adding polynomials together or scaling polynomials (multiplying by
    * a constant) could reduce the degree of the result.
    * 
    */
  int degree;
  
  /**
   * List of terms, in ascending order of power. 
   * Terms with zero coefficients are dropped.
   * An empty list of degree 0 is the polynomial: 0.
   */
  std::list<Term> terms;

  // For example, the polynomial x^2 + 2x -1 would have:
  //    degree: 2
  //    terms: {Term(-1, 0), Term(2, 1), Term(1, 2)}
  //
  // The polynomial 4x^2 - 12 would have:
  //    degree: 2
  //    terms: {Term(-12, 0), Term(4,2)}   
  //
  // The polynomial 42 would have:
  //    degree: 0
  //    terms: {Term(42, 0)}
  //
  // The polynomial 0 would have:
  //    degree: 0
  //    terms: {}
  //
  // A special "bad" value used to signal an unsuccessful operations is
  //    degree: -1
  //    terms: {}
  
  /**
   * A utility function to scan the current polynomial, putting it into
   * "normal form". In this case, the normal form will drop all terms with 
   * zero coefficients, adjusting the degree as necessary. 
   *
   * Polynomials should be kept in normal form at all times outside of the
   * actual member function bodies of this class.
   */
  void normalize();

  // A "friend" declaration means that the following function or class will
  // have access to this class's private data members, just as if it were a
  // member function of this class.
  friend std::ostream& operator<< (std::ostream&, const Polynomial&);

public:
  // For use by instructor only;
  bool sanityCheck() const;

};


/**
 *  Write a polynomial to an ostream. Format should be
 *     term0 + term1 + ...
 *
 *   @param out the stream to which to write the polynomial
 *   @param p the polynomial to write
 *   @return the stream out
 */
std::ostream& operator<< (std::ostream&, const Polynomial&);

/**
 * Note: a member function of the Polynomial class must have a polynomial
 * as the first argument (e.g., poly.operator*(x) <===> poly * x). These
 * functionssimply allows for the multiplication to be written with the
 * polynomial on the right.
 *
 * @param the value to multiply the polynomial by
 * @param p a polynomial
 * @return the product of scale and p
 */
inline
Polynomial operator* (int by, const Polynomial& p)
{ return p * by; }


inline
bool operator!= (const Polynomial& p, const Polynomial& q)
{
  return !(p == q);
}


#endif
