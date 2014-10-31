void computeR(std::string filename)
{

  TChain* a = new TChain("tree/tree");
  a->Add(filename.data());
  ofstream fout;
  fout.open("minpt.dat");
  TH1F* h1=new TH1F("h1","",1000,0,1000);
  float vx[10];
  float vy[10];
  for(int i=1; i<=10;i++)
    {
      a->Draw("hitGlobalR>>h1",Form("hitSubDec==1 && hitLayer==%d",i));
      float trackR = h1->GetMean();
      cout << "trackR = " << trackR << endl;
      float minPt= 0.303*3.8*0.5*trackR/100;
      fout << trackR << " " << minPt << endl;
      vx[i-1]=trackR;
      vy[i-1]=minPt;
    }

  fout.close();

  TGraph* gr = new TGraph(10,vx,vy);
  gr->SetTitle("Minimum p_{T} for crossing barrel layers");
  gr->GetXaxis()->SetTitle("Barrel layer radius [cm]");
  gr->GetXaxis()->SetLabelSize(0.05);
  gr->GetXaxis()->SetTitleSize(0.05);
  gr->GetYaxis()->SetTitle("Minimum p_{T} [GeV/c]"); 
  gr->GetYaxis()->SetLabelSize(0.05);
  gr->GetYaxis()->SetTitleSize(0.05);
  gr->GetYaxis()->SetTitleOffset(0.9);
  gr->SetLineWidth(3);
  gr->SetMarkerSize(1.5);
  gr->SetMarkerStyle(8);
  gr->SetLineColor(4);
  gr->SetMarkerColor(1);
  gr->Draw("acp");

}
