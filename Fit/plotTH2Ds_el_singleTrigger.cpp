/*usage: root -l -b -q plotTH2Ds_el_singleTrigger.cpp */

int plotTH2Ds_el_singleTrigger(void) {

    gStyle->SetOptStat(0);

    //Toggle menu (either/or):
    TString thisHLTPath = "HLTMu8Ele23";
    //TString thisHLTPath = "HLTMu23Ele12";

    TString year = "2016pre";
    //TString year = "2016post";
    //TString year = "2017";
    //TString year = "2018";

    TString outputPath = "/eos/user/a/aquinn/Ha1a2bbtautau_05Jul24/CMSSW_10_6_27/src/TnP_emu/Fit/RootHistograms/Dec18/";
    TString path = "sf_el_" + year + "_"  + thisHLTPath + ".root";

    TFile *newFile = new TFile(path);
    if (!newFile->IsOpen() || newFile==0 ) {
        std::cout<<"ERROR: FILE "<< path <<" NOT FOUND; EXITING" << std::endl;
        return 0;
    }
    TH2F* newEff_ele_mc = (TH2F*) newFile->Get("eff_mc");
    if (newEff_ele_mc == 0) {
        std::cout << "ERROR: eff_mc not found in file; EXITING" << std::endl;
        return 0;
    }
    TH2F* newEff_ele_embedded = (TH2F*) newFile->Get("eff_embedded");
    if (newEff_ele_embedded == 0) {
        std::cout << "ERROR: eff_embedded not found in file; EXITING" << std::endl;
        return 0;
    }
    TH2F* newEff_ele_data = (TH2F*) newFile->Get("eff_data");
    if (newEff_ele_data == 0) {
        std::cout << "ERROR: eff_data not found in file; EXITING" << std::endl;
        return 0;
    }    
    TH2F* newSF_ele_mc = (TH2F*) newFile->Get("SF2D_mc");
    if (newSF_ele_mc == 0) {
        std::cout << "ERROR: SF2D_mc not found in file; EXITING" << std::endl;
        return 0;
    }

    TH2F* newSF_ele_embedded = (TH2F*) newFile->Get("SF2D_embedded");
    if (newSF_ele_embedded == 0) {
        std::cout << "ERROR: SF2D_embedded not found in file; EXITING" << std::endl;
        return 0;
    }

    //Max and min
    newSF_ele_mc->SetMaximum(2.0);
    newSF_ele_embedded->SetMaximum(2.0);

    newSF_ele_mc->SetMinimum(0.0);
    newSF_ele_embedded->SetMinimum(0.0);
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

    // Draw the electrons MC eff 
    newEff_ele_mc->SetTitle("Electron MC eff" + year + "_" + thisHLTPath);
    newEff_ele_mc->Draw("");
    newEff_ele_mc->Draw("TEXT45 SAME");

    c1->SaveAs(outputPath + "electron_mc_eff_" + year +"_" + thisHLTPath + ".png");
    c1->SaveAs(outputPath + "electron_mc_eff_" + year +"_" + thisHLTPath + ".pdf");

    // Draw the electrons Embedded eff
    newEff_ele_embedded->SetTitle("Electron Embedded eff" + year + "_" + thisHLTPath);
    newEff_ele_embedded->Draw("");
    newEff_ele_embedded->Draw("TEXT45 SAME");
    c1->SaveAs(outputPath + "electron_embedded_eff_" + year + "_" + thisHLTPath + ".png");
    c1->SaveAs(outputPath + "electron_embedded_eff_" + year + "_" + thisHLTPath + ".pdf");

    // Draw the electrons Data eff
    newEff_ele_data->SetTitle("Electron Data eff" + year + "_" + thisHLTPath);
    newEff_ele_data->Draw("");
    newEff_ele_data->Draw("TEXT45 SAME");
    c1->SaveAs(outputPath + "electron_data_eff_" + year + "_" + thisHLTPath + ".png");
    c1->SaveAs(outputPath + "electron_data_eff_" + year + "_"  + thisHLTPath + ".pdf");

    // Draw the electrons SF2D
    //Embedded
    newSF_ele_embedded->SetTitle("Electron Embedded SF" + year + "_" + thisHLTPath);
    newSF_ele_embedded->Draw("");
    newSF_ele_embedded->Draw("TEXT45 SAME");
    c1->SaveAs(outputPath + "electron_embedded_sf_" + year + "_"  + thisHLTPath + ".png");
    c1->SaveAs(outputPath + "electron_embedded_sf_" + year + "_"  + thisHLTPath + ".pdf");

    newSF_ele_mc->SetTitle("Electron MC SF" + year + "_" + thisHLTPath);
    newSF_ele_mc->Draw("");
    newSF_ele_mc->Draw("TEXT45 SAME");
    c1->SaveAs(outputPath + "electron_mc_sf_" + year + "_" + thisHLTPath + ".png");
    c1->SaveAs(outputPath + "electron_mc_sf_" + year + "_"  + thisHLTPath + ".pdf");

/*    // Draw the muons
    newSF_muon->SetTitle("UL muon SF");
    newSF_muon->Draw("");
    newSF_muon->Draw("TEXT45 SAME");
    c1->SaveAs("/eos/user/s/skkwan/www/sfComparisons/muon_HLT_" + thisHLTPath + "_UL.pdf");
    c1->SaveAs("/eos/user/s/skkwan/www/sfComparisons/muon_HLT_" + thisHLTPath + "_UL.png");
*/
    return 1;
}

/*usage: root -l -b -q plot_scale_factors.C */

/*void plot_scale_factors()
{
    //draw MC efficiency 2D histogram
    eff_mc->Draw();
    eff_mc->Draw("TEXT45 SAME");
    c1->SaveAs("RootHistograms/eff_mc_HLTMu8Ele23.png");

    //draw data efficiency 2D histogram
    eff_data->Draw();
    eff_data->Draw("TEXT45 SAME");
    c1->SaveAs("RootHistograms/eff_data_HLTMu8Ele23.png");

    //draw embedded efficiency 2D histogram
    eff_embedded->Draw();
    eff_embedded->Draw("TEXT45 SAME");
    c1->SaveAs("RootHistograms/eff_embedded_HLTMu8Ele23.png");

    //draw MC Scale Factor 2D histogram
    SF2D_mc->Draw();
    SF2D_mc->Draw(“TEXT45 SAME”);
    c1->SaveAs("RootHistograms/SF2D_mc_HLTMu8Ele23.png");

    //draw Embedded Scale Factor 2D histogram
    SF2D_embedded->Draw();
    SF2D_embedded->Draw(“TEXT45 SAME”);
    c1->SaveAs("RootHistograms/SF2D_embedded_HLTMu8Ele23.png");
}
*/