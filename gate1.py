import ROOT

# Open the ROOT file
file_path = "ROSPHERE_response_23_noBGO_CoEf_th300.root"
root_file = ROOT.TFile.Open(file_path, "READ")

# Access the TTree
# Adjust the name if your TTree is named differently
tree = root_file.Get("tree")

# Prepare a histogram
# Adjust bins as needed
histogram = ROOT.TH1F(
    "histogram", "Histogram of Vector Sizes with Element == 1", 100, 0, 100)

# Loop over the entries in the TTree
for entry in tree:
    id_vector = entry.id  # Adjust the variable name if needed
    if 1 in id_vector:  # Check if 1 is an element of the vector
        # Fill the histogram with the size of the vector
        histogram.Fill(id_vector.size())
# Create a list to hold the bin contents
bin_contents = []
for i in range(1, histogram.GetNbinsX() + 1):
    bin_contents.append(histogram.GetBinContent(i))

# Print the list or return it
print(bin_contents)
# Draw the histogram
histogram.Draw()


# Save the histogram to a file or display it, depending on your setup
ROOT.gROOT.SetBatch(True)  # Uncomment if running in a non-interactive mode
canvas = ROOT.TCanvas()
histogram.Draw()
canvas.SaveAs("output_histogram.png")

root_file.Close()
