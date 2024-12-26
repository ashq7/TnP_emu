/*usage: root -l -b -q plotTH2Ds_el.cpp */

int plotTH2Ds_el(void) {

    gStyle->SetOptStat(0);

    //HLT paths
    TString firstHLTPath = "HLTMu8Ele23";
    TString secondHLTPath = "HLTMu23Ele12";

    //Toggle menu (either/or):
    //TString year = "2016pre";
    TString year = "2016post";
    //TString year = "2017";
    //TString year = "2018";

    TString outputPath = "/eos/user/a/aquinn/Ha1a2bbtautau_05Jul24/CMSSW_10_6_27/src/TnP_emu/Fit/RootHistograms/Dec26/"+ year +"/electron/";

    //first cross-trigger: HLTMu8Ele23
    TString path = "sf_el_" + year + "_" + firstHLTPath + ".root";

    TFile *newFile = new TFile(path);
    if (!newFile->IsOpen() || newFile==0 ) {
        std::cout<<"ERROR: FILE "<< path <<" NOT FOUND; EXITING" << std::endl;
        return 0;
    }
    TH2F* newEff_ele_mc = (TH2F*) newFile->Get("eff_mc");
    if (newEff_ele_mc == 0) {
        std::cout << "ERROR: eff_mc not found in file "<< path <<"; EXITING" << std::endl;
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

    TCanvas* c1 = new TCanvas("Tcan","", 100, 20, 1000, 800);
    TLegend* leg = new TLegend(0.60,0.75,0.85,0.9);

    // Draw the electrons MC eff 
    newEff_ele_mc->SetTitle("Electron MC eff" + year + "_" + firstHLTPath);
    newEff_ele_mc->Draw("");
    newEff_ele_mc->Draw("TEXT45 SAME");

    c1->SaveAs(outputPath + "electron_mc_eff_" + year +"_" + firstHLTPath + ".png");
    c1->SaveAs(outputPath + "electron_mc_eff_" + year +"_" + firstHLTPath + ".pdf");

    // Draw the electrons Embedded eff
    newEff_ele_embedded->SetTitle("Electron Embedded eff" + year + "_" + firstHLTPath);
    newEff_ele_embedded->Draw("");
    newEff_ele_embedded->Draw("TEXT45 SAME");
    c1->SaveAs(outputPath + "electron_embedded_eff_" + year + "_" + firstHLTPath + ".png");
    c1->SaveAs(outputPath + "electron_embedded_eff_" + year + "_" + firstHLTPath + ".pdf");

    // Draw the electrons Data eff
    newEff_ele_data->SetTitle("Electron Data eff" + year + "_" + firstHLTPath);
    newEff_ele_data->Draw("");
    newEff_ele_data->Draw("TEXT45 SAME");
    c1->SaveAs(outputPath + "electron_data_eff_" + year + "_" + firstHLTPath + ".png");
    c1->SaveAs(outputPath + "electron_data_eff_" + year + "_"  + firstHLTPath + ".pdf");

    // Draw the electrons SF2D
    //Embedded
    newSF_ele_embedded->SetTitle("Electron Embedded SF" + year + "_" + firstHLTPath);
    newSF_ele_embedded->Draw("");
    newSF_ele_embedded->Draw("TEXT45 SAME");
    c1->SaveAs(outputPath + "electron_embedded_sf_" + year + "_"  + firstHLTPath + ".png");
    c1->SaveAs(outputPath + "electron_embedded_sf_" + year + "_"  + firstHLTPath + ".pdf");

    newSF_ele_mc->SetTitle("Electron MC SF" + year + "_" + firstHLTPath);
    newSF_ele_mc->Draw("");
    newSF_ele_mc->Draw("TEXT45 SAME");
    c1->SaveAs(outputPath + "electron_mc_sf_" + year + "_" + firstHLTPath + ".png");
    c1->SaveAs(outputPath + "electron_mc_sf_" + year + "_"  + firstHLTPath + ".pdf");

//********************************************************************* */
//   second cross-trigger: HLTMu23Ele12
//********************************************************************* */

    path = "sf_el_" + year + "_" + secondHLTPath + ".root";

    newFile = new TFile(path);
    if (!newFile->IsOpen() || newFile==0 ) {
        std::cout<<"ERROR: FILE "<< path <<" NOT FOUND; EXITING" << std::endl;
        return 0;
    }
    newEff_ele_mc = (TH2F*) newFile->Get("eff_mc");
    if (newEff_ele_mc == 0) {
        std::cout << "ERROR: eff_mc not found in file; EXITING" << std::endl;
        return 0;
    }
    newEff_ele_embedded = (TH2F*) newFile->Get("eff_embedded");
    if (newEff_ele_embedded == 0) {
        std::cout << "ERROR: eff_embedded not found in file; EXITING" << std::endl;
        return 0;
    }
    newEff_ele_data = (TH2F*) newFile->Get("eff_data");
    if (newEff_ele_data == 0) {
        std::cout << "ERROR: eff_data not found in file; EXITING" << std::endl;
        return 0;
    }    
    newSF_ele_mc = (TH2F*) newFile->Get("SF2D_mc");
    if (newSF_ele_mc == 0) {
        std::cout << "ERROR: SF2D_mc not found in file; EXITING" << std::endl;
        return 0;
    }

    newSF_ele_embedded = (TH2F*) newFile->Get("SF2D_embedded");
    if (newSF_ele_embedded == 0) {
        std::cout << "ERROR: SF2D_embedded not found in file; EXITING" << std::endl;
        return 0;
    }

    //Max and min
    newSF_ele_mc->SetMaximum(2.0);
    newSF_ele_embedded->SetMaximum(2.0);

    newSF_ele_mc->SetMinimum(0.0);
    newSF_ele_embedded->SetMinimum(0.0);

    c1 = new TCanvas("Tcan","", 100, 20, 1000, 800);
    leg = new TLegend(0.60,0.75,0.85,0.9);

    //
    // Draw the electrons MC eff 
    newEff_ele_mc->SetTitle("Electron MC eff" + year + "_" + secondHLTPath);
    newEff_ele_mc->Draw("");
    newEff_ele_mc->Draw("TEXT45 SAME");

    c1->SaveAs(outputPath + "electron_mc_eff_" + year +"_" + secondHLTPath + ".png");
    c1->SaveAs(outputPath + "electron_mc_eff_" + year +"_" + secondHLTPath + ".pdf");

    // Draw the electrons Embedded eff
    newEff_ele_embedded->SetTitle("Electron Embedded eff" + year + "_" + secondHLTPath);
    newEff_ele_embedded->Draw("");
    newEff_ele_embedded->Draw("TEXT45 SAME");
    c1->SaveAs(outputPath + "electron_embedded_eff_" + year + "_" + secondHLTPath + ".png");
    c1->SaveAs(outputPath + "electron_embedded_eff_" + year + "_" + secondHLTPath + ".pdf");

    // Draw the electrons Data eff
    newEff_ele_data->SetTitle("Electron Data eff" + year + "_" + secondHLTPath);
    newEff_ele_data->Draw("");
    newEff_ele_data->Draw("TEXT45 SAME");
    c1->SaveAs(outputPath + "electron_data_eff_" + year + "_" + secondHLTPath + ".png");
    c1->SaveAs(outputPath + "electron_data_eff_" + year + "_"  + secondHLTPath + ".pdf");

    // Draw the electrons SF2D
    //Embedded
    newSF_ele_embedded->SetTitle("Electron Embedded SF" + year + "_" + secondHLTPath);
    newSF_ele_embedded->Draw("");
    newSF_ele_embedded->Draw("TEXT45 SAME");
    c1->SaveAs(outputPath + "electron_embedded_sf_" + year + "_"  + secondHLTPath + ".png");
    c1->SaveAs(outputPath + "electron_embedded_sf_" + year + "_"  + secondHLTPath + ".pdf");

    newSF_ele_mc->SetTitle("Electron MC SF" + year + "_" + secondHLTPath);
    newSF_ele_mc->Draw("");
    newSF_ele_mc->Draw("TEXT45 SAME");
    c1->SaveAs(outputPath + "electron_mc_sf_" + year + "_" + secondHLTPath + ".png");
    c1->SaveAs(outputPath + "electron_mc_sf_" + year + "_"  + secondHLTPath + ".pdf");
    return 1;
}

