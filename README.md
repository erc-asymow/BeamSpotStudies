# BeamSpotStudies

## Dump BeamSpot infos from DB:
```
wget https://raw.githubusercontent.com/cms-sw/cmssw/master/CondTools/BeamSpot/test/BeamSpotRcdPrinter_cfg.py .
cmsRun BeamSpotRcdPrinter_cfg.py  # for 2016: --startIOV 1173204676640769 --endIOV 1219959690625054
```
The first and last IOV are determined by looking at the json:
```
/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/Legacy_2016/Cert_271036-284044_13TeV_Legacy2016_Collisions16_JSON.txt
```
using the unpack functions. E.g.:
```
root[0] #include "CondFormats/Common/interface/TimeConversions.h"
root[1] cond::time::pack({284044, 30})
```

## Produce a brilcalc output file containing a summary of lumi and avg pileup LS-by-LS:
```
setenv PATH $HOME/.local/bin:/cvmfs/cms-bril.cern.ch/brilconda/bin:$PATH
pip install --user --upgrade brilws
~/.local/bin/brilcalc lumi --normtag /cvmfs/cms-bril.cern.ch/cms-lumi-pog/Normtags/normtag_PHYSICS.json -u /fb -i /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/Legacy_2016/Cert_271036-284044_13TeV_Legacy2016_Collisions16_JSON.txt --byls --minBiasXsec 69200 --xingTr 0.1 > 2016_brilcalc_byls_69200ub.txt
# FIXME: brilcalc supports the -o option to output a csv file directly
```