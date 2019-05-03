

def print_vars(n, vars):
  for var in vars :
    name = n + var
    print "Double_t * " + name + " = event.GetVar(\"" + name + "\");"

def print_lorenz_def( vars ):
  print "TLorentzVector ",
  for var in vars :
    print var,
    if var != vars[-1] : print ",",
  print ";"


def print_lorenz_set(name):
  print name + ".SetPtEtaPhiM(*" + name + "_pt, *", name + "_eta, *", name + "_phi, *", name + "_m);"



##################### JETS
print "##################### JETS"
jets = ["ptag_pfjets02", "ptag_pfjets04", "ptag_pfjets08"]
drops = ["", "_softDroppedJet", "_leadingSoftDroppedSubJet", "_trailingSoftDroppedSubJet"]
vars = ["_pt", "_eta", "_phi", "_m"]

for jet in jets :
  for drop in drops :
    print_vars(jet + drop, vars)

for jet in jets :
  jnames = [ jet + name for name in drops ]
  print_lorenz_def( jnames )
  
for jet in jets :
  for drop in drops :
    name = jet + drop
    print_lorenz_set(name)

##################### PHOTON
print "##################### PHOTON"
jets = ["photon"]

for jet in jets :
  print_vars(jet, vars)

print_lorenz_def( jets )
  
for jet in jets :
  print_lorenz_set(jet)

##################### OTHER
if True:
  jets = ["ptag_pfjets02", "ptag_pfjets04", "ptag_pfjets08"]
  drops = ["", "_softDroppedJet", "_leadingSoftDroppedSubJet", "_trailingSoftDroppedSubJet"]
  jnames = []
  for jet in jets:
    jnames += [ jet + name for name in drops]
  for name in jnames:
    print name + ",",



