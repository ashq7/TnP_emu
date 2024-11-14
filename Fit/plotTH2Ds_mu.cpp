/*usage: root -l -b -q plotTH2Ds_mu.cpp */

int plotTH2Ds_mu(void) {

    TString thisHLTPath = "HLTMu8Ele23";
    //TString thisHLTPath = "HLTMu23Ele12";
    TString year = "2018";
    TString outputPath = "/eos/user/a/aquinn/Ha1a2bbtautau_05Jul24/CMSSW_10_6_27/src/TnP_emu/Fit/RootHistograms/";
    TString path = "sf_mu_" + year + "_" + thisHLTPath + ".root";

    TFile *newFile = new TFile(path);
    if (!newFile->IsOpen() || newFile==0 ) {
        std::cout<<"ERROR: FILE "<< path <<" NOT FOUND; EXITING" << std::endl;
        return 0;
    }
    TH2F* newEff_mu_mc = (TH2F*) newFile->Get("eff_mc");
    if (newEff_mu_mc == 0) {
        std::cout << "ERROR: eff_mc not found in file; EXITING" << std::endl;
        return 0;
    }
    TH2F* newEff_mu_embedded = (TH2F*) newFile->Get("eff_embedded");
    if (newEff_mu_embedded == 0) {
        std::cout << "ERROR: eff_embedded not found in file; EXITING" << std::endl;
        return 0;
    }
    TH2F* newEff_mu_data = (TH2F*) newFile->Get("eff_data");
    if (newEff_mu_data == 0) {
        std::cout << "ERROR: eff_data not found in file; EXITING" << std::endl;
        return 0;
    }    
    TH2F* newSF_mu_mc = (TH2F*) newFile->Get("SF2D_mc");
    if (newSF_mu_mc == 0) {
        std::cout << "ERROR: SF2D_mc not found in file; EXITING" << std::endl;
        return 0;
    }

    TH2F* newSF_mu_embedded = (TH2F*) newFile->Get("SF2D_embedded");
    if (newSF_mu_embedded == 0) {
        std::cout << "ERROR: SF2D_embedded not found in file; EXITING" << std::endl;
        return 0;
    }
/*
    // Get the muons
    TH2F* newSF_muon = (TH2F*) newFile->Get("muon_SF2D");
    if (newSF_muon == 0) {
        std::cout << "ERROR: muon_SF2D;1 not found in file; EXITING" << std::endl;
        return 0;
    }

    newSF_muon->SetMaximum(2.0);
    newSF_muon->SetMinimum(0.0);
*/
    TCanvas* c1 = new TCanvas("Tcan","", 100, 20, 1000, 800);
    TLegend* leg = new TLegend(0.60,0.75,0.85,0.9);

    // Draw the muons MC eff 
    newEff_mu_mc->SetTitle("muon MC eff" year + thisHLTPath);
    newEff_mu_mc->Draw("");
    newEff_mu_mc->Draw("TEXT45 SAME");
    c1->SaveAs(outputPath + "muon_mc_eff_" + year + "_" + thisHLTPath + ".png");
    c1->SaveAs(outputPath + "muon_mc_eff_" + year + "_" + thisHLTPath + ".pdf");

    // Draw the muons Embedded eff
    newEff_mu_embedded->SetTitle("muon Embedded eff" + year + thisHLTPath);
    newEff_mu_embedded->Draw("");
    newEff_mu_embedded->Draw("TEXT45 SAME");
    c1->SaveAs(outputPath + "muon_embedded_eff_" + year + "_" + thisHLTPath + ".png");
    c1->SaveAs(outputPath + "muon_embedded_eff_" + year + "_" + thisHLTPath + ".pdf");

    // Draw the muons Data eff
    newEff_mu_data->SetTitle("muon Data eff " + year + "_" + thisHLTPath);
    newEff_mu_data->Draw("");
    newEff_mu_data->Draw("TEXT45 SAME");
    c1->SaveAs(outputPath + "muon_data_eff_" + year + "_" + thisHLTPath + ".png");
    c1->SaveAs(outputPath + "muon_data_eff_" + year + "_" + thisHLTPath + ".pdf");

    // Draw the muons SF2D
    //Embedded
    newSF_mu_embedded->SetTitle("muon Embedded SF" + year + thisHLTPath);
    newSF_mu_embedded->Draw("");
    newSF_mu_embedded->Draw("TEXT45 SAME");
    c1->SaveAs(outputPath + "muon_embedded_sf_" + year + "_" + thisHLTPath + ".png");
    c1->SaveAs(outputPath + "muon_embedded_sf_" + year + "_" + thisHLTPath + ".pdf");

    //MC
    newSF_mu_mc->SetTitle("muon MC SF" + year + thisHLTPath);
    newSF_mu_mc->Draw("");
    newSF_mu_mc->Draw("TEXT45 SAME");
    c1->SaveAs(outputPath + "muon_mc_sf_" + year + "_" + thisHLTPath + ".png");
    c1->SaveAs(outputPath + "muon_mc_sf_" + year + "_" + thisHLTPath + ".pdf");

/*    // Draw the muons
    newSF_muon->SetTitle("UL muon SF");
    newSF_muon->Draw("");
    newSF_muon->Draw("TEXT45 SAME");
    c1->SaveAs("/eos/user/s/skkwan/www/sfComparisons/muon_HLT_" + thisHLTPath + "_UL.pdf");
    c1->SaveAs("/eos/user/s/skkwan/www/sfComparisons/muon_HLT_" + thisHLTPath + "_UL.png");
*/
    return 1;
}