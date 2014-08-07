{

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

}

