{

  gSystem->Load("libGeom");
  gSystem->Load("libEve");
  gSystem->Load("libMinuit");
  gSystem->Load("libCintex");
  Cintex::Enable();
  gSystem->Load("libWCSimRootDict");
  gSystem->Load("libWCSimRoot");
  gSystem->Load("libWCSimAnalysis");


  Double_t Dir[3],StartPos[3],HitPos[3],Intersect[3];
  Dir[0] = 1.;
  Dir[1] = 0.;
  Dir[2] = 0.;
  StartPos[0] = -2.;
  StartPos[1] = 0.;
  StartPos[2] = 0.;
  HitPos[0] = -10.;
  HitPos[1] = 3.5;
  HitPos[2] = 0.;
  Double_t lmda = 300.;
  Double_t distmu, distpho, timemu, timepho, openangle, D;

  WCSimCherenkovGeo chere;
  chere.MuonDistance(StartPos, Dir, HitPos, lmda, Intersect, openangle, distmu, distpho, timemu, timepho, D);
  std::cout << "i am good" << std::endl;
  //timepho = chere.PhoTime(lmda, distpho);
  //std::cout << "i am good2" << std::endl;
  //distmu = chere.MuonDistance(StartPos, Dir, HitPos, lmda, Intersect, distpho, timemu, timepho, openangle, D);
  std::cout << "the intersection position is: ";
  for (Int_t i=0; i<3; i++) std::cout << Intersect[i] << "\t";
  std::cout << std::endl;
  std::cout << "the information of muon: distance: " << distmu << ", time: " << timemu << std::endl;
  std::cout << "the information of photon: distance: " << distpho << ", time: " << timepho << std::endl;
  std::cout << openangle << "\t" << D << std::endl;
  /*Double_t Sub[3];
  Double_t ctc = WCSimParameters::CosThetaC;
  //Double_t ctc = 0.7431;
  for (Int_t i=0; i<3; i++) { Sub[i] = HitPos[i] - StartPos[i]; }
  Double_t prod1 = WCSimMathUtil::DotProduct(Dir,sub);
  Double_t prod2 = WCSimMathUtil::DotProduct(sub,sub);
  Double_t prod3 = 1-ctc*ctc;
  Double_t arg_a = prod3;
  Double_t arg_b = -2*prod1*prod3;
  Double_t arg_c = prod1*prod1 - prod2*ctc*ctc;

  WCSimCherenkovGeo chere;
  Double_t firstSol;
  Double_t secondSol;
  Double_t det = WCSimMathUtil::Determinant(arg_a, arg_b, arg_c);
  WCSimMathUtil::RealRoots(arg_a, arg_b, sqrt(det), firstSol, secondSol); 
  if (firstSol > secondSol) { std::cout << secondSol << std::endl; }
  else { std::cout << firstSol << std::endl; }*/
  
  //Double_t distpho = chere.WCSimCherenkovGeo::DistanceToIntersectLine(HitPos,StartPos,EndPos,Intersect);
  //std::cout << det << "\t" << firstSol << "\t" <<secondSol << std::endl; //<< "\t" << Intersect[0] << "\t" << Intersect[1] << "\t" << Intersect[2] << std::endl;


}
