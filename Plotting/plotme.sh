########################################
#
# plotting script
#
########################################

# name of analyses
analysis="HWWAnalysis"

# location of their outputs
outputpath="../Analysis/Output_HWWAnalysis" \

# run main command
root -l -b << EOF
.L Plotting.cxx+
    Plotting *m=new Plotting();
    m->SetLumi(10064);
	m->SetOption("$analysis");
    m->SetInputLocation("$outputpath")
    m->run()
    .q
EOF
########################################
