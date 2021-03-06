/*

    This file is part of the Maude 2 interpreter.

    Copyright 1997-2005 SRI International, Menlo Park, CA 94025, USA.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.

*/

//
//	Easy subcases for gcd based solver.
//

bool
MpzSystem::findConcensus(const mpz_class& a,
			 const mpz_class& b,
			 const mpz_class& u,
			 const mpz_class& c,
			 const mpz_class& d,
			 const mpz_class& v,
			 mpz_class& e,
			 mpz_class& f,
			 mpz_class& w)
{
  //
  //	Given two general solutions for x:
  //	  x = a + ib for i = 0,..., u
  //	  x = c + jd for j = 0,..., v
  //	compute a concensus solution:
  //	  x = e + kf for k = 0,..., w
  //	Any of u, v and w may be -1 to indicate unbounded.
  //	Assume b != 0 and d != 0.
  //
  Assert(b != 0, "b zero");
  Assert(d != 0, "d zero");
  mpz_class i_base;
  mpz_class i_inc;
  mpz_class j_base;
  mpz_class j_inc;
  if (solveTwoVariableProblem(b, -d, c - a, true, u, v, i_base, j_base, i_inc, j_inc, w))
    {
      e = a + i_base * b;
      f = i_inc * b;
      Assert(e == c + j_base * d, "base conflict " << e << " vs " << c + j_base * d);
      Assert(f == j_inc * d, "inc conflict");
      return true;
    }
  return false;
}

bool
MpzSystem::solveTwoVariableProblem(mpz_class a,
				   mpz_class b,
				   mpz_class c,
				   bool y_nonneg,
				   const mpz_class& x_bound,
				   const mpz_class& y_bound,
				   mpz_class& x_base,
				   mpz_class& y_base,
				   mpz_class& x_inc,
				   mpz_class& y_inc,
				   mpz_class& bound)
{
  //PRINT(a); PRINT(b); PRINT(c);  PRINT(y_nonneg);  PRINT(x_bound); PRINT_NL(y_bound);
  //
  //	For integers a, b, c with a != 0 and b != 0, generate the set of solutions to
  //	ax + by = c
  //	where x is nonnegative and bounded by x_bound (>= 0, -1 indicates unbounded)
  //	and y is nonnegaive if y_nonneg flag set and bounded by y_bound (>= 0, -1 indicates unbounded)
  //	encoded as (x_base, y_base) + k (x_inc, y_inc) for
  //	k = 0, 1,..., bound
  //	where bound may be -1 to represent unbounded.
  //
  Assert(a != 0, "a zero");
  Assert(b != 0, "b zero");
  if (b < 0)
    {
      a = -a;
      b = -b;
      c = -c;
    }
  bool neg_slope = true;
  bool neg_a = false;
  if (a < 0)
    {
      a = -a;
      neg_a = true;
      neg_slope = false;
    }
  {
    mpz_class g;
    mpz_class u;
    mpz_class v;
    mpz_gcdext(g.get_mpz_t(), u.get_mpz_t(), v.get_mpz_t(), a.get_mpz_t(), b.get_mpz_t());
 
    //PRINT(neg_slope); PRINT(a); PRINT(b); PRINT(g); PRINT(u); PRINT_NL(v);

    if (!mpz_divisible_p(c.get_mpz_t(), g.get_mpz_t()))
      return false;  // c not in the additive group generated by a and b
    mpz_class cs;
    mpz_divexact(cs.get_mpz_t(), c.get_mpz_t(), g.get_mpz_t());
    mpz_divexact(x_inc.get_mpz_t(), b.get_mpz_t(), g.get_mpz_t());
    mpz_divexact(y_inc.get_mpz_t(), a.get_mpz_t(), g.get_mpz_t());
    if (neg_slope)
      y_inc = -y_inc;
    if (neg_a)
      u = -u;
    x_base = u * cs;
    y_base = v * cs;
    //PRINT(cs); PRINT(x_base); PRINT_NL(y_base); 
  }
  //
  //	We now have a general solution over the integers; we need to clip it
  //	to respect nonnegativity and upper bounds.
  //
  //	t = least k such that x_base + k * x_inc >= 0;
  //
  mpz_class t;
  mpz_class m_x_base = -x_base;
  mpz_cdiv_q(t.get_mpz_t(), m_x_base.get_mpz_t(), x_inc.get_mpz_t());
  if (!neg_slope)
    {
      if (y_nonneg)
	{
	  //
	  //	y_k = least k such that y_base + k * y_inc >= 0
	  //
	  mpz_class y_k;
	  mpz_class m_y_base = -y_base;
	  mpz_cdiv_q(y_k.get_mpz_t(), m_y_base.get_mpz_t(), y_inc.get_mpz_t());
	  if (y_k > t)
	    t = y_k;
	}
      x_base += t * x_inc;
      y_base += t * y_inc;
      bound = -1;
      if (x_bound >= 0)
	{
	  //
	  //	bound = greatest k such that x_base + k * x_inc <= x_bound
	  //
	  mpz_class x_diff = x_bound - x_base;
	  mpz_fdiv_q(bound.get_mpz_t(), x_diff.get_mpz_t(), x_inc.get_mpz_t());
	  if (bound < 0)
	    return false;
	}
      if (y_bound >= 0)
	{
	  //
	  //	y_k = greatest k such that y_base + k * y_inc <= y_bound
	  //
	  mpz_class y_k;
	  mpz_class y_diff = y_bound - y_base;
	  mpz_fdiv_q(y_k.get_mpz_t(), y_diff.get_mpz_t(), y_inc.get_mpz_t());
	  if (y_k < 0)
	    return false;
	  if (bound == -1 || y_k < bound)
	    bound = y_k;
	}
    }
  else
    {
      if (y_bound >= 0)
	{
	  //
	  //	y_k = least k such that y_base + k * y_inc <= y_bound
	  //
	  mpz_class y_k;
	  mpz_class y_diff = y_bound - y_base;
	  mpz_cdiv_q(y_k.get_mpz_t(), y_diff.get_mpz_t(), y_inc.get_mpz_t());
	  if (y_k > t)
	    t = y_k;
	}
      x_base += t * x_inc;
      y_base += t * y_inc;
      bound = -1;
      if (x_bound >= 0)
	{
	  //
	  //	bound = greatest k such that x_base + k * x_inc <= x_bound
	  //
	  mpz_class x_diff = x_bound - x_base;
	  mpz_fdiv_q(bound.get_mpz_t(), x_diff.get_mpz_t(), x_inc.get_mpz_t());
	  if (bound < 0)
	    return false;
	}
      if (y_nonneg)
	{
	  //
	  //	y_k = greatest k such that y_base + k * y_inc >= 0
	  //
	  mpz_class y_k;
	  mpz_class m_y_base = -y_base;
	  mpz_fdiv_q(y_k.get_mpz_t(), m_y_base.get_mpz_t(), y_inc.get_mpz_t());
	  if (y_k < 0)
	    return false;
	  if (bound == -1 || y_k < bound)
	    bound = y_k;
	}
    }
  //PRINT(x_base); PRINT(y_base); PRINT(x_inc);  PRINT(y_inc);  PRINT_NL(bound);
  return true;
}
