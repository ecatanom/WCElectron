#ifndef WCSIMMATHUTIL_HH
#define WCSIMMATHUTIL_HH

#include <cmath>
#include "TMath.h"

namespace WCSimMathUtil {
  
  template<class T> inline T sqr(T x){return x*x;}
  inline Double_t pythag(Double_t x, Double_t y)
   {
     return sqrt(sqr(x)+sqr(y));
   }
   
   inline Double_t pythag(Double_t x, Double_t y, Double_t z)
   {
     return sqrt(sqr(x)+sqr(y)+sqr(z));
   }
   
   inline Double_t pythag(Double_t x1, Double_t y1, Double_t z1, Double_t x2, Double_t y2, Double_t z2)
   {
     return sqrt(sqr(x2-x1)+sqr(y2-y1)+sqr(z2-z1));
   }
   // dot product between two vectors
   Double_t DotProduct(Double_t* A, Double_t* B);
   
   // magnitude of distance between two vectors
   Double_t Magnitude(Double_t* A, Double_t* B);
   Double_t Determinant(Double_t a, Double_t b, Double_t c);
   // res is the resultant vector subtracting B from A
   void SubtractVec(Double_t* A, Double_t* B, Double_t* res);
   void RealRoots(Double_t a, Double_t b, Double_t arg_sqrt, Double_t &firstRoot, Double_t &secondRoot); 

}

#endif  
