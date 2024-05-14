import ROOT

def extract_hist_values():
    # Open the ROOT file
    file = ROOT.TFile("ROSPHERE_response_23_noBGO_CoEf_th300.root", "READ")

    # Retrieve the histogram
    hist = file.Get("hist2")
    if not hist:
        print("Histogram not found!")
        return []

    # Get the number of bins
    nBins = hist.GetNbinsX()

    # Extract the bin contents
    bin_values = [hist.GetBinContent(i) for i in range(1, nBins + 1)]

    # Close the file
    file.Close()

    return bin_values

# Print the bin values as a Python list
print(extract_hist_values())

