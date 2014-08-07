#include "WCSimMathUtil.hh"

#include "TMath.h"
#include <iostream>

namespace WCSimMathUtil {

  Double_t DotProduct(Double_t* A, Double_t* B)
  {
    Double_t dotprod = 0.;
    for ( Int_t i = 0; i < 3; i++) {
      dotprod += A[i]*B[i];
    }
    return  dotprod;
  }

  Double_t Magnitude(Double_t* A, Double_t* B)
  {
    Double_t dx     = fabs(A[0] - B[0]);
    Double_t dy     = fabs(A[1] - B[1]);
    Double_t dz     = fabs(A[2] - B[2]);
    return pythag(dx,dy,dz);
  }
  
  void SubtractVec(Double_t* A, Double_t* B, Double_t* res)
  {
    for (Int_t i = 0; i < 3; i++) {
      res[i] = A[i] - B[i];
    }
  }
  // Helper functions for solving quadratic equation
  // Function to evaluate the determinant
  Double_t Determinant(Double_t a, Double_t b, Double_t c) 
  {
    return (b * b) - (4 * a * c);
  } // end determinant

  // function to evaluate real roots
  void RealRoots(Double_t a, Double_t b, Double_t arg_sqrt, Double_t &firstRoot, Double_t &secondRoot) 
  {
    firstRoot  = (-b + arg_sqrt)/(2*a);
    secondRoot = (-b - arg_sqrt)/(2*a);
    //std::cout << "\nFirst Real Root: \t" << firstRoot << "\n";
    //std::cout << "Second Real Root: \t" << secondRoot << "\n";
   } // end realRoots

  
}         
