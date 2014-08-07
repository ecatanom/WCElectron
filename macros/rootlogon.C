// To set this as default, you need a .rootrc file in your home directory,
// containing the following line:
// Rint.Logon: /full/path/to/rootlogon.C

void rootlogon()
{
  printf("Welcome to the ROOT of all evils \n");

  // Defaults to classic style, but that's OK, we can fix it
  TStyle* novaStyle = new TStyle("novaStyle", "NOvA Style");

  // Centre title
  novaStyle->SetTitleAlign(22);
  novaStyle->SetTitleX(.5);
  novaStyle->SetTitleY(.95);
  novaStyle->SetTitleBorderSize(0);

  // No info box
  novaStyle->SetOptStat(0);

  //set the background color to white
  novaStyle->SetFillColor(10);
  novaStyle->SetFrameFillColor(10);
  novaStyle->SetCanvasColor(10);
  novaStyle->SetPadColor(10);
  novaStyle->SetTitleFillColor(0);
  novaStyle->SetStatColor(10);

  // Don't put a colored frame around the plots
  novaStyle->SetFrameBorderMode(0);
  novaStyle->SetCanvasBorderMode(0);
  novaStyle->SetPadBorderMode(0);

  // Set the default line color for a fit function to be red
  novaStyle->SetFuncColor(kRed);

  // Marker settings
  //  novaStyle->SetMarkerStyle(kFullCircle);

  // No border on legends
  novaStyle->SetLegendBorderSize(0);

  // Disabled for violating NOvA style guidelines
  // Scientific notation on axes
  //  TGaxis::SetMaxDigits(3);

  // Axis titles
  novaStyle->SetTitleSize(.055, "xyz");
  novaStyle->SetTitleOffset(.8, "xyz");
  // More space for y-axis to avoid clashing with big numbers
  novaStyle->SetTitleOffset(.9, "y");
  // This applies the same settings to the overall plot title
  novaStyle->SetTitleSize(.055, "");
  novaStyle->SetTitleOffset(.8, "");
  // Axis labels (numbering)
  novaStyle->SetLabelSize(.04, "xyz");
  novaStyle->SetLabelOffset(.005, "xyz");

  // Thicker lines
  novaStyle->SetHistLineWidth(2);
  novaStyle->SetFrameLineWidth(2);
  novaStyle->SetFuncWidth(2);

  // Set the number of tick marks to show
  novaStyle->SetNdivisions(506, "xyz");

  // Set the tick mark style
  novaStyle->SetPadTickX(1);
  novaStyle->SetPadTickY(1);

  // Fonts
  const int kNovaFont = 42;
  novaStyle->SetStatFont(kNovaFont);
  novaStyle->SetLabelFont(kNovaFont, "xyz");
  novaStyle->SetTitleFont(kNovaFont, "xyz");
  novaStyle->SetTitleFont(kNovaFont, ""); // Apply same setting to plot titles
  novaStyle->SetTextFont(kNovaFont);
  novaStyle->SetLegendFont(kNovaFont);

  // Get moodier colours for colz
  const Int_t NRGBs = 5;
  const Int_t NCont = 255;
  Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
  Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
  Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
  Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  novaStyle->SetNumberContours(NCont);
  
  
  
//minos TStyle
  TStyle* minosStyle = new  TStyle("minosStyle", "MINOS Style");
 
//set the background color to white
 minosStyle->SetFillColor(10);
 minosStyle->SetFrameFillColor(10);
 minosStyle->SetCanvasColor(10);
 minosStyle->SetPadColor(10);
 minosStyle->SetTitleFillColor(0);
minosStyle->SetStatColor(10);
 
//dont put a colored frame around the plots
 minosStyle->SetFrameBorderMode(0);
minosStyle->SetCanvasBorderMode(0);
 minosStyle->SetPadBorderMode(0);
 minosStyle->SetLegendBorderSize(0);
 
//use the primary color palette
 minosStyle->SetPalette(1,0);
 
//set the default line color for a histogram to be black
 minosStyle->SetHistLineColor(kBlack);

//set the default line color for a fit function to be red
 minosStyle->SetFuncColor(kRed);

//make the axis labels black
minosStyle->SetLabelColor(kBlack,"xyz");
 
//set the default title color to be black
 minosStyle->SetTitleColor(kBlack);
 
//set the margins
 minosStyle->SetPadBottomMargin(0.18);
 minosStyle->SetPadTopMargin(0.08);
 minosStyle->SetPadRightMargin(0.08);
 minosStyle->SetPadLeftMargin(0.17);
 
//set axis label and title text sizes
 minosStyle->SetLabelFont(42,"xyz");
 minosStyle->SetLabelSize(0.06,"xyz");
 minosStyle->SetLabelOffset(0.015,"xyz");
 minosStyle->SetTitleFont(42,"xyz");
 minosStyle->SetTitleSize(0.07,"xyz");
 minosStyle->SetTitleOffset(1.1,"yz");
 minosStyle->SetTitleOffset(1.0,"x");
 minosStyle->SetStatFont(42);
 minosStyle->SetStatFontSize(0.07);
 minosStyle->SetTitleBorderSize(0);
 minosStyle->SetStatBorderSize(0);
 minosStyle->SetTextFont(42);
 
//set line widths
 minosStyle->SetFrameLineWidth(2);
 minosStyle->SetFuncWidth(2);

//set the number of divisions to show
 minosStyle->SetNdivisions(506, "xy");
 
//turn off xy grids
 minosStyle->SetPadGridX(0);
 minosStyle->SetPadGridY(0);
 
//set the tick mark style
 minosStyle->SetPadTickX(1);
 minosStyle->SetPadTickY(1);
 
//turn off stats
 minosStyle->SetOptStat(0);
 
//marker settings
 minosStyle->SetMarkerStyle(20);
 minosStyle->SetMarkerSize(1.2);
 minosStyle->SetLineWidth(1); 
 
 //done
 minosStyle->cd();
 gROOT->ForceStyle();
 gStyle->ls();
 
 

  //gROOT->SetStyle("novaStyle");

  // Uncomment this line if you want to force all plots loaded from files
  // to use this same style
  //gROOT->ForceStyle();
 printf("Careful! Check gStyle (novaStyle or minosStyle) \n");
 gStyle->Print();


}

// Put a "NOvA Preliminary" tag in the corner
void Preliminary()
{
  TLatex* prelim = new TLatex(.9, .95, "NO#nuA Preliminary");
  prelim->SetTextColor(kBlue);
  prelim->SetNDC();
  prelim->SetTextSize(2/30.);
  prelim->SetTextAlign(32);
  prelim->Draw();
}

// Put a "NOvA Simulation" tag in the corner
void Simulation()
{
  TLatex* prelim = new TLatex(.9, .95, "NO#nuA Simulation");
  prelim->SetTextColor(kGray+1);
  prelim->SetNDC();
  prelim->SetTextSize(2/30.);
  prelim->SetTextAlign(32);
  prelim->Draw();
}

void CenterTitles(TH1* histo)
{
  histo->GetXaxis()->CenterTitle();
  histo->GetYaxis()->CenterTitle();
  histo->GetZaxis()->CenterTitle();  
}
